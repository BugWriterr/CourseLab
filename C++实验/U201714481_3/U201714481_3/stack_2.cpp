#include"STACK_1.h"
#include<stdio.h>
#include<iostream>
#include<stdlib.h>
#include<cstring>

using namespace std;

extern FILE* fp;



STACK::STACK(int m) : elems(new int[m]), max(elems ? m : 0)//初始化栈：最多存m个元素
{
	this->pos = 0;
}
STACK::STACK(const STACK &s) : elems(new int[s.max]), max(elems ? s.max : 0) {//用栈s拷贝初始化栈
	int i = 0;
	if (elems&&s.elems) {
		for (; i < s.pos; i++) {
			this->elems[i] = s.elems[i];
		}
		pos = s.pos;
	}
}

STACK::STACK(STACK&&s) :max(s.max), elems(s.elems) {//移动构造
	pos = s.pos;
	*(int**)&s.elems = nullptr;//强制类型转换将更改数据值
	//(int &)s.elems = NULL;

}
int STACK::size() const {//返回栈的最大元素个数max
	return max;
}
STACK::operator int() const {//返回栈的实际元素个数pos
	return pos;
}
int STACK::operator [](int x)const {//取下标x处的栈元素，第1个元素x=0
	if (0 <= x && x < pos) {
		return elems[x];
	}
	else return -2147473648;//返回一个特殊值代表出错
}
STACK& STACK::operator<<(int e) {//将e入栈并返回栈
	if (max > 0 && pos < max) {
		elems[pos] = e;
		++pos;
	}
	return *this;
}
STACK& STACK::operator>>(int &e) {//出栈到e,并返回栈
	if (max > 0 && pos > 0 && pos <= max) {
		pos--;
		e = elems[pos];
	}
	return *this;
}

STACK& STACK::operator=(const STACK&s)
{//赋s给栈,并返回被赋值栈
	int *p = (int *)&max;
	int **q = (int **)&elems;
	int i = 0;

	if (elems == s.elems) //如果两个栈相同
	{
		return *this;
	}
	else {
		if (elems) {
			delete[] elems;
			*q = NULL;
		}
		if (s.elems != NULL) {
			(*q) = new int[s.max];
			for (i = 0; i < s.pos; i++) {
				elems[i] = s.elems[i];
			}
		}
		pos = s.pos;
		*p = s.max;//对max进行更改
		return *this;
	}
}
STACK & STACK::operator=(STACK&&s) {  //移动赋值
	int *p = (int *)&max;
	*p = s.max;
	pos = s.pos;
	int **q = (int **)&elems;
	(*q) = s.elems;
	*(int **)&s.elems = NULL;
	//(int &)s.elems = NULL;//一定要将s的elems置为空

	return *this;
}


void STACK::print() const {//遍历栈
	int i = 0;
	if (this&&max > 0 && elems) {
		for (; i < pos; i++) {
			cout << elems[i] << "  ";
			fprintf(fp, "%d  ", elems[i]);
		}
	}
}
STACK::~STACK() {//析构函数
	if (elems) {
		delete[] elems;
	}
	*(int **)&elems = NULL;
	pos = 0;
	*(int **)&max = 0;
}