#pragma once
#ifndef TCP_SENDER_H
#define TCP_SENDER_H
#include "RdtSender.h"
#include <list>

class TCPSender :public RdtSender {
private:
	int base;
	int nextseqnum;
	list<Packet> sending_packet;
	int packetcount;
	bool waitstate;
	int y;//���ظ�ACK���м���

public:
	static const int window_size;//���ڴ�С
	static const int seq_num_bits;//������ŵ�λ��
	static const int seq_num_max;//���ֵ


	TCPSender();
	virtual ~TCPSender();//������������������Ϊ�麯��

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
