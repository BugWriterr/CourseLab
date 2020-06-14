#include<stdio.h>
#include<iostream>
#include<stdlib.h>
#include<cstring>
//ע���Ⱥ�˳��
#include"STACK.h"
#include"QUEUE.h"

using namespace std;
extern FILE* fp;



//������ʼ���б�ʵ�ֹ��캯���ͳ�ʼ��
QUEUE::QUEUE(int m) :STACK(m), s(m) {//ÿ��ջ���m��Ԫ�أ�Ҫ��ʵ�ֵĶ����������2m��Ԫ��

}
QUEUE::QUEUE(const QUEUE &q) : STACK(q), s(q.s) {//�ö���q������ʼ������

}
QUEUE::QUEUE(QUEUE&&q) : STACK(move(q)), s(move(q.s))//�ƶ�����//
{

}
QUEUE::operator int() const {			//���ض��е�ʵ��Ԫ�ظ���
	int a = int(s);
	int b = STACK::operator int();
	return a + b;
}
int QUEUE::full()const { //���ض����Ƿ�������������1�����򷵻�0
	if (STACK::operator int() == STACK::size() && int(s)) return 1;
	else return 0;
}
//�����￪ʼs=s2,STACK=s1
int QUEUE::operator[](int x)const {//ȡ�±�Ϊx��Ԫ��,��1��Ԫ���±�Ϊ0
	if (x<0 || x>int(*this)) return -1;
	if (int(s) == 0) {
		return STACK::operator[](x);
	}
	else {
		int t1 = STACK::operator int();
		int t2 = int(s);
		if (x < 0) {
			return -1;//ȷ�����ݲ������-1������-1��ʾ���ݳ���
		}
		else if (x < t2) {
			return s[t2 - 1 - x];
		}
		else if (x < t1 + t2) {
			return STACK::operator[](x - t2);
		}
		else {
			return -1;//��ʾ���ݳ�����������Ԫ��
		}
	}
}
QUEUE& QUEUE::operator<<(int e) {	//��e�����,�����ض���
	int i = 0; int j = STACK::operator int(); int data;
	if (this->full() == 0) {
		if (j == STACK::size()) {
			while (i < j) {
				STACK::operator>>(data);
				s << data;
				i++;
			}
			STACK::operator<<(e);
		}
		else {
			STACK::operator<<(e);
		}
	}
	return *this;
}
QUEUE& QUEUE::operator>>(int &e) {//�����е�e,�����ض���
	int i = 0; int j = STACK::operator int(); int data;
	if ((j + int(s)) != 0) {
		if (int(s) == 0) {
			while (i < j) {
				STACK::operator>>(data);
				s << data;
				i++;
			}
			s >> e;
		}
		else {
			s >> e;
		}
	}
	return *this;
}
QUEUE& QUEUE::operator=(const QUEUE&q) { //��q������,�����ر���ֵ�Ķ���//��ȸ�ֵ�����

	if (this != &q) {
		//STACK::STACK(q);//����ֱ�ӵ��ù��캯�������������֮������飬ֻ�ǹ�����һ����������
		STACK::operator=(q);
		s = q.s;
	}
	return *this;
}

QUEUE& QUEUE::operator=(QUEUE&&q) {//�ƶ���ֵ
	if (this != &q) {
		STACK::operator=(q);
		s = move(q.s);
	}
	return *this;
}

void QUEUE::print() const {			//��ӡ����
	int i = 0;
	int j = STACK::operator int();
	int k = int(s);
	int data = 0;
	for (; i < k; i++) {
		data = s[k - i - 1];
		printf("%d  ", data);
		fprintf(fp, "%d  ", data);
	}
	STACK::print();
}
QUEUE::~QUEUE() {					//���ٶ���

	/*const_cast
	static_cast
	dynamic_cast*/

}
