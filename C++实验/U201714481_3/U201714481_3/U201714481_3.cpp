#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<cstring>
#include"STACK_1.h"

//pΪ��ʱ����ջ��û�����ʼ�������в���Ӧ���ERROR

//����-C���ƿ����������ֵ��ʵ�֣���������Ҫ�õ��ƶ���ֵ
//-A ��ֵ����ȿ���

using namespace std;
FILE *fp = NULL;//�ļ�ָ��
class QUEUE {
	STACK s1, s2;
public:
	QUEUE(int m); //ÿ��ջ���m��Ԫ�أ�Ҫ��ʵ�ֵĶ����������2m��Ԫ��
	QUEUE(const QUEUE&q); 			//�ö���q������ʼ������
	QUEUE(QUEUE&&q);				//�ƶ�����
	virtual operator int() const;			//���ض��е�ʵ��Ԫ�ظ���
	virtual int full() const;		       //���ض����Ƿ�������������1�����򷵻�0
	virtual int operator[ ](int x)const;   //ȡ�±�Ϊx��Ԫ��,��1��Ԫ���±�Ϊ0
	virtual QUEUE& operator<<(int e); 	//��e�����,�����ض���
	virtual QUEUE& operator>>(int &e);	//�����е�e,�����ض���
	virtual QUEUE& operator=(const QUEUE&q); //��q������,�����ر���ֵ�Ķ���
	virtual QUEUE& operator=(QUEUE&&q);	//�ƶ���ֵ
	virtual void print() const;			//��ӡ����
	virtual ~QUEUE();					//���ٶ���
};
//������ʼ���б�ʵ�ֹ��캯���ͳ�ʼ��
QUEUE::QUEUE(int m) :s1(m), s2(m) {//ÿ��ջ���m��Ԫ�أ�Ҫ��ʵ�ֵĶ����������2m��Ԫ��

}
QUEUE::QUEUE(const QUEUE &q) : s1(q.s1), s2(q.s2) {//�ö���q������ʼ������

}
QUEUE::QUEUE(QUEUE&&q) : s1(move(q.s1)), s2(move(q.s2))//�ƶ�����//
{

}
QUEUE::operator int() const {			//���ض��е�ʵ��Ԫ�ظ���
	return int(s1) + int(s2);
}
int QUEUE::full()const { //���ض����Ƿ�������������1�����򷵻�0
	if (int(s1) == s1.size() && int(s2)) return 1;
	else return 0;
}
int QUEUE::operator[](int x)const {//ȡ�±�Ϊx��Ԫ��,��1��Ԫ���±�Ϊ0
	if (x<0 || x>int(*this)) return -1;
	if (int(s2) == 0) {
		return s1[x];;
	}
	else {
		int t1 = int(s1);
		int t2 = int(s2);
		if (x < 0) {
			return -1;//ȷ�����ݲ������-1������-1��ʾ���ݳ���
		}
		else if (x < t2) {
			return s2[t2 - 1 - x];
		}
		else if (x < t1 + t2) {
			return s1[x - t2];
		}
		else {
			return -1;//��ʾ���ݳ�����������Ԫ��
		}
	}
}
QUEUE& QUEUE::operator<<(int e) {	//��e�����,�����ض���
	int i = 0; int j = int(s1); int data;
	if (this->full() == 0) {//����δ��
		if (j == s1.size()) {//s1����
			while (i < j) {//��s1����Ԫ�س�ջ��s2
				s1 >> data;
				s2 << data;
				i++;
			}
			s1 << e;//Ȼ��eѹջ
		}
		else {
			s1 << e;//ֱ�ӽ�eѹջ
		}
	}
	return *this;
}
QUEUE& QUEUE::operator>>(int &e) {//�����е�e,�����ض���
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
QUEUE& QUEUE::operator=(const QUEUE&q) { //��q������,�����ر���ֵ�Ķ���//��ȸ�ֵ�����

	if (this != &q) {
		s1 = q.s1;
		s2 = q.s2;
	}
	return *this;
}

QUEUE& QUEUE::operator=(QUEUE&&q) {//�ƶ���ֵ
	if (this != &q) {
		s1 = move(q.s1);
		s2 = move(q.s2);
	}
	return *this;
}

void QUEUE:: print() const {			//��ӡ����
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
QUEUE::~QUEUE() {					//���ٶ���
}


int main(int argc, char *argv[]) {
	
	int i = 0; int j = 0; int data;//ѹջ����
	int sum = 0;//ʣ��Ԫ�ظ���
	int m = 0;//ջ��С
	int flag = 0;

	//�ļ����
	char filename[100];
	strcpy(filename, argv[0]);
	i = strlen(filename);
	filename[i - 3] = 't'; filename[i - 2] = 'x'; filename[i - 1] = 't';
	fp = fopen(filename, "w+");
	//

	QUEUE *p = NULL;//pָ��ǰ�����Ķ���
	QUEUE *q = NULL;//qָ��-A -C������ʱ��Ķ���
	for (i = 1; i < argc; i++) {
		flag = 0;//�ж��Ƿ����
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
				q = new	QUEUE(*p);//���һ����ջ��qָ���ָ��
				p->~QUEUE();
				p = q;
				q = NULL;
				p->print();
				break;
			case 'A':

				printf("A  "); fprintf(fp, "A  ");
				m = atoi(argv[++i]);


				//�ƶ�����
				/*q = new QUEUE(m);//����һ����ջ����СΪm
								//������Ҫ���ǰѾ�ջ������ջ������ֻ��Ҫ�ƶ�����
				*q = (move(*p));
				p = q;
				q = NULL;*/


				//�������
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