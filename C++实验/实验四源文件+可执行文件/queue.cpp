#include<stdio.h>
#include<iostream>
#include<stdlib.h>
#include<cstring>
//注意先后顺序
#include"STACK.h"
#include"QUEUE.h"

using namespace std;
extern FILE* fp;



//参数初始化列表实现构造函数和初始化
QUEUE::QUEUE(int m) :STACK(m), s(m) {//每个栈最多m个元素，要求实现的队列最多能入2m个元素

}
QUEUE::QUEUE(const QUEUE &q) : STACK(q), s(q.s) {//用队列q拷贝初始化队列

}
QUEUE::QUEUE(QUEUE&&q) : STACK(move(q)), s(move(q.s))//移动构造//
{

}
QUEUE::operator int() const {			//返回队列的实际元素个数
	int a = int(s);
	int b = STACK::operator int();
	return a + b;
}
int QUEUE::full()const { //返回队列是否已满，满返回1，否则返回0
	if (STACK::operator int() == STACK::size() && int(s)) return 1;
	else return 0;
}
//从这里开始s=s2,STACK=s1
int QUEUE::operator[](int x)const {//取下标为x的元素,第1个元素下标为0
	if (x<0 || x>int(*this)) return -1;
	if (int(s) == 0) {
		return STACK::operator[](x);
	}
	else {
		int t1 = STACK::operator int();
		int t2 = int(s);
		if (x < 0) {
			return -1;//确保数据不会包含-1，返回-1表示数据出错
		}
		else if (x < t2) {
			return s[t2 - 1 - x];
		}
		else if (x < t1 + t2) {
			return STACK::operator[](x - t2);
		}
		else {
			return -1;//表示数据超出队列所有元素
		}
	}
}
QUEUE& QUEUE::operator<<(int e) {	//将e入队列,并返回队列
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
QUEUE& QUEUE::operator>>(int &e) {//出队列到e,并返回队列
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
QUEUE& QUEUE::operator=(const QUEUE&q) { //赋q给队列,并返回被赋值的队列//深度赋值，深拷贝

	if (this != &q) {
		//STACK::STACK(q);//不能直接调用构造函数，会造成意料之外的事情，只是构造了一个常量对象
		STACK::operator=(q);
		s = q.s;
	}
	return *this;
}

QUEUE& QUEUE::operator=(QUEUE&&q) {//移动赋值
	if (this != &q) {
		STACK::operator=(q);
		s = move(q.s);
	}
	return *this;
}

void QUEUE::print() const {			//打印队列
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
QUEUE::~QUEUE() {					//销毁队列

	/*const_cast
	static_cast
	dynamic_cast*/

}
