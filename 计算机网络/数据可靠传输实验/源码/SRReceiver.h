#pragma once
#ifndef SR_RECEIVER_H
#define SR_RECEIVER_H
#include"RdtReceiver.h"
#include<list>


class SRReceiver :public RdtReceiver {
private:
	static const int window_size;
	static const int seq_num_bits;
	static const int seq_num_max;//seq_num的最大值

	int rcvbase;
	Packet sndpkt;
	int packetcount;
	list<Packet> recving_packet;//缓存接收分组

public:
	virtual ~SRReceiver();
	SRReceiver();

	void receive(Packet &packet);
	
};



#endif