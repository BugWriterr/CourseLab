#pragma once
#include "stdafx.h"
#include "Global.h"
#include "GBNRdtSender.h"


const int GBNRDTSender::window_size = 4;//���ڴ�СΪ4
const int GBNRDTSender::seq_num_bits = 3;//���λ��
const int GBNRDTSender::seq_num_max = (1 << GBNRDTSender::seq_num_bits);

GBNRDTSender::GBNRDTSender() {
	base = 0;
	nextseqnum = 0;
	waitstate = false;//û���ڵȣ����Խ�������
	packetcount = 0;
	result_file.open("C:\\Users\\ypzhang\\Desktop\\U201714481\\exp2\\U201714481_2\\result_1.txt");
	if (result_file.fail()) {
		cout << "���ͷ��ļ���ʧ�ܣ�\n" << endl;
		exit(0);
	}
}

GBNRDTSender::~GBNRDTSender() {
	result_file.close();
}
bool GBNRDTSender::getWaitingState() {//�ж��Ƿ��ڵȴ�״̬
	if (packetcount < window_size) {
		waitstate = false;
	}
	else {
		waitstate = true;
	}
	return waitstate;
}


bool GBNRDTSender::send(Message &message) {//��������
	if (getWaitingState()) return false;

	Packet sendpacket;
	sendpacket.acknum = 0;//ack����ν
	sendpacket.seqnum = nextseqnum;//���Ϊ��һ�����
	memcpy(sendpacket.payload, message.data, sizeof(message.data));//ȫ�����
	sendpacket.checksum = pUtils->calculateCheckSum(sendpacket);

	sending_packet.push_back(sendpacket);

	pUtils->printPacket("\n\n���ͷ����ͱ���", sendpacket);

	if (base == nextseqnum)  pns->startTimer(SENDER, Configuration::TIME_OUT, nextseqnum);
	nextseqnum = (nextseqnum + 1) % (seq_num_max);//��һ�����

	packetcount++;

	pns->sendToNetworkLayer(RECEIVER, sendpacket);

	return true;
}

void GBNRDTSender::receive(Packet &ackpkt) {
	//��ʹ�� GBN �ͼ򻯰� TCP ��ЩЭ�飬ҲҪ���øò�����ӦΪ���緢
	//����δȷ�ϵ� Packet ��ţ�

	list<Packet>::iterator itr;//������

	int checksum = pUtils->calculateCheckSum(ackpkt);

	if (checksum != ackpkt.checksum) return;

	pUtils->printPacket("\n\n���ͷ���ȷ�յ�ȷ��", ackpkt);

	int count = 0;

	//����ͨ���Ƚ�ack��base��ֵ�������ж��ǲ����յ��ظ���
	for (itr = sending_packet.begin(); itr != sending_packet.end(); itr++) {
		if ((*itr).seqnum == ackpkt.acknum) break;//�ҵ����յ��İ�Ϊֹ
		else count++;
	}

	if (itr == sending_packet.end())//û���ҵ��յ��İ������
		return;

	for (int i = 0; i < count + 1; i++) {//�Ӷ�����ɾ���յ��İ�
		sending_packet.pop_front();//��ǰ�����ݵ��Ƴ�
		packetcount--;
	}

	
	pns->stopTimer(SENDER, base);

	base = (ackpkt.acknum + 1) % seq_num_max;

	result_file<< "���ͷ����������ƶ�" << count + 1 << "�����" << endl;

	result_file<< "���ͷ���NOW BASE=" << base << endl;

	//����������ʱ��
	//	//������������һ����ʱ��ǰ��һ��Ҫ�ȹرոö�ʱ����Ҫע��
	//	//seqNum ������һ���ԣ�������ģ�����绷������ʾ����ͼ����һ���������Ķ�ʱ������
	if (base != nextseqnum) pns->startTimer(SENDER, Configuration::TIME_OUT, base);
}

void GBNRDTSender::timeoutHandler(int seqNum) {//seqNum��ʱ

	/*cout << "���ͷ���ʱ����ʱ����ʱ���������=" << seqNum << endl;*/

	result_file<< "���ͷ���ʱ����ʱ����ʱ���������=" << seqNum << endl;

	pns->stopTimer(SENDER, seqNum);

	pns->startTimer(SENDER, Configuration::TIME_OUT, seqNum);

	list<Packet>::iterator itr;

	for (itr = sending_packet.begin(); itr != sending_packet.end(); itr++) {
		pUtils->printPacket("���ͷ���ʱ��ʱ�䵽���ش��ϴεı���\n", *itr);
		pns->sendToNetworkLayer(RECEIVER, *itr);//�ش���
	}
}

