#pragma once
#ifndef TCP_RECEIVER_H
#define TCP_RECEIVER_H
#include"RdtReceiver.h"

class TCPReceiver :public RdtReceiver {
private:
	int expectedseqnum;//�������յ��ı������
	int lastacknum;//��һ��ȷ�ϱ������
	Packet sndpkt;//���͵�ȷ�ϱ��ģ�Ҳ���������ش�ʹ��
public:
	//���ձ��ģ�����NetworkService����	

	static const int seq_num_bits;
	static const int seq_num_max;
	virtual ~TCPReceiver();
	TCPReceiver();

	void receive(Packet &packet);

};

#endif