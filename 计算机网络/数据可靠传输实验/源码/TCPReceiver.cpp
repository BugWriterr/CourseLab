#pragma once
#include "stdafx.h"
#include "Global.h"
#include "TCPReceiver.h"
#include "TCPSender.h"

const int TCPReceiver::seq_num_bits = 3;
const int TCPReceiver::seq_num_max = (1 << TCPReceiver::seq_num_bits);

TCPReceiver::TCPReceiver() {
	expectedseqnum = 0;
	lastacknum = -1;
	sndpkt.acknum = 0;//-1��ʾ���շ�ȷ����Ч
	sndpkt.seqnum = -1;
	memset(sndpkt.payload, 0, Configuration::PAYLOAD_SIZE);//'.'��ʾδ��ʼ��
	sndpkt.checksum = pUtils->calculateCheckSum(sndpkt);

	result_file.open("C:\\Users\\ypzhang\\Desktop\\U201714481\\exp2\\U201714481_2\\result_3.txt");
	if (result_file.fail()) {
		cout << "���շ��ļ���ʧ�ܣ�\n" << endl;
		exit(0);
	}
}

TCPReceiver::~TCPReceiver() {
	result_file.close();

}
void TCPReceiver::receive(Packet &packet) {//���յ�һ������
	Message data;
	int checksum = pUtils->calculateCheckSum(packet);

	if (checksum == packet.checksum&&expectedseqnum == packet.seqnum) {//������ȷ����

		pUtils->printPacket("���ܷ���ȷ�յ����ͷ��ı���", packet);

		memcpy(data.data, packet.payload, sizeof(packet.payload));//���챨��

		pns->delivertoAppLayer(RECEIVER, data);

		sndpkt.acknum =(packet.seqnum + 1)%seq_num_max;

		sndpkt.checksum = pUtils->calculateCheckSum(sndpkt);

		pUtils->printPacket("���ܷ�����ȷ�ϱ��ģ�", sndpkt);

		pns->sendToNetworkLayer(SENDER, sndpkt);//������ȷ����

		lastacknum = expectedseqnum;

		expectedseqnum = (expectedseqnum + 1) % seq_num_max;//�õ���һ��expectedseqnum

	}
	else {//�ش��ϴ�ȷ���ı���
		if (checksum != packet.checksum) {
			pUtils->printPacket("\n���շ�û����ȷ�յ����ͷ��ı���,����У�����:", packet);
		}
		else {
			pUtils->printPacket("\n���շ�û����ȷ�յ����ͷ��ı���,������Ų���:", packet);
		}
		pUtils->printPacket("\n���շ����·����ϴε�ȷ�ϱ���", sndpkt);
		pns->sendToNetworkLayer(SENDER, sndpkt);
	}

}