#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<cstring>
#include"STACK_1.h"

//pΪ��ʱ����ջ��û�����ʼ�������в���Ӧ���ERROR

//����ʵ������Ҫ������ֵ������ʲô��˼
//����-C���ƿ����������ֵ��ʵ�֣���������Ҫ�õ��ƶ���ֵ
//-A ��ֵ����ȿ���
using namespace std;
FILE *fp=NULL;//�ļ�ָ��



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

	STACK *p = NULL;//pΪָ��ǰ����ջ�Ķ���
	STACK *q = NULL;//Ϊ-A -C���������Ķ���
	for (i = 1; i < argc; i++) {
		flag = 0;//�ж��Ƿ����
		if (argv[i][0] == '-') {
			switch (argv[i][1])
			{
			case 'S':
		
				m = atoi(argv[++i]);
				p = new STACK(m);
				printf("S  %d  ", m); fprintf(fp, "S  %d  ", m);
				break;

			case 'I':

				printf("I  "); fprintf(fp, "I  "); i++;
				while (i < argc&&argv[i][0] != '-') {
					data = atoi(argv[i++]);
					int k = p->size();
					if (k > 0 && int(*p) < k)
						(*p)<< data;
					else
					{
						flag = 1;
						break;
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
				for (; j < m; j++) {
					if (((*p).size())<= 0 || int((*p)) <= 0) { flag = 1; }
					else {
						(*p) >> data;
					}
					if (flag==1) break;
				}
				if (flag==0) {
					(*p).print();
				}
				else
				{
					printf("E  "); fprintf(fp, "E  "); i = argc;
				}
				break;
			case 'C':

				printf("C  "); fprintf(fp, "C  ");
				q = new STACK(*p);//���һ����ջ��qָ���ָ��
				p->~STACK();
				p = q;
				q = NULL;
				p->print();
				break;
			case 'A':

				printf("A  "); fprintf(fp, "A  ");
				m = atoi(argv[++i]);
				//�ƶ�����
				/*q = new STACK(m);//����һ����ջ����СΪm
								//������Ҫ���ǰѾ�ջ������ջ������ֻ��Ҫ�ƶ�����
				*q = (move(*p));
				p = q;
				q = NULL;*/
				//�������
				q = new STACK(m);
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
				if (m >= int((*p)) || data == -2147483648) {
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