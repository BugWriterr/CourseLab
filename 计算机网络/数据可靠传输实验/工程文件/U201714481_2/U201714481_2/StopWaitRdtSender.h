#ifndef STOP_WAIT_RDT_SENDER_H
#define STOP_WAIT_RDT_SENDER_H
#include "RdtSender.h"
#include "list"
class StopWaitRdtSender :public RdtSender
{
private:

	int base;											//���ʹ�����ʼ��ţ�Ҳ�������緢����û�б�ȷ�ϵı������
	int lastSentSeqNum;									//����ѷ�����û��ȷ�ϵı������
	int waitingAckPacketCount;							//�ѷ��Ͳ��һ�ûȷ�ϵı��ĸ���
	list<Packet> packetWaiting;                         //�ѷ��Ͳ��ȴ�Ack�����ݰ�

	int next_seq(int seqNum);								//������һ�����

public:
	static const int SEQ_NUM_BITS;						//Rdt������ű���λ��
	static const int WINDOWS_SIZE;						//���ʹ��ڴ�С

	virtual bool getWaitingState();
	virtual bool send(Message &message);						//����Ӧ�ò�������Message����NetworkServiceSimulator����,������ͷ��ɹ��ؽ�Message���͵�����㣬����true;�����Ϊ���ͷ����ڵȴ���ȷȷ��״̬���ܾ�����Message���򷵻�false
	virtual void receive(Packet &ackPkt);						//����ȷ��Ack������NetworkServiceSimulator����	
	virtual void timeoutHandler(int seqNum);					//Timeout handler������NetworkServiceSimulator����

public:
	StopWaitRdtSender();
	virtual ~StopWaitRdtSender();
};

#endif

