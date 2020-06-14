#include<stdio.h>
#include<string.h>
#include<malloc.h>
#include<stdlib.h>
#include<string.h>

struct STACK {//ջ�ṹ����
	int  *elems;	//�����ڴ����ڴ��ջ��Ԫ��
	int   max;	//ջ�ܴ�ŵ����Ԫ�ظ���
	int   pos;	//ջʵ������Ԫ�ظ�����ջ��ʱpos=0;
};

FILE *fp;
void initSTACK(STACK *const p, int m);	//��ʼ��pָ���ջ�����m��Ԫ��
void initSTACK(STACK *const p, const STACK&s); //��ջs��ʼ��pָ���ջ
int  size(const STACK *const p);		//����pָ���ջ�����Ԫ�ظ���max
int  howMany(const STACK *const p);	//����pָ���ջ��ʵ��Ԫ�ظ���pos
int  getelem(const STACK *const p, int x);	//ȡ�±�x����ջԪ��
STACK *const push(STACK *const p, int e); 	//��e��ջ��������p
STACK *const pop(STACK *const p, int &e); 	//��ջ��e��������p
STACK *const assign(STACK*const p, const STACK&s); //��s��pָ��ջ,������p
void print(const STACK*const p);			//��ӡpָ���ջ
void destroySTACK(STACK*const p);		//����pָ���ջ

int main(int argc, char *argv[]) {
	int i = 0; int j = 0; int data; int sum = 0;//ʣ��Ԫ�ظ���
	int m = 0;//ջ��С
	struct STACK * p;//pָ��ǰջ
	struct STACK * q;//qָ���½�ջ
	struct STACK * temp;//qָ���½�ջ
	char filename[100];
	//�ļ����

	strcpy(filename, argv[0]);
	i = strlen(filename);
	filename[i - 3] = 't'; filename[i - 2] = 'x'; filename[i - 1] = 't';
	fp = fopen(filename, "w+");

	p = (STACK*)malloc(sizeof(STACK));//ָ��pָ��ջ�ռ�
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

void initSTACK(STACK *const p, int m) {//��ʼ��pָ�������ջ�����Ϊm��Ԫ��
	p->max = m;
	p->pos = 0;
	free(p->elems);
	if (p->elems == NULL) {
		p->elems = (int *)malloc(m * sizeof(int));
	}
}
void initSTACK(STACK *const p, const STACK&s) {//��ջs��ʼ��pָ���ջ,��������ٿ���һ���ڴ�
	int i = 0;
	p->max = s.max;
	p->pos = s.pos;
	if (p->elems == NULL) {
		p->elems = (int *)malloc(p->max * sizeof(int));
	}
	if (p->elems) {
		for (; i < p->max; i++) {
			p->elems[i] = s.elems[i];//��ֵ
		}
	}
}
int  size(const STACK *const p) {//����pָ���ջ�����Ԫ�ظ���max,����ж�ָ���Ƿ�Ϊ��
	if (p != NULL) {
		return p->max;
	}
}
int  howMany(const STACK *const p) {//����pָ���ջ��ʵ��Ԫ�ظ���pos
	if (p != NULL) {
		return p->pos;
	}
}
int  getelem(const STACK *const p, int x) {//�õ��±�Ϊx��Ԫ��
	if (p != NULL) {
		if (0 <= x && x < p->pos) {
			return p->elems[x];
		}
		else {
			return -2147483648;//��Խ���򷵻ظ���������Ӧ��������ж�
		}
	}
}
STACK *const push(STACK *const p, int e) {//��eѹջ
	if (p != NULL) {
		if (p->max == 0 || p->pos == p->max) return NULL;//���ؿձ�ʾջ�ջ���ջ��ʱ��ջ������,����ʱ���E����Ļ
		else {
			p->elems[p->pos] = e;
			p->pos++;
			return p;
		}
	}
}
STACK *const pop(STACK *const p, int &e) {//��ջ��e
	if (p != NULL) {
		if (p->max == 0 || p->pos == 0) return NULL;//���ؿ�ֵ��ʾջ�ճ�ջ
		else {
			p->pos--;
			e = p->elems[p->pos];
			return p;
		}
	}
}
//����Ϊ�����ֵ������
STACK *const assign(STACK*const p, const STACK&s) {//��s��pָ��ջ,������p    Ҫ��������ٿ���һ���ڴ棿��
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
}			//��ӡpָ���ջ
void destroySTACK(STACK*const p) {//����pָ���ջ
	if (p != NULL) {
		if (p->elems != NULL) {
			free(p->elems);
			p->elems = NULL;
			p->max = 0;
			p->pos = 0;
		}
	}
}