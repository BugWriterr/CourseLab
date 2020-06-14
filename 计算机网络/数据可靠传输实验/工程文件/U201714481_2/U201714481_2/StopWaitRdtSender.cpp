#include "stdafx.h"
#include "Global.h"
#include "StopWaitRdtSender.h"


const int StopWaitRdtSender::SEQ_NUM_BITS = 3;
const int StopWaitRdtSender::WINDOWS_SIZE = (1 << StopWaitRdtSender::SEQ_NUM_BITS) - 1;

StopWaitRdtSender::StopWaitRdtSender():base(0), lastSentSeqNum(-1), waitingAckPacketCount(0)
{
}


StopWaitRdtSender::~StopWaitRdtSender()
{
}

//�����ʹ�������
bool StopWaitRdtSender::getWaitingState() {
	return this->waitingAckPacketCount >= StopWaitRdtSender::WINDOWS_SIZE;
}

int StopWaitRdtSender::next_seq(int seqNum) {
	return (seqNum + 1) % (1 << StopWaitRdtSender::SEQ_NUM_BITS);
}


bool StopWaitRdtSender::send(Message &message) {
	if (this->getWaitingState()) {					//���ͷ����ʹ�������
		return false;
	}

	Packet mypacket;
	mypacket.acknum = -1;	//���շ�����ȷ��ack
	mypacket.seqnum = next_seq(lastSentSeqNum);
	lastSentSeqNum = mypacket.seqnum;
	memcpy(mypacket.payload, message.data, sizeof(message.data));
	mypacket.checksum = pUtils->calculateCheckSum(mypacket);
	this->packetWaiting.push_back(mypacket);
	pUtils->printPacket("\n\n���ͷ����ͱ���", mypacket);

	if (base == lastSentSeqNum)
	{
		pns->startTimer(SENDER, Configuration::TIME_OUT, base);    //�������ͷ���ʱ��
	}

	pns->sendToNetworkLayer(RECEIVER, mypacket);				//����ģ�����绷����sendToNetworkLayer��ͨ������㷢�͵��Է�

	this->waitingAckPacketCount = packetWaiting.size();
	return true;
}

void StopWaitRdtSender::receive(Packet &ackPkt) {
	int checkSum = pUtils->calculateCheckSum(ackPkt);
	if (checkSum == ackPkt.checksum)
	{
		int oldBase = base;

		pUtils->printPacket("���ͷ���ȷ�յ�ȷ��", ackPkt);
		int i = 0;
		list<Packet>::iterator iter;
		for (iter = packetWaiting.begin(); iter != packetWaiting.end() && ackPkt.acknum != iter->seqnum; iter++) 
		{
			i++;
		}
		if (iter == packetWaiting.end())
			i = 0;
		else
			i = i + 1;
		for (int j = 0; j < i; j++)
		{
			packetWaiting.pop_front();
			base = next_seq(base);	//��ʱ���ƶ���������
		}
		if (i == 0) {
			return;
		}
		else {
			cout << "���������ƶ�" << i << "�����, ��base = " << base << endl;
		}

		if (base == next_seq(lastSentSeqNum)) //��ʱ����Ϊ�գ��Źرն�ʱ��
			pns->stopTimer(SENDER, oldBase);
		else {
			pns->stopTimer(SENDER, oldBase);
			pns->startTimer(SENDER, Configuration::TIME_OUT, base);
		}

		this->waitingAckPacketCount = packetWaiting.size();
	}
}

void StopWaitRdtSender::timeoutHandler(int seqNum) {
	cout << "���ͷ���ʱ���¼���, ��ʱ��������� = " << seqNum << endl;
	pns->stopTimer(SENDER, seqNum);											//���ȹرն�ʱ��
	pns->startTimer(SENDER, Configuration::TIME_OUT, seqNum);				//�����������ͷ���ʱ��
	for (list<Packet>::iterator iter = packetWaiting.begin(); iter != packetWaiting.end(); iter++)
	{
		pUtils->printPacket("���ͷ���ʱ��ʱ�䵽���ط��ϴη��͵ı���", *iter);
		pns->sendToNetworkLayer(RECEIVER, *iter);			//���·������ݰ�
	}
}
