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
	int y;//对重复ACK进行计数

public:
	static const int window_size;//窗口大小
	static const int seq_num_bits;//报文序号的位数
	static const int seq_num_max;//最大值


	TCPSender();
	virtual ~TCPSender();//析构函数尽量都定义为虚函数

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
