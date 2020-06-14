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
	sndpkt.acknum = -1;//-1��ʾ���շ�ȷ����Ч
	sndpkt.seqnum = -1;
	packetcount = 0;
	memset(sndpkt.payload, 0, Configuration::PAYLOAD_SIZE);

	sndpkt.checksum = pUtils->calculateCheckSum(sndpkt);

	result_file.open("C:\\Users\\ypzhang\\Desktop\\U201714481\\exp2\\U201714481_2\\result_2.txt");
	if (result_file.fail()) {
		cout << "���շ��ļ���ʧ�ܣ�\n" << endl;
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

		pUtils->printPacket("\n\n���շ�����ȷ�ϱ��ģ�", sndpkt);

		result_file << "\n���շ���ȷ�յ� " << packet.seqnum << "�ű��ģ�" << endl;

		pns->sendToNetworkLayer(SENDER, sndpkt);

		if ((packet.seqnum - rcvbase + seq_num_max) % seq_num_max >= window_size)
			return;//���ڴ����ں��Ը÷���

		list<Packet>::iterator itr,itr2;

		for (itr = recving_packet.begin(); itr != recving_packet.end(); itr++) {
			if (packet.seqnum == itr->seqnum) {
				flag = 1; break;
			}
			else if ((packet.seqnum - rcvbase + seq_num_max)%seq_num_max < (itr->seqnum - rcvbase + seq_num_max) % seq_num_max)
				break;
		}

		if (itr == recving_packet.end()) {//�ں���ĩβ����
			recving_packet.push_back(packet);
			packetcount++;
			//result_file << "\n���շ��յ�" << packet.seqnum << "�ű��ģ�\n";
		}

		else if (flag == 0) {//�����в����ڸ÷���
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
		result_file << "\n���շ������ƶ��ˣ�" << (packetcount_old - packetcount + seq_num_max) % seq_num_max << endl;
	}
	else {
		pUtils->printPacket("\n\n���շ�û����ȷ�յ����ͷ��ı��ģ�����У����󣬺��Ը÷���", packet);
	}

}

