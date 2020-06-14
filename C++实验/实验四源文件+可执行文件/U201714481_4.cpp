#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<cstring>
#include"STACK.h"
#include"QUEUE.h"

//pΪ��ʱ����ջ��û�����ʼ�������в���Ӧ���ERROR

//����-C���ƿ����������ֵ��ʵ�֣���������Ҫ�õ��ƶ���ֵ
//-A ��ֵ����ȿ���

using namespace std;
FILE *fp = NULL;//�ļ�ָ��

int main(int argc, char *argv[]) {
	if (argc>1) {
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

		QUEUE* p = NULL;//pָ��ǰ�����Ķ���
		QUEUE* q = NULL;//qָ��-A -C������ʱ��Ķ���
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
					while (i < argc && argv[i][0] != '-') {
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
	else {
	int m, f;
	int M, F;
	cout << "Please input the male's number:" << endl;
	cin >> M;
	cout << "And please input the female's number again:" << endl;
	cin >> F;
	QUEUE male(M);
	QUEUE female(F);

	int count = 0;//������

	int i = 0;
	int data1;
	int data2;
	cout << "�����������ڵ�λ��m:" << endl;
	cin >> m;
	cout << "������Ů���ڵ�λ��f:" << endl;
	cin >> f;
	for (i = 1; i <= M; i++) {
		if (i == m)male << 1;
		else male << 0;
	}
	for (i = 1; i <= F; i++) {
		if (i == f) female << 1;
		else female << 0;
	}
	do {
		male >> data1;
		female >> data2;
		male << data1;
		female << data2;
		count++;
	} while (data1 == 0 || data2 == 0);//û��ͬʱ����������Ů������ѭ��

	cout << count;
	system("pause");

	return 0;
}
	
}