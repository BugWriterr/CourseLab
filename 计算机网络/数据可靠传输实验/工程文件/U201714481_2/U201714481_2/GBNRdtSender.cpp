#pragma once
#include "stdafx.h"
#include "Global.h"
#include "GBNRdtSender.h"


const int GBNRDTSender::window_size = 4;//窗口大小为4
const int GBNRDTSender::seq_num_bits = 3;//序号位数
const int GBNRDTSender::seq_num_max = (1 << GBNRDTSender::seq_num_bits);

GBNRDTSender::GBNRDTSender() {
	base = 0;
	nextseqnum = 0;
	waitstate = false;//没有在等，可以接收数据
	packetcount = 0;
	result_file.open("C:\\Users\\ypzhang\\Desktop\\U201714481\\exp2\\U201714481_2\\result_1.txt");
	if (result_file.fail()) {
		cout << "发送方文件打开失败！\n" << endl;
		exit(0);
	}
}

GBNRDTSender::~GBNRDTSender() {
	result_file.close();
}
bool GBNRDTSender::getWaitingState() {//判断是否在等待状态
	if (packetcount < window_size) {
		waitstate = false;
	}
	else {
		waitstate = true;
	}
	return waitstate;
}


bool GBNRDTSender::send(Message &message) {//发送数据
	if (getWaitingState()) return false;

	Packet sendpacket;
	sendpacket.acknum = 0;//ack无所谓
	sendpacket.seqnum = nextseqnum;//序号为下一个序号
	memcpy(sendpacket.payload, message.data, sizeof(message.data));//全部打包
	sendpacket.checksum = pUtils->calculateCheckSum(sendpacket);

	sending_packet.push_back(sendpacket);

	pUtils->printPacket("\n\n发送方发送报文", sendpacket);

	if (base == nextseqnum)  pns->startTimer(SENDER, Configuration::TIME_OUT, nextseqnum);
	nextseqnum = (nextseqnum + 1) % (seq_num_max);//下一个序号

	packetcount++;

	pns->sendToNetworkLayer(RECEIVER, sendpacket);

	return true;
}

void GBNRDTSender::receive(Packet &ackpkt) {
	//即使是 GBN 和简化版 TCP 这些协议，也要设置该参数（应为最早发
	//出但未确认的 Packet 序号）

	list<Packet>::iterator itr;//迭代器

	int checksum = pUtils->calculateCheckSum(ackpkt);

	if (checksum != ackpkt.checksum) return;

	pUtils->printPacket("\n\n发送方正确收到确认", ackpkt);

	int count = 0;

	//不能通过比较ack与base的值来进行判断是不是收到重复的
	for (itr = sending_packet.begin(); itr != sending_packet.end(); itr++) {
		if ((*itr).seqnum == ackpkt.acknum) break;//找到了收到的包为止
		else count++;
	}

	if (itr == sending_packet.end())//没有找到收到的包的序号
		return;

	for (int i = 0; i < count + 1; i++) {//从队列中删掉收到的包
		sending_packet.pop_front();//将前面数据的移除
		packetcount--;
	}

	
	pns->stopTimer(SENDER, base);

	base = (ackpkt.acknum + 1) % seq_num_max;

	result_file<< "发送方滑动窗口移动" << count + 1 << "个序号" << endl;

	result_file<< "发送方：NOW BASE=" << base << endl;

	//重新启动计时器
	//	//另外重新启动一个定时器前，一定要先关闭该定时器（要注意
	//	//seqNum 参数的一致性），否则模拟网络环境会提示“试图启动一个已启动的定时器”。
	if (base != nextseqnum) pns->startTimer(SENDER, Configuration::TIME_OUT, base);
}

void GBNRDTSender::timeoutHandler(int seqNum) {//seqNum超时

	/*cout << "发送方计时器超时，定时器报文序号=" << seqNum << endl;*/

	result_file<< "发送方计时器超时，定时器报文序号=" << seqNum << endl;

	pns->stopTimer(SENDER, seqNum);

	pns->startTimer(SENDER, Configuration::TIME_OUT, seqNum);

	list<Packet>::iterator itr;

	for (itr = sending_packet.begin(); itr != sending_packet.end(); itr++) {
		pUtils->printPacket("发送方定时器时间到，重传上次的报文\n", *itr);
		pns->sendToNetworkLayer(RECEIVER, *itr);//重传；
	}
}

