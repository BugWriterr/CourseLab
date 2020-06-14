#pragma once
#ifndef SR_SENDER_H
#define SR_SENDER_H
#include "RdtSender.h"
#include <list>

class SRSender :public RdtSender {//����SR���ͷ�
private:
	int base;
	int nextseqnum;
	list<Packet>  sending_packet;
	int packetcount;
	bool waitstate;
public:
	static const int window_size;
	static const int seq_num_bits;
	static const int seq_num_max;

	SRSender();
	virtual ~SRSender();

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