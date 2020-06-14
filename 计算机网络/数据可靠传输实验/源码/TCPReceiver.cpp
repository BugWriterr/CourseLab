#pragma once
#include "stdafx.h"
#include "Global.h"
#include "TCPReceiver.h"
#include "TCPSender.h"

const int TCPReceiver::seq_num_bits = 3;
const int TCPReceiver::seq_num_max = (1 << TCPReceiver::seq_num_bits);

TCPReceiver::TCPReceiver() {
	expectedseqnum = 0;
	lastacknum = -1;
	sndpkt.acknum = 0;//-1表示接收方确认无效
	sndpkt.seqnum = -1;
	memset(sndpkt.payload, 0, Configuration::PAYLOAD_SIZE);//'.'表示未初始化
	sndpkt.checksum = pUtils->calculateCheckSum(sndpkt);

	result_file.open("C:\\Users\\ypzhang\\Desktop\\U201714481\\exp2\\U201714481_2\\result_3.txt");
	if (result_file.fail()) {
		cout << "接收方文件打开失败！\n" << endl;
		exit(0);
	}
}

TCPReceiver::~TCPReceiver() {
	result_file.close();

}
void TCPReceiver::receive(Packet &packet) {//接收到一个报文
	Message data;
	int checksum = pUtils->calculateCheckSum(packet);

	if (checksum == packet.checksum&&expectedseqnum == packet.seqnum) {//报文正确无误

		pUtils->printPacket("接受方正确收到发送方的报文", packet);

		memcpy(data.data, packet.payload, sizeof(packet.payload));//构造报文

		pns->delivertoAppLayer(RECEIVER, data);

		sndpkt.acknum =(packet.seqnum + 1)%seq_num_max;

		sndpkt.checksum = pUtils->calculateCheckSum(sndpkt);

		pUtils->printPacket("接受方发送确认报文：", sndpkt);

		pns->sendToNetworkLayer(SENDER, sndpkt);//发送正确报文

		lastacknum = expectedseqnum;

		expectedseqnum = (expectedseqnum + 1) % seq_num_max;//得到下一个expectedseqnum

	}
	else {//重传上次确定的报文
		if (checksum != packet.checksum) {
			pUtils->printPacket("\n接收方没有正确收到发送方的报文,数据校验错误:", packet);
		}
		else {
			pUtils->printPacket("\n接收方没有正确收到发送方的报文,报文序号不对:", packet);
		}
		pUtils->printPacket("\n接收方重新发送上次的确认报文", sndpkt);
		pns->sendToNetworkLayer(SENDER, sndpkt);
	}

}