#pragma once
#include "stdafx.h"
#include "Global.h"
#include "SRReceiver.h"
#include "SRSender.h"


const int SRReceiver::window_size = 4;
const int SRReceiver::seq_num_bits = 3;
const int SRReceiver::seq_num_max = (1 << seq_num_bits);

SRReceiver::SRReceiver() {
	rcvbase = 0;
	sndpkt.acknum = -1;//-1表示接收方确认无效
	sndpkt.seqnum = -1;
	packetcount = 0;
	memset(sndpkt.payload, 0, Configuration::PAYLOAD_SIZE);

	sndpkt.checksum = pUtils->calculateCheckSum(sndpkt);

	result_file.open("C:\\Users\\ypzhang\\Desktop\\U201714481\\exp2\\U201714481_2\\result_2.txt");
	if (result_file.fail()) {
		cout << "接收方文件打开失败！\n" << endl;
		exit(0);
	}

}
SRReceiver::~SRReceiver() {
	result_file.close();
}
void SRReceiver::receive(Packet &packet) {
	int checksum;
	int flag = 0;
	int count = 0;
	int rcvbase_last = rcvbase;
	checksum = pUtils->calculateCheckSum(packet);

	if (checksum == packet.checksum) {

		sndpkt.acknum = packet.seqnum;
		sndpkt.seqnum = -1;
		sndpkt.checksum = pUtils->calculateCheckSum(sndpkt);

		pUtils->printPacket("\n\n接收方发送确认报文：", sndpkt);

		result_file << "\n接收方正确收到 " << packet.seqnum << "号报文！" << endl;

		pns->sendToNetworkLayer(SENDER, sndpkt);

		if ((packet.seqnum - rcvbase + seq_num_max) % seq_num_max >= window_size)
			return;//不在窗口内忽略该分组

		list<Packet>::iterator itr,itr2;

		for (itr = recving_packet.begin(); itr != recving_packet.end(); itr++) {
			if (packet.seqnum == itr->seqnum) {
				flag = 1; break;
			}
			else if ((packet.seqnum - rcvbase + seq_num_max)%seq_num_max < (itr->seqnum - rcvbase + seq_num_max) % seq_num_max)
				break;
		}

		if (itr == recving_packet.end()) {//在后面末尾插入
			recving_packet.push_back(packet);
			packetcount++;
			//result_file << "\n接收方收到" << packet.seqnum << "号报文！\n";
		}

		else if (flag == 0) {//缓存中不存在该分组
			recving_packet.insert(itr, packet);
			packetcount++;

		}

		if (recving_packet.begin()->seqnum == rcvbase) {
			for (itr = recving_packet.begin(); itr != recving_packet.end()&&itr->seqnum==rcvbase; itr++) {
				Message sendmessage;
				memset(sendmessage.data, 0, Configuration::PAYLOAD_SIZE);
				memcpy(sendmessage.data, (*itr).payload, sizeof(itr->payload));
				pns->delivertoAppLayer(RECEIVER, sendmessage);
				rcvbase = (rcvbase + 1) % seq_num_max;
				count++;
			}
		}

		if (itr == recving_packet.end()&&rcvbase==rcvbase_last)
			count = 0;

		int packetcount_old=packetcount;

		for (int i = 0; i < count; i++) {
			recving_packet.pop_front();
			packetcount--;
		}
		result_file << "\nNOW rcvbase=" << rcvbase << endl;
		result_file << "\n接收方窗口移动了：" << (packetcount_old - packetcount + seq_num_max) % seq_num_max << endl;
	}
	else {
		pUtils->printPacket("\n\n接收方没有正确收到发送方的报文，数据校验错误，忽略该分组", packet);
	}

}

