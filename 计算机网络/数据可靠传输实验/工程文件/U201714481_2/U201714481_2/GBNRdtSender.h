#pragma once
#ifndef GBN_RDT_SENDER_H
#define GBN_RDT_SENDER_H
#include "RdtSender.h"
#include <list>

//需要知道当前base
//接收上层报文时，给他的序号
//判断当前窗口有没有满等待状态
class GBNRDTSender :public RdtSender {
private :
	int base;//发送窗口第一个已发送但是还没确认的
	int nextseqnum;//待发送报文的下一个序号
	list<Packet> sending_packet;//待发送报文，窗口内报文
	int packetcount;//当前在窗口内的报文总数
	bool waitstate;//等待状态


public:
	static const int window_size;//窗口大小
	static const int seq_num_bits;//报文序号的位数
	static const int seq_num_max;
	
	GBNRDTSender();
	virtual ~GBNRDTSender();//析构函数尽量都定义为虚函数

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