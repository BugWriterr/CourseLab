// StopWait.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "Global.h"
#include "RdtSender.h"
#include "RdtReceiver.h"
#include "StopWaitRdtSender.h"
#include "StopWaitRdtReceiver.h"
#include"GBNRdtSender.h"
#include"GBNRdtReceiver.h"
#include"SRSender.h"
#include"SRReceiver.h"
#include"TCPSender.h"
#include"TCPReceiver.h"
#include <string>

using namespace std;

int main(int argc, char **argv)
{
	if (argc <= 1) {
		cout << "传入参数错误！\n" << endl;
		return 0;
	}

	cout << "*******可靠传输协议实验*******" << endl;
	cout << "请选择协议类型：" << endl;
	cout << "1:GBN" << endl;
	cout << "2.SR" << endl;
	cout << "3.TCP" << endl;
	cout << "0.EXIT" << endl;
	int c = stoi(argv[1]);
	RdtSender *ps = NULL;
	RdtReceiver *pr = NULL;
		switch (c)
		{
		case 1:
			ps = new GBNRDTSender();
			pr = new GBNRDTReceiver();
			break;
		case 2:
			ps = new SRSender();
			pr = new SRReceiver();
			break;
		case 3:
			ps = new TCPSender();
		    pr = new TCPReceiver();
			break;
		case 0:
			break;
		default:
			break;
		}
		pns->init();
		pns->setRtdSender(ps);
		pns->setRtdReceiver(pr);
		pns->setInputFile("C:\\Users\\ypzhang\\Desktop\\U201714481\\exp2\\U201714481_2\\input.txt");
		pns->setOutputFile("C:\\Users\\ypzhang\\Desktop\\U201714481\\exp2\\U201714481_2\\output.txt");

		pns->start();
		delete ps;
		delete pr;
		delete pUtils;									//指向唯一的工具类实例，只在main函数结束前delete
		delete pns;										//指向唯一的模拟网络环境类实例，只在main函数结束前delet
		return 0;

}

