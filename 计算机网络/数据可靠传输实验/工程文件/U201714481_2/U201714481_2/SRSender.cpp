#pragma once
#include "stdafx.h"
#include "Global.h"
#include "SRSender.h"

const int SRSender::window_size = 4;
const int SRSender::seq_num_bits = 3;
const int SRSender::seq_num_max = (1 << SRSender::seq_num_bits);

SRSender::SRSender() {
	base = 0;
	nextseqnum = 0;
	waitstate = false;
	packetcount = 0;
	result_file.open("C:\\Users\\ypzhang\\Desktop\\U201714481\\exp2\\U201714481_2\\result_2.txt");
	if (result_file.fail()) {
		cout << "发送方文件打开失败！\n" << endl;
		exit(0);
	}
}
SRSender::~SRSender() {
	result_file.close();
}
bool SRSender::getWaitingState() {
	if (packetcount < window_size) {
		waitstate = false;
	}
	else {
		waitstate = true;
	}
	return waitstate;
}

bool SRSender::send(Message &message) {
	if (getWaitingState()) return false;

	Packet sendpacket;
	sendpacket.acknum = 0;
	sendpacket.seqnum = nextseqnum;
	memset(sendpacket.payload, 0, sizeof(sendpacket.payload));
	memcpy(sendpacket.payload, message.data, sizeof(message.data));
	sendpacket.checksum = pUtils->calculateCheckSum(sendpacket);

	sending_packet.push_back(sendpacket);

	pUtils->printPacket("\n\n发送方发送报文", sendpacket);

	pns->startTimer(SENDER, Configuration::TIME_OUT, nextseqnum);

	nextseqnum = (nextseqnum + 1) % (seq_num_max);

	packetcount++;

	pns->sendToNetworkLayer(RECEIVER, sendpacket);

	return true;

}

void SRSender::receive(Packet &ackpkt) {
	int checksum = pUtils->calculateCheckSum(ackpkt);
	if (checksum != ackpkt.checksum) {
		pUtils->printPacket("\n\n发送方收到错误确认", ackpkt);
		return;
	}

	pUtils->printPacket("\n\n发送方收到正确确认", ackpkt);

	list<Packet> ::iterator itr;

	int base_last = base;//

	for (itr = sending_packet.begin(); itr != sending_packet.end(); itr++) {
		if (itr->seqnum == ackpkt.acknum) break;
	}

	//找到或者没找到
	if (itr == sending_packet.end()) {
		return;
	}
	else {//该ACK在窗口内
		sending_packet.erase(itr);//删除该packet
		result_file << "\n发送方接收到第" << ackpkt.acknum << " 报文的确认!\n";
		packetcount--;
		if (packetcount) base = sending_packet.begin()->seqnum;
		else {
			base = nextseqnum;
		}
	}

	pns->stopTimer(SENDER, ackpkt.acknum);//关闭收到ACK的定时器 

	result_file << "\n\n发送方窗口移动了" << (base + seq_num_max - base_last) % seq_num_max << "个单位" << endl;
	result_file << "\n发送方NOW BASE=" << base << endl;

}
void SRSender::timeoutHandler(int seqnum) {
	result_file << "\n发送方计时器超时，定时器报文序号=" << seqnum << endl;

	pns->stopTimer(SENDER, seqnum);

	pns->startTimer(SENDER, Configuration::TIME_OUT, seqnum);

	list<Packet>::iterator itr;

	for (itr = sending_packet.begin(); itr != sending_packet.end(); itr++) {
		if (itr->seqnum == seqnum) {//重传该分组
			pUtils->printPacket("\n\n发送方定时器时间到，重传该报文", *itr);
			pns->sendToNetworkLayer(RECEIVER, *itr);			//重新发送数据包
		}
	}

}