#ifndef STOP_WAIT_RDT_SENDER_H
#define STOP_WAIT_RDT_SENDER_H
#include "RdtSender.h"
#include "list"
class StopWaitRdtSender :public RdtSender
{
private:

	int base;											//发送窗口起始序号，也就是最早发出还没有被确认的报文序号
	int lastSentSeqNum;									//最后已发送且没被确认的报文序号
	int waitingAckPacketCount;							//已发送并且还没确认的报文个数
	list<Packet> packetWaiting;                         //已发送并等待Ack的数据包

	int next_seq(int seqNum);								//返回下一个序号

public:
	static const int SEQ_NUM_BITS;						//Rdt报文序号编码位数
	static const int WINDOWS_SIZE;						//发送窗口大小

	virtual bool getWaitingState();
	virtual bool send(Message &message);						//发送应用层下来的Message，由NetworkServiceSimulator调用,如果发送方成功地将Message发送到网络层，返回true;如果因为发送方处于等待正确确认状态而拒绝发送Message，则返回false
	virtual void receive(Packet &ackPkt);						//接受确认Ack，将被NetworkServiceSimulator调用	
	virtual void timeoutHandler(int seqNum);					//Timeout handler，将被NetworkServiceSimulator调用

public:
	StopWaitRdtSender();
	virtual ~StopWaitRdtSender();
};

#endif

