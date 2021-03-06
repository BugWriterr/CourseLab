#include"STACK.h"
#include<iostream>

extern FILE*fp;


STACK::STACK(int m) :max(m), elems(new int[m])//初始化栈：最多存m个元素
{
	this->pos = 0;
}
STACK::STACK(const STACK &s) : max(s.max), elems(new int[s.max]) {//用栈s拷贝初始化栈
	int i = 0;
	if (elems&&s.elems) {
		for (; i < s.max; i++) {
			this->elems[i] = s.elems[i];
		}
		pos = s.pos;
	}
}
STACK::STACK(STACK&&s) :max(s.max), elems(s.elems) {//移动构造
	pos = s.pos;
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
	else return -2147473648;
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
		if (s.elems == NULL) {
			if (elems) {
				delete(elems);
				*q = NULL;
				pos = s.pos;
				*p = s.max;
				return *this;
			}
		}
		else {
			if (s.max <= max) {
				for (; i < s.max; i++) {
					elems[i] = s.elems[i];
				}
			}
			else {
				delete(elems);
				(*q) = new int[s.max];
				for (; i < s.max; i++) {
					elems[i] = s.elems[i];
				}
				pos = s.pos;
				*p = s.max;
				return *this;
			}
		}
	}
}
STACK & STACK::operator=(STACK&&s) {  //移动赋值
	int *p = (int *)&max;
	*p = s.max;
	pos = s.pos;
	int **q = (int **)&elems;
	(*q) = s.elems;
	return *this;
}


void STACK::print() const {//遍历栈
	int i = 0;
	if (this&&max > 0 && elems) {
		for (; i < pos; i++) {
			//cout << elems[i] << "  ";
			printf("%d  ", elems[i]);
			fprintf(fp, "%d  ", elems[i]);
		}
	}
}
STACK::~STACK() {//析构函数
	if (elems) {
		delete(elems);
	}
	int **t1 = (int **)&elems;
	(*t1) = NULL;
	pos = 0;
	int *t = (int *)&max;
	*t = 0;
}