#include"STACK_1.h"
#include<stdio.h>
#include<iostream>
#include<stdlib.h>
#include<cstring>

using namespace std;

extern FILE* fp;



STACK::STACK(int m) : elems(new int[m]), max(elems ? m : 0)//��ʼ��ջ������m��Ԫ��
{
	this->pos = 0;
}
STACK::STACK(const STACK &s) : elems(new int[s.max]), max(elems ? s.max : 0) {//��ջs������ʼ��ջ
	int i = 0;
	if (elems&&s.elems) {
		for (; i < s.pos; i++) {
			this->elems[i] = s.elems[i];
		}
		pos = s.pos;
	}
}

STACK::STACK(STACK&&s) :max(s.max), elems(s.elems) {//�ƶ�����
	pos = s.pos;
	*(int**)&s.elems = nullptr;//ǿ������ת������������ֵ
	//(int &)s.elems = NULL;

}
int STACK::size() const {//����ջ�����Ԫ�ظ���max
	return max;
}
STACK::operator int() const {//����ջ��ʵ��Ԫ�ظ���pos
	return pos;
}
int STACK::operator [](int x)const {//ȡ�±�x����ջԪ�أ���1��Ԫ��x=0
	if (0 <= x && x < pos) {
		return elems[x];
	}
	else return -2147473648;//����һ������ֵ�������
}
STACK& STACK::operator<<(int e) {//��e��ջ������ջ
	if (max > 0 && pos < max) {
		elems[pos] = e;
		++pos;
	}
	return *this;
}
STACK& STACK::operator>>(int &e) {//��ջ��e,������ջ
	if (max > 0 && pos > 0 && pos <= max) {
		pos--;
		e = elems[pos];
	}
	return *this;
}

STACK& STACK::operator=(const STACK&s)
{//��s��ջ,�����ر���ֵջ
	int *p = (int *)&max;
	int **q = (int **)&elems;
	int i = 0;

	if (elems == s.elems) //�������ջ��ͬ
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
		*p = s.max;//��max���и���
		return *this;
	}
}
STACK & STACK::operator=(STACK&&s) {  //�ƶ���ֵ
	int *p = (int *)&max;
	*p = s.max;
	pos = s.pos;
	int **q = (int **)&elems;
	(*q) = s.elems;
	*(int **)&s.elems = NULL;
	//(int &)s.elems = NULL;//һ��Ҫ��s��elems��Ϊ��

	return *this;
}


void STACK::print() const {//����ջ
	int i = 0;
	if (this&&max > 0 && elems) {
		for (; i < pos; i++) {
			cout << elems[i] << "  ";
			fprintf(fp, "%d  ", elems[i]);
		}
	}
}
STACK::~STACK() {//��������
	if (elems) {
		delete[] elems;
	}
	*(int **)&elems = NULL;
	pos = 0;
	*(int **)&max = 0;
}