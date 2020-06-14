#pragma once
#ifndef GBN_RDT_RECEIVER_H
#define GBN_RDT_RECEIVER_H
#include"RdtReceiver.h"

class GBNRDTReceiver :public RdtReceiver {
private:
	int expectedseqnum;//�������յ��ı������
	int lastacknum;//��һ��ȷ�ϱ������
	Packet sndpkt;//���͵�ȷ�ϱ��ģ�Ҳ���������ش�ʹ��
public:
	//���ձ��ģ�����NetworkService����	

	static const int seq_num_bits;
	static const int seq_num_max;

	virtual ~GBNRDTReceiver();

	GBNRDTReceiver();

	void receive(Packet &packet);		
	
};

#endif