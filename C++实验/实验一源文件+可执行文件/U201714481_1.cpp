#include<stdio.h>
#include<string.h>
#include<malloc.h>
#include<stdlib.h>
#include<string.h>

struct STACK {//栈结构定义
	int  *elems;	//申请内存用于存放栈的元素
	int   max;	//栈能存放的最大元素个数
	int   pos;	//栈实际已有元素个数，栈空时pos=0;
};

FILE *fp;
void initSTACK(STACK *const p, int m);	//初始化p指向的栈：最多m个元素
void initSTACK(STACK *const p, const STACK&s); //用栈s初始化p指向的栈
int  size(const STACK *const p);		//返回p指向的栈的最大元素个数max
int  howMany(const STACK *const p);	//返回p指向的栈的实际元素个数pos
int  getelem(const STACK *const p, int x);	//取下标x处的栈元素
STACK *const push(STACK *const p, int e); 	//将e入栈，并返回p
STACK *const pop(STACK *const p, int &e); 	//出栈到e，并返回p
STACK *const assign(STACK*const p, const STACK&s); //赋s给p指的栈,并返回p
void print(const STACK*const p);			//打印p指向的栈
void destroySTACK(STACK*const p);		//销毁p指向的栈

int main(int argc, char *argv[]) {
	int i = 0; int j = 0; int data; int sum = 0;//剩余元素个数
	int m = 0;//栈大小
	struct STACK * p;//p指向当前栈
	struct STACK * q;//q指向新建栈
	struct STACK * temp;//q指向新建栈
	char filename[100];
	//文件输出

	strcpy(filename, argv[0]);
	i = strlen(filename);
	filename[i - 3] = 't'; filename[i - 2] = 'x'; filename[i - 1] = 't';
	fp = fopen(filename, "w+");

	p = (STACK*)malloc(sizeof(STACK));//指针p指向栈空间
	p->elems = NULL;
	p->max = p->pos = 0;
	q = (STACK*)malloc(sizeof(STACK));
	temp = NULL;
	q->elems = NULL;
	q->max = q->pos = 0;
	for (i = 1; i < argc; i++) {
		if (argv[i][0] == '-') {
			switch (argv[i][1])
			{
			case 'S':
				m = atoi(argv[++i]);
				initSTACK(p, m);
				printf("S  %d  ", m); fprintf(fp, "S  %d  ", m);
				break;
			case 'I':
				printf("I  "); fprintf(fp, "I  "); i++;
				while (i < argc&&argv[i][0] != '-') {
					data = atoi(argv[i]);
					p = push(p, data);
					i++;
					if (p == NULL)break;
				}
				if (p != NULL) {
					print(p); i--;
				}
				else {
					printf("E  "); fprintf(fp, "E  "); i = argc;
				}
				break;
			case 'O':
				printf("O  "); fprintf(fp, "O  ");
				j = 0; m = atoi(argv[++i]);
				for (; j < m; j++) {
					p = pop(p, data);
					if (p == NULL) break;
				}
				if (p != NULL) {
					print(p);
				}
				else
				{
					printf("E  "); fprintf(fp, "E  "); i = argc;
				}
				break;
			case 'C':
				printf("C  "); fprintf(fp, "C  ");
				initSTACK(q, *p);
				free(p->elems);
				free(p);
				p = q;
				q = (STACK*)malloc(sizeof(STACK));
				q->elems = NULL;
				q->max = q->pos = 0;
				print(p);
				break;
			case 'A':
				printf("A  "); fprintf(fp, "A  ");
				temp = assign(q, *p);
				free(p->elems);
				free(p);
				p = temp;
				temp = NULL;
				print(p);
				break;
			case 'N':
				sum = howMany(p);
				printf("N  %d  ", sum); fprintf(fp, "N  %d  ", sum);
				break;
			case 'G':
				m = atoi(argv[++i]);
				data = getelem(p, m);
				if (m >= p->pos || data == -2147483648) {
					printf("G  E  ");
					fprintf(fp, "G  E  ");
					i = argc;
				}
				else {
					printf("G  %d  ", data);
					fprintf(fp, "G  %d  ", data);
				}
				break;
			}
		}
	}
	destroySTACK(p);
	fclose(fp);
	return 0;
}

void initSTACK(STACK *const p, int m) {//初始化p指向的整形栈，最大为m个元素
	p->max = m;
	p->pos = 0;
	free(p->elems);
	if (p->elems == NULL) {
		p->elems = (int *)malloc(m * sizeof(int));
	}
}
void initSTACK(STACK *const p, const STACK&s) {//用栈s初始化p指向的栈,深拷贝，，再开辟一段内存
	int i = 0;
	p->max = s.max;
	p->pos = s.pos;
	if (p->elems == NULL) {
		p->elems = (int *)malloc(p->max * sizeof(int));
	}
	if (p->elems) {
		for (; i < p->max; i++) {
			p->elems[i] = s.elems[i];//赋值
		}
	}
}
int  size(const STACK *const p) {//返回p指向的栈的最大元素个数max,最好判断指针是否为空
	if (p != NULL) {
		return p->max;
	}
}
int  howMany(const STACK *const p) {//返回p指向的栈的实际元素个数pos
	if (p != NULL) {
		return p->pos;
	}
}
int  getelem(const STACK *const p, int x) {//得到下标为x的元素
	if (p != NULL) {
		if (0 <= x && x < p->pos) {
			return p->elems[x];
		}
		else {
			return -2147483648;//若越界则返回该数，或许应该在外层判断
		}
	}
}
STACK *const push(STACK *const p, int e) {//将e压栈
	if (p != NULL) {
		if (p->max == 0 || p->pos == p->max) return NULL;//返回空表示栈空或者栈满时入栈，错误,错误时输出E到屏幕
		else {
			p->elems[p->pos] = e;
			p->pos++;
			return p;
		}
	}
}
STACK *const pop(STACK *const p, int &e) {//出栈到e
	if (p != NULL) {
		if (p->max == 0 || p->pos == 0) return NULL;//返回空值表示栈空出栈
		else {
			p->pos--;
			e = p->elems[p->pos];
			return p;
		}
	}
}
//下面为深拷贝赋值函数，
STACK *const assign(STACK*const p, const STACK&s) {//赋s给p指的栈,并返回p    要求深拷贝，再开辟一段内存？？
	int i = 0;
	p->max = s.max;
	p->pos = s.pos;
	if (p->elems != s.elems) {
		if (p->elems) free(p->elems);
		p->elems = (int *)malloc(sizeof(int)*p->max);
	}
	for (i = 0; i < p->pos; i++) {
		p->elems[i] = s.elems[i];
	}
	return p;
}
void print(const STACK*const p) {
	int i = 0;
	if (p != NULL)
		for (; i < p->pos; i++) {
			printf("%d  ", p->elems[i]);
			fprintf(fp, "%d  ", p->elems[i]);
		}
}			//打印p指向的栈
void destroySTACK(STACK*const p) {//销毁p指向的栈
	if (p != NULL) {
		if (p->elems != NULL) {
			free(p->elems);
			p->elems = NULL;
			p->max = 0;
			p->pos = 0;
		}
	}
}