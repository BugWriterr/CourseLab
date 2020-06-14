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
		cout << "���ͷ��ļ���ʧ�ܣ�\n" << endl;
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

	pUtils->printPacket("\n\n���ͷ����ͱ���", sendpacket);

	pns->startTimer(SENDER, Configuration::TIME_OUT, nextseqnum);

	nextseqnum = (nextseqnum + 1) % (seq_num_max);

	packetcount++;

	pns->sendToNetworkLayer(RECEIVER, sendpacket);

	return true;

}

void SRSender::receive(Packet &ackpkt) {
	int checksum = pUtils->calculateCheckSum(ackpkt);
	if (checksum != ackpkt.checksum) {
		pUtils->printPacket("\n\n���ͷ��յ�����ȷ��", ackpkt);
		return;
	}

	pUtils->printPacket("\n\n���ͷ��յ���ȷȷ��", ackpkt);

	list<Packet> ::iterator itr;

	int base_last = base;//

	for (itr = sending_packet.begin(); itr != sending_packet.end(); itr++) {
		if (itr->seqnum == ackpkt.acknum) break;
	}

	//�ҵ�����û�ҵ�
	if (itr == sending_packet.end()) {
		return;
	}
	else {//��ACK�ڴ�����
		sending_packet.erase(itr);//ɾ����packet
		result_file << "\n���ͷ����յ���" << ackpkt.acknum << " ���ĵ�ȷ��!\n";
		packetcount--;
		if (packetcount) base = sending_packet.begin()->seqnum;
		else {
			base = nextseqnum;
		}
	}

	pns->stopTimer(SENDER, ackpkt.acknum);//�ر��յ�ACK�Ķ�ʱ�� 

	result_file << "\n\n���ͷ������ƶ���" << (base + seq_num_max - base_last) % seq_num_max << "����λ" << endl;
	result_file << "\n���ͷ�NOW BASE=" << base << endl;

}
void SRSender::timeoutHandler(int seqnum) {
	result_file << "\n���ͷ���ʱ����ʱ����ʱ���������=" << seqnum << endl;

	pns->stopTimer(SENDER, seqnum);

	pns->startTimer(SENDER, Configuration::TIME_OUT, seqnum);

	list<Packet>::iterator itr;

	for (itr = sending_packet.begin(); itr != sending_packet.end(); itr++) {
		if (itr->seqnum == seqnum) {//�ش��÷���
			pUtils->printPacket("\n\n���ͷ���ʱ��ʱ�䵽���ش��ñ���", *itr);
			pns->sendToNetworkLayer(RECEIVER, *itr);			//���·������ݰ�
		}
	}

}