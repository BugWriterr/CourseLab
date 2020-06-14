#pragma once
#include "stdafx.h"
#include "Global.h"
#include "TCPSender.h"

const int TCPSender::window_size = 4;
const int TCPSender::seq_num_bits = 3;
const int TCPSender::seq_num_max = (1 << TCPSender::seq_num_bits);

TCPSender::TCPSender() {
	base = 0;
	nextseqnum = 0;
	packetcount = 0;

	waitstate = false;
	y = 0;

	result_file.open("C:\\Users\\ypzhang\\Desktop\\U201714481\\exp2\\U201714481_2\\result_3.txt");
	if (result_file.fail()) {
		cout << "发送方文件打开失败！\n" << endl;
		exit(0);
	}
}
TCPSender::~TCPSender() {
	result_file.close();

}

bool TCPSender::getWaitingState() {
	if (packetcount < window_size) {
		waitstate = false;
	}
	else {
		waitstate = true;
	}
	return waitstate;
}
bool TCPSender::send(Message &message) {//得到报文段发送
	if (getWaitingState()) return false;

	Packet sendpacket;
	sendpacket.acknum = 0;
	sendpacket.seqnum = nextseqnum;
	memset(sendpacket.payload, 0, sizeof(sendpacket.payload));
	memcpy(sendpacket.payload, message.data, sizeof(message.data));

	sendpacket.checksum = pUtils->calculateCheckSum(sendpacket);

	sending_packet.push_back(sendpacket);

	pUtils->printPacket("\n\n发送方发送报文", sendpacket);

	if (base == nextseqnum) pns->startTimer(SENDER, Configuration::TIME_OUT, nextseqnum);

	nextseqnum = (nextseqnum + 1) % seq_num_max;

	packetcount++;

	pns->sendToNetworkLayer(RECEIVER, sendpacket);

	return true;
}

void TCPSender::receive(Packet &ackpkt) {
	int checksum = pUtils->calculateCheckSum(ackpkt);
	if (checksum != ackpkt.checksum) {
		pUtils->printPacket("\n\n发送方检测到确认报文检验和错误", ackpkt);
		return;
	}
	pUtils->printPacket("\n\n发送方正确收到确认", ackpkt);
	
	list<Packet>::iterator itr;//迭代器

	int count = 0;
	//不能通过比较ack与base的值来进行判断是不是收到重复的
	for (itr = sending_packet.begin(); itr != sending_packet.end(); itr++) {
		if ((*itr).seqnum == (ackpkt.acknum - 1+seq_num_max)%seq_num_max) break;//找到了收到的包为止
		else count++;
	}
	if (itr == sending_packet.end())//没有找到收到的包的序号
	{
		count = -1;//表示收到之前重复的包以前确认过了

		y++;

		if (y == 3) {//快速重传base
			result_file << "\n\n发送方收到3个重复ACK，开始快速重传" << endl;
			result_file << "重传序号为：" << base << endl;
			pns->stopTimer(SENDER, base);
			pns->sendToNetworkLayer(RECEIVER, *sending_packet.begin());
			pns->startTimer(SENDER, Configuration::TIME_OUT, base);
		}
		return;//直接返回
	}
	list<Packet>::iterator itr1;

	for (int i = 0; i < count + 1; i++) {//从队列中删掉收到的包
		sending_packet.pop_front();//将前面数据的移除
		packetcount--;
	}

	y = 0;
	
	pns->stopTimer(SENDER, base);

	base = (ackpkt.acknum) % seq_num_max;
	result_file << "发送方滑动窗口移动" << count + 1 << "个序号" << endl;
	result_file << "NOW BASE=" << base << endl;

	if (base != nextseqnum) pns->startTimer(SENDER, Configuration::TIME_OUT, base);
}

void TCPSender::timeoutHandler(int seqNum) {

	result_file << "发送方计时器超时，定时器报文序号=" << seqNum << endl;
	pns->stopTimer(SENDER, seqNum);
	result_file << "发送方定时器时间到，重传该序号的报文\n" << endl;
	pns->stopTimer(SENDER, seqNum);
	list<Packet>::iterator itr;
	itr = sending_packet.begin();
	pns->sendToNetworkLayer(RECEIVER, *itr);
	pns->startTimer(SENDER, Configuration::TIME_OUT,seqNum);
}