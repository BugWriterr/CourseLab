#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<cstring>
#include"STACK_1.h"

//p为空时，即栈还没定义初始化，进行操作应输出ERROR

//本次实验中需要考虑右值引用是什么意思
//考虑-C复制拷贝即深拷贝赋值的实现，但是又需要用到移动赋值
//-A 赋值，深度拷贝
using namespace std;
FILE *fp=NULL;//文件指针



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

	STACK *p = NULL;//p为指向当前操作栈的对象
	STACK *q = NULL;//为-A -C操作建立的对象
	for (i = 1; i < argc; i++) {
		flag = 0;//判断是否出错
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
				q = new STACK(*p);//深拷贝一个新栈，q指向该指针
				p->~STACK();
				p = q;
				q = NULL;
				p->print();
				break;
			case 'A':

				printf("A  "); fprintf(fp, "A  ");
				m = atoi(argv[++i]);
				//移动复制
				/*q = new STACK(m);//构造一个新栈，大小为m
								//接下来要考虑把旧栈赋给新栈，或许只需要移动复制
				*q = (move(*p));
				p = q;
				q = NULL;*/
				//深拷贝复制
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