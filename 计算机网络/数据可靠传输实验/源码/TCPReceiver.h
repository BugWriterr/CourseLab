#pragma once
#ifndef TCP_RECEIVER_H
#define TCP_RECEIVER_H
#include"RdtReceiver.h"

class TCPReceiver :public RdtReceiver {
private:
	int expectedseqnum;//期望接收到的报文序号
	int lastacknum;//上一个确认报文序号
	Packet sndpkt;//发送的确认报文，也可以用作重传使用
public:
	//接收报文，将被NetworkService调用	

	static const int seq_num_bits;
	static const int seq_num_max;
	virtual ~TCPReceiver();
	TCPReceiver();

	void receive(Packet &packet);

};

#endif