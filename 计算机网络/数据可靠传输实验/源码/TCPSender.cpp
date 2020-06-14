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
		cout << "���ͷ��ļ���ʧ�ܣ�\n" << endl;
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
bool TCPSender::send(Message &message) {//�õ����Ķη���
	if (getWaitingState()) return false;

	Packet sendpacket;
	sendpacket.acknum = 0;
	sendpacket.seqnum = nextseqnum;
	memset(sendpacket.payload, 0, sizeof(sendpacket.payload));
	memcpy(sendpacket.payload, message.data, sizeof(message.data));

	sendpacket.checksum = pUtils->calculateCheckSum(sendpacket);

	sending_packet.push_back(sendpacket);

	pUtils->printPacket("\n\n���ͷ����ͱ���", sendpacket);

	if (base == nextseqnum) pns->startTimer(SENDER, Configuration::TIME_OUT, nextseqnum);

	nextseqnum = (nextseqnum + 1) % seq_num_max;

	packetcount++;

	pns->sendToNetworkLayer(RECEIVER, sendpacket);

	return true;
}

void TCPSender::receive(Packet &ackpkt) {
	int checksum = pUtils->calculateCheckSum(ackpkt);
	if (checksum != ackpkt.checksum) {
		pUtils->printPacket("\n\n���ͷ���⵽ȷ�ϱ��ļ���ʹ���", ackpkt);
		return;
	}
	pUtils->printPacket("\n\n���ͷ���ȷ�յ�ȷ��", ackpkt);
	
	list<Packet>::iterator itr;//������

	int count = 0;
	//����ͨ���Ƚ�ack��base��ֵ�������ж��ǲ����յ��ظ���
	for (itr = sending_packet.begin(); itr != sending_packet.end(); itr++) {
		if ((*itr).seqnum == (ackpkt.acknum - 1+seq_num_max)%seq_num_max) break;//�ҵ����յ��İ�Ϊֹ
		else count++;
	}
	if (itr == sending_packet.end())//û���ҵ��յ��İ������
	{
		count = -1;//��ʾ�յ�֮ǰ�ظ��İ���ǰȷ�Ϲ���

		y++;

		if (y == 3) {//�����ش�base
			result_file << "\n\n���ͷ��յ�3���ظ�ACK����ʼ�����ش�" << endl;
			result_file << "�ش����Ϊ��" << base << endl;
			pns->stopTimer(SENDER, base);
			pns->sendToNetworkLayer(RECEIVER, *sending_packet.begin());
			pns->startTimer(SENDER, Configuration::TIME_OUT, base);
		}
		return;//ֱ�ӷ���
	}
	list<Packet>::iterator itr1;

	for (int i = 0; i < count + 1; i++) {//�Ӷ�����ɾ���յ��İ�
		sending_packet.pop_front();//��ǰ�����ݵ��Ƴ�
		packetcount--;
	}

	y = 0;
	
	pns->stopTimer(SENDER, base);

	base = (ackpkt.acknum) % seq_num_max;
	result_file << "���ͷ����������ƶ�" << count + 1 << "�����" << endl;
	result_file << "NOW BASE=" << base << endl;

	if (base != nextseqnum) pns->startTimer(SENDER, Configuration::TIME_OUT, base);
}

void TCPSender::timeoutHandler(int seqNum) {

	result_file << "���ͷ���ʱ����ʱ����ʱ���������=" << seqNum << endl;
	pns->stopTimer(SENDER, seqNum);
	result_file << "���ͷ���ʱ��ʱ�䵽���ش�����ŵı���\n" << endl;
	pns->stopTimer(SENDER, seqNum);
	list<Packet>::iterator itr;
	itr = sending_packet.begin();
	pns->sendToNetworkLayer(RECEIVER, *itr);
	pns->startTimer(SENDER, Configuration::TIME_OUT,seqNum);
}