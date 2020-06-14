#pragma once
#ifndef SR_SENDER_H
#define SR_SENDER_H
#include "RdtSender.h"
#include <list>

class SRSender :public RdtSender {//定义SR发送方
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

	//如果因为发送方处于等待确认状态或发送窗口已满而拒绝发送Message，则返回false
	virtual bool send(Message &message);
	//接受确认Ack，将被NetworkService调用	
	virtual void receive(Packet &ackPkt);

	//Timeout handler，将被NetworkService调用
	virtual void timeoutHandler(int seqNum);

	//返回RdtSender是否处于等待状态，如果发送方正等待确认或者发送窗口已满，返回true
	virtual bool getWaitingState();

};



#endif