#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<cstring>
#include"STACK_1.h"

//p为空时，即栈还没定义初始化，进行操作应输出ERROR

//考虑-C复制拷贝即深拷贝赋值的实现，但是又需要用到移动赋值
//-A 赋值，深度拷贝

using namespace std;
FILE *fp = NULL;//文件指针
class QUEUE {
	STACK s1, s2;
public:
	QUEUE(int m); //每个栈最多m个元素，要求实现的队列最多能入2m个元素
	QUEUE(const QUEUE&q); 			//用队列q拷贝初始化队列
	QUEUE(QUEUE&&q);				//移动构造
	virtual operator int() const;			//返回队列的实际元素个数
	virtual int full() const;		       //返回队列是否已满，满返回1，否则返回0
	virtual int operator[ ](int x)const;   //取下标为x的元素,第1个元素下标为0
	virtual QUEUE& operator<<(int e); 	//将e入队列,并返回队列
	virtual QUEUE& operator>>(int &e);	//出队列到e,并返回队列
	virtual QUEUE& operator=(const QUEUE&q); //赋q给队列,并返回被赋值的队列
	virtual QUEUE& operator=(QUEUE&&q);	//移动赋值
	virtual void print() const;			//打印队列
	virtual ~QUEUE();					//销毁队列
};
//参数初始化列表实现构造函数和初始化
QUEUE::QUEUE(int m) :s1(m), s2(m) {//每个栈最多m个元素，要求实现的队列最多能入2m个元素

}
QUEUE::QUEUE(const QUEUE &q) : s1(q.s1), s2(q.s2) {//用队列q拷贝初始化队列

}
QUEUE::QUEUE(QUEUE&&q) : s1(move(q.s1)), s2(move(q.s2))//移动构造//
{

}
QUEUE::operator int() const {			//返回队列的实际元素个数
	return int(s1) + int(s2);
}
int QUEUE::full()const { //返回队列是否已满，满返回1，否则返回0
	if (int(s1) == s1.size() && int(s2)) return 1;
	else return 0;
}
int QUEUE::operator[](int x)const {//取下标为x的元素,第1个元素下标为0
	if (x<0 || x>int(*this)) return -1;
	if (int(s2) == 0) {
		return s1[x];;
	}
	else {
		int t1 = int(s1);
		int t2 = int(s2);
		if (x < 0) {
			return -1;//确保数据不会包含-1，返回-1表示数据出错
		}
		else if (x < t2) {
			return s2[t2 - 1 - x];
		}
		else if (x < t1 + t2) {
			return s1[x - t2];
		}
		else {
			return -1;//表示数据超出队列所有元素
		}
	}
}
QUEUE& QUEUE::operator<<(int e) {	//将e入队列,并返回队列
	int i = 0; int j = int(s1); int data;
	if (this->full() == 0) {//队列未满
		if (j == s1.size()) {//s1满了
			while (i < j) {//则将s1所有元素出栈至s2
				s1 >> data;
				s2 << data;
				i++;
			}
			s1 << e;//然后将e压栈
		}
		else {
			s1 << e;//直接将e压栈
		}
	}
	return *this;
}
QUEUE& QUEUE::operator>>(int &e) {//出队列到e,并返回队列
	int i = 0; int j = int(s1); int data;
	if ((int(s1) + int(s2)) != 0) {
		if (int(s2) == 0) {
			while (i < j) {
				s1 >> data;
				s2 << data;
				i++;
			}
			s2 >> e;
		}
		else {
			s2 >> e;
		}
	}
	return *this;
}
QUEUE& QUEUE::operator=(const QUEUE&q) { //赋q给队列,并返回被赋值的队列//深度赋值，深拷贝

	if (this != &q) {
		s1 = q.s1;
		s2 = q.s2;
	}
	return *this;
}

QUEUE& QUEUE::operator=(QUEUE&&q) {//移动赋值
	if (this != &q) {
		s1 = move(q.s1);
		s2 = move(q.s2);
	}
	return *this;
}

void QUEUE:: print() const {			//打印队列
	int i = 0;
	int j = int(s1);
	int k = int(s2);
	int data = 0;
	for (; i < k; i++) {
		data = s2[k - i - 1];
		printf("%d  ", data);
		fprintf(fp, "%d  ", data);
	}
	s1.print();
}
QUEUE::~QUEUE() {					//销毁队列
}


int main(int argc, char *argv[]) {
	
	int i = 0; int j = 0; int data;//压栈数据
	int sum = 0;//剩余元素个数
	int m = 0;//栈大小
	int flag = 0;

	//文件输出
	char filename[100];
	strcpy(filename, argv[0]);
	i = strlen(filename);
	filename[i - 3] = 't'; filename[i - 2] = 'x'; filename[i - 1] = 't';
	fp = fopen(filename, "w+");
	//

	QUEUE *p = NULL;//p指向当前操作的队列
	QUEUE *q = NULL;//q指向-A -C操作的时候的队列
	for (i = 1; i < argc; i++) {
		flag = 0;//判断是否出错
		if (argv[i][0] == '-') {
			switch (argv[i][1])
			{
			case 'S':

				m = atoi(argv[++i]);
				p = new QUEUE(m);
				printf("S  %d  ", m); fprintf(fp, "S  %d  ", m);
				break;

			case 'I':

				printf("I  "); fprintf(fp, "I  "); i++;
				while (i < argc&&argv[i][0] != '-') {
					data = atoi(argv[i++]);
					if (p->full()) {
						flag = 1;
						break;
					}
					else
					{
						(*p) << data;
					}
				}
				if (flag == 0) {
					p->print();
					i--;
				}
				else {
					printf("E  "); fprintf(fp, "E  "); i = argc;
				}
				break;
			case 'O':
				printf("O  "); fprintf(fp, "O  ");
				j = 0; m = atoi(argv[++i]);
				if (m <= int(*p)) {
					for (; j < m; j++) {
						*p >> data;
					}
				}
				else
				{
					flag = 1;
					printf("E  "); fprintf(fp, "E  "); i = argc;
				}
				if (flag == 0) {
					p->print();
				}
				break;
			case 'C':

				printf("C  "); fprintf(fp, "C  ");
				q = new	QUEUE(*p);//深拷贝一个新栈，q指向该指针
				p->~QUEUE();
				p = q;
				q = NULL;
				p->print();
				break;
			case 'A':

				printf("A  "); fprintf(fp, "A  ");
				m = atoi(argv[++i]);


				//移动复制
				/*q = new QUEUE(m);//构造一个新栈，大小为m
								//接下来要考虑把旧栈赋给新栈，或许只需要移动复制
				*q = (move(*p));
				p = q;
				q = NULL;*/


				//深拷贝复制
				q = new QUEUE(m);
				(*q) = (*p);
				p = q;
				q = NULL;
				p->print();
				break;

			case 'N':
				sum = int((*p));
				printf("N  %d  ", sum); fprintf(fp, "N  %d  ", sum);
				break;
			case 'G':
				m = atoi(argv[++i]);
				if (m >= int((*p)) || data == -1) {
					printf("G  E  ");
					fprintf(fp, "G  E  ");
					i = argc;
				}
				else {
					data = (*p)[m];
					printf("G  %d  ", data);
					fprintf(fp, "G  %d  ", data);
				}
				break;
			}
		}
	}
	fclose(fp);
	delete(p);
	delete(q);
	system("pause");
	return 0;
}