#include "stdafx.h"
#include "Global.h"
#include "StopWaitRdtSender.h"


const int StopWaitRdtSender::SEQ_NUM_BITS = 3;
const int StopWaitRdtSender::WINDOWS_SIZE = (1 << StopWaitRdtSender::SEQ_NUM_BITS) - 1;

StopWaitRdtSender::StopWaitRdtSender():base(0), lastSentSeqNum(-1), waitingAckPacketCount(0)
{
}


StopWaitRdtSender::~StopWaitRdtSender()
{
}

//若发送窗口已满
bool StopWaitRdtSender::getWaitingState() {
	return this->waitingAckPacketCount >= StopWaitRdtSender::WINDOWS_SIZE;
}

int StopWaitRdtSender::next_seq(int seqNum) {
	return (seqNum + 1) % (1 << StopWaitRdtSender::SEQ_NUM_BITS);
}


bool StopWaitRdtSender::send(Message &message) {
	if (this->getWaitingState()) {					//发送方发送窗口已满
		return false;
	}

	Packet mypacket;
	mypacket.acknum = -1;	//接收方无需确认ack
	mypacket.seqnum = next_seq(lastSentSeqNum);
	lastSentSeqNum = mypacket.seqnum;
	memcpy(mypacket.payload, message.data, sizeof(message.data));
	mypacket.checksum = pUtils->calculateCheckSum(mypacket);
	this->packetWaiting.push_back(mypacket);
	pUtils->printPacket("\n\n发送方发送报文", mypacket);

	if (base == lastSentSeqNum)
	{
		pns->startTimer(SENDER, Configuration::TIME_OUT, base);    //启动发送方定时器
	}

	pns->sendToNetworkLayer(RECEIVER, mypacket);				//调用模拟网络环境的sendToNetworkLayer，通过网络层发送到对方

	this->waitingAckPacketCount = packetWaiting.size();
	return true;
}

void StopWaitRdtSender::receive(Packet &ackPkt) {
	int checkSum = pUtils->calculateCheckSum(ackPkt);
	if (checkSum == ackPkt.checksum)
	{
		int oldBase = base;

		pUtils->printPacket("发送方正确收到确认", ackPkt);
		int i = 0;
		list<Packet>::iterator iter;
		for (iter = packetWaiting.begin(); iter != packetWaiting.end() && ackPkt.acknum != iter->seqnum; iter++) 
		{
			i++;
		}
		if (iter == packetWaiting.end())
			i = 0;
		else
			i = i + 1;
		for (int j = 0; j < i; j++)
		{
			packetWaiting.pop_front();
			base = next_seq(base);	//这时才移动滑动窗口
		}
		if (i == 0) {
			return;
		}
		else {
			cout << "滑动窗口移动" << i << "个序号, 新base = " << base << endl;
		}

		if (base == next_seq(lastSentSeqNum)) //这时队列为空，才关闭定时器
			pns->stopTimer(SENDER, oldBase);
		else {
			pns->stopTimer(SENDER, oldBase);
			pns->startTimer(SENDER, Configuration::TIME_OUT, base);
		}

		this->waitingAckPacketCount = packetWaiting.size();
	}
}

void StopWaitRdtSender::timeoutHandler(int seqNum) {
	cout << "发送方定时器事件到, 定时器报文序号 = " << seqNum << endl;
	pns->stopTimer(SENDER, seqNum);											//首先关闭定时器
	pns->startTimer(SENDER, Configuration::TIME_OUT, seqNum);				//重新启动发送方定时器
	for (list<Packet>::iterator iter = packetWaiting.begin(); iter != packetWaiting.end(); iter++)
	{
		pUtils->printPacket("发送方定时器时间到，重发上次发送的报文", *iter);
		pns->sendToNetworkLayer(RECEIVER, *iter);			//重新发送数据包
	}
}
