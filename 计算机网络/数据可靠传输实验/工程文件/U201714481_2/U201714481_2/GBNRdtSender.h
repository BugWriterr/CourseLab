#pragma once
#ifndef GBN_RDT_SENDER_H
#define GBN_RDT_SENDER_H
#include "RdtSender.h"
#include <list>

//��Ҫ֪����ǰbase
//�����ϲ㱨��ʱ�����������
//�жϵ�ǰ������û�����ȴ�״̬
class GBNRDTSender :public RdtSender {
private :
	int base;//���ʹ��ڵ�һ���ѷ��͵��ǻ�ûȷ�ϵ�
	int nextseqnum;//�����ͱ��ĵ���һ�����
	list<Packet> sending_packet;//�����ͱ��ģ������ڱ���
	int packetcount;//��ǰ�ڴ����ڵı�������
	bool waitstate;//�ȴ�״̬


public:
	static const int window_size;//���ڴ�С
	static const int seq_num_bits;//������ŵ�λ��
	static const int seq_num_max;
	
	GBNRDTSender();
	virtual ~GBNRDTSender();//������������������Ϊ�麯��

	//�����Ϊ���ͷ����ڵȴ�ȷ��״̬���ʹ����������ܾ�����Message���򷵻�false
	virtual bool send(Message &message);
	//����ȷ��Ack������NetworkService����	
	virtual void receive(Packet &ackPkt);

	//Timeout handler������NetworkService����
	virtual void timeoutHandler(int seqNum);

	//����RdtSender�Ƿ��ڵȴ�״̬��������ͷ����ȴ�ȷ�ϻ��߷��ʹ�������������true
	virtual bool getWaitingState();
};


#endif