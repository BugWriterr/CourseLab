#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<cstring>
#include"STACK.h"
#include"QUEUE.h"

//p为空时，即栈还没定义初始化，进行操作应输出ERROR

//考虑-C复制拷贝即深拷贝赋值的实现，但是又需要用到移动赋值
//-A 赋值，深度拷贝

using namespace std;
FILE *fp = NULL;//文件指针

int main(int argc, char *argv[]) {
	if (argc>1) {
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

		QUEUE* p = NULL;//p指向当前操作的队列
		QUEUE* q = NULL;//q指向-A -C操作的时候的队列
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
	else {
	int m, f;
	int M, F;
	cout << "Please input the male's number:" << endl;
	cin >> M;
	cout << "And please input the female's number again:" << endl;
	cin >> F;
	QUEUE male(M);
	QUEUE female(F);

	int count = 0;//计数器

	int i = 0;
	int data1;
	int data2;
	cout << "请输入男生在的位置m:" << endl;
	cin >> m;
	cout << "请输入女生在的位置f:" << endl;
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
	} while (data1 == 0 || data2 == 0);//没有同时到该男生和女生继续循环

	cout << count;
	system("pause");

	return 0;
}
	
}