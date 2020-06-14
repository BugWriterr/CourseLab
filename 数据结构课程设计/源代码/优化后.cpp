#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include<time.h>
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
typedef int status;
typedef struct root {//��
	int varnum;//��Ԫ�� 
	int calnum;//�Ӿ��� 
	struct clause* fircal;//ָ���һ���Ӿ� 
}*Root;//������ 

typedef struct clause {//�Ӿ�ͷ 
	int litnum;//���Ӿ��Ԫ����
	struct clause* nextcal;//ָ����һ���Ӿ� 
	struct literal* first;//ָ���һ������ 
	int clamark;//����Ӿ��Ƿ�ɾ�� 
}clause;//�Ӿ����� 

typedef struct literal {//����
	int liter;//��Ԫ
	struct literal* next;//ָ����һ������ 
	int litmark;//����Ƿ�ɾ��
}literal;//�������� 

typedef struct word {//��Ԫ�� 
	clause *clahead;//ָ��ñ�Ԫ���ڵ��Ӿ�ͷ 
	literal* liter;//ָ��ñ�Ԫ���ڵ����� 
	int L;//�ñ�Ԫ���ڵ��Ӿ���� 
	word *next;//ָ����һ����ͬ��Ԫ 
}word, *Word;//��Ԫ������ 

typedef struct stack {//ջ���������ʱʹ�� 
	int literal;//���븳ֵ��ֵ 
	int value;//��Ԫ��ֵ 
}*Stack;//ջָ�룬��̬�������� 
status Loadcnf(char*filename, Root* root, int flag);//����cnf�ļ�
status Testcnf(Root root);//���Խ����Ƿ���ȷ
status DPLL(Root root, int *valuation);//DPLL�㷨 
status evaluateClause(Root root, int L, int *value);//�жϹ�ʽ�Ƿ���ڳ�ͻ 
status createsudoku();//������Ϸ���㷨�Զ�����������֣�ͬʱ�������������˻����� 
status savefile(char *filename, int *valuation, Root root, int flag, double t);//��������������res�ļ���
int variable_decide(Root root, int *valuation);//���߱�����ѡȡ���Ӿ���߳�������Ӿ��һ����Ԫ 
void liternum(Root root, Word *lb);//������������Ԫ��ͬʱͳ��ÿ���Ӿ��Ԫ���� 
void cnfdeduce(Root *root, int L, int flag, Word *lb);//����cnf��ʽ��ɾ�� 
void cnfrestore(Root *root, int L, Word *lb);//����cnf��ʽ������ʱ 
int sudoku[9][9];//������� 
int litnum[10000000];//�Ӿ�������˹��趨�����Ӿ�������ڣ������������С 
int main(void) {
	clock_t start, finish;//ʱ��
	double tim, tim2;
	tim2=0; 
	int op = 1;
	int i = 0;
	int j, k, w; int oooo = 0;
	int flag; int select = 0;
	char filename[60];
	FILE*fp;
	while (op) {
		system("cls");	printf("\n\n");
		printf("      Menu for �ۺϿ��� \n");
		printf("-------------------------------------------------\n");
		printf("    	  1. SAT       2. sudoku\n    	  0.EXIT\n");
		scanf("%d", &op);
		switch (op) {
		case 1:
			Root root;
			if (Loadcnf(filename, &root, 1)) {
				printf("�ù�ʽ����%d����Ԫ�� %d���Ӿ䣡\n", root->varnum, root->calnum);
				printf("�Ƿ���Ҫ��֤��\n1.YES    0.NO\n");
				scanf("%d", &select);
				if (select == 1) {
					printf("����س���ʼ��֤��\n");
					if (Testcnf(root))
						printf("������ɣ�\n");
				}
				getchar();
				printf("����س���ʼ��⣡\n");
				getchar();
				printf("���ing...\n");
			}
			else return 0;
			int *valuation;
			valuation = (int*)malloc(sizeof(int)*(root->varnum + 1));
			valuation[0] = root->varnum;
			for (i = 1; i <= root->varnum; i++) {
				valuation[i] = 0;
			}
			start = clock();
			printf("�ļ���%s\n",filename);
			if (DPLL(root, valuation)) {
				finish = clock();
				flag = 1;
				printf("SAT!\n");
			}
			else {
				flag = 0;
				finish = clock();
				printf("UNSAT��\n");
			}
			tim = (double)(finish - start);
			printf("DPLL��ִ��ʱ����%fms.\n", tim);
			printf("                %fs.\n", tim / CLK_TCK);
			printf("����Ҫ�����Ż��ʣ���ȷ����sat�����Ż�ǰ.cpp���У�\n");
			printf("�Ƿ��������Ҫ��\n0:NO(�������Ż���)   1.YES(������������Ż�ǰ������)\n");
			scanf("%d", &oooo);
			if (oooo) {
				if(fp = fopen("t.txt", "r")){
				fscanf(fp, "%lf", &tim2);
				}
				else {
					printf("�Ż�ǰδ���С�\n");
				}
				fclose(fp);
				printf("�Ż�ǰ��ִ��ʱ��Ϊ%fms\n", tim2);
				if(tim2==0){
					printf("�Ż���Ϊ%f%%\n", (1 - tim) / 1.0 * 100);
				}
				else printf("�Ż���Ϊ%f%%\n", (tim2 - tim) / tim2 * 100);
				getchar();
			}
			savefile(filename, valuation, root, flag, tim);
			getchar();
			break;
		case 2:
			if (createsudoku()) {
				printf("GAME OVER��\n");
			}
			getchar();
			break;
		case 0:
			break;
		}
	}
	printf("��ӭ�ٴ����鱾ϵͳ��\n");
	return 0;
}

status DPLL(Root root, int *valuation) {//DPLL��SAT 
int t, flag, L;
int flag3=0; 
	int i = 0;
	int j = 0;
	flag = 1;
	Stack visit;//ջ
	Word lb;//�½�һ������
	lb = (Word)malloc(sizeof(word)*(2 * root->varnum + 1));//��Ԫ�� 
	visit = (Stack)malloc(sizeof(stack)*(root->varnum + 1));//ջ��������� 
	for (i = 0; i < root->varnum + 1; i++) {//��ʼ�� 
		visit[i].literal = 0;
		visit[i].value = 0;
		lb[i].clahead = NULL;
		lb[i].liter = NULL;
		lb[i].next = NULL;
		lb[i].L = 0;
	}
	for (i; i <= 2 * root->varnum; i++) {///��ʼ��
		lb[i].clahead = NULL;
		lb[i].liter = NULL;
		lb[i].next = NULL;
		lb[i].L = 0;
	}
	liternum(root, &lb);//������Ԫ�� 
	i = 0;
	L = variable_decide(root, valuation);//���߱��� 
	visit[i].literal = L;
	visit[i].value = valuation[L];
	i++; 
	while (1) {
		if (flag3!=-2&&evaluateClause(root, L, valuation)){//flag==-2��ʾ���ڿ��Ӿ䣬�ж��Ƿ���ڳ�ͻ 
			cnfdeduce(&root, L, valuation[L], &lb);//���� 
			if ((L = variable_decide(root, valuation))==-1) //����Ӿ伯Ϊ�գ���˵�������㣬 ������ڿ��Ӿ䣬L==-2, 
			return OK; //������ 
			else if(L!=-2){//L!=-2��˵�����߳���������ջ 
				visit[i].literal = L;
				visit[i].value = valuation[L];
				i++;
			}
			else{//���ڳ�ͻ 
				flag3=-2;//���п��Ӿ䣬������ 
			}
		}
		else {//���ݣ� 
			flag3=0;
			for (j = i - 1; j >= 0; j--) {
				t = visit[j].literal;
				if (visit[j].value == 0) {//ջ����0����˵���ѷ�ת�� 
					visit[j].value = 1;//�ָ� 
					valuation[t] = 1;
					valuation[0]++;
					if(j!=i-1)cnfrestore(&root, t,&lb);
					continue;
				}
				else if (visit[j].value == 1) {//ջ���һ��δ��ת���� 
					visit[j].value = 0;//��ת 
					valuation[t] = 0;
					L = t;
					if(j!=i-1)cnfrestore(&root, L,&lb);//�ָ� 
					i = j + 1;
					break;
				}
			}
			if (j == -1) return ERROR;
		}
	}
}

status evaluateClause(Root root, int L, int *value) {//�ж��Ƿ�һ�����ڳ�ͻ�����Ӿ��ͻ���п��Ӿ� 
	clause*p;
	literal*q;
	p = root->fircal;
	int i = 0;
	int t;
	for (i = 0; i < root->calnum; i++) {
		if (p->clamark == 0 && p->litnum == 1) {
			q = p->first;
			while (q) {
				if (q->litmark == 0) {
					t = q->liter;
					if (abs(t) == L) {
						if (t > 0 && value[L] == 0) return ERROR;
						else if (t < 0 && value[L]>0) return ERROR;
						break;
					}
					else break;
				}
				q = q->next;
			}
		}
		else if(p->litnum==0) return ERROR; 
		p = p->nextcal;
	}
	return OK;
}
void cnfrestore(Root *root, int L, Word *lb) {//�Ӿ�ָ�
	word *p, *q;
	clause*r;
	literal*t;
	p = (*lb)[L].next;
	q = (*lb)[L + (*root)->varnum].next;
	while (p) {
		r = p->clahead;
		t = p->liter;
		if (r->clamark == L)r->clamark = 0;
		if (t->litmark == L) {
			t->litmark = 0;
			r->litnum++;
			litnum[p->L]++;
		}
		p = p->next;
	}
	while (q) {
		r = q->clahead;
		t = q->liter;
		if (r->clamark == L)r->clamark = 0;
		if (t->litmark == L) {
			t->litmark = 0;
			r->litnum++;
			litnum[q->L]++;
		}
		q = q->next;
	}
}
void cnfdeduce(Root *root, int L, int flag, Word *lb) {//�Ӿ仯�� 
	word *p, *q;
	if (flag == 1) {
		p = (*lb)[L].next;
		q = (*lb)[L + (*root)->varnum].next;
	}
	else {
		p = (*lb)[L + (*root)->varnum].next;
		q = (*lb)[L].next;
	}
	clause*r;
	literal*t;
	while (p) {//������
		r = p->clahead;
		if (r->clamark == 0)//δɾ�� 
		r->clamark = L;//��Ǹ��ı�ʾɾ����
		p = p->next;
	}
	while (q) {//������ 
		r = q->clahead;
		t = q->liter;
		if (r->clamark == 0) {//δɾ�� 
			r->litnum--;
			litnum[q->L]--;//���Ӿ��Ԫ��Ŀ��1  
			t->litmark = L;//��Ǹ��ı�ʾɾ�� 
		}
		q = q->next;
	}
}
int variable_decide(Root root, int *valuation) {//���߱���
	int ooo=valuation[0];
	int L, t, max;int visit=0;//�鿴cnf�Ƿ�Ϊ�� 
	int i = 0;L=-2;
	clause*p, *r;
	literal *q;
	int min;
	p = root->fircal;
	r = p;
	for (i = 0; i < root->calnum; i++) {
		if (p->clamark == 0) {//�Ӿ�δɾ�� 
			if(p->litnum==0) return -2;//���ڿ��Ӿ䷵��-2 
			min = p->litnum;
			r = p;
			visit=1; 
			break;
		}
		p = p->nextcal;
	}
	for (; i < root->calnum; i++) {
		if (p->clamark == 0) {//�Ӿ�δɾ�� 
			visit=1;
			if(p->litnum==0) return -2;//���ڿ��Ӿ䷵��-2 
			if (min > litnum[i + 1]) {
				min = litnum[i + 1];
				r = p;
			}
			if (p->litnum == 1) {
				q = r->first;
				while (q) {
					if (q->litmark == 0) {
						L = q->liter;
						t = abs(L);
						if (L > 0) {
							valuation[t] = 1;
							valuation[0]--;
						}
						else {
							valuation[t] = 0;
							valuation[0]--;
						}
						return t;//�����Ѹ�ֵ�ı�Ԫ 
					}
					q = q->next;
				}
			}
		}
		p = p->nextcal;
	}
	q = r->first;
	while (q) {
		if (q->litmark == 0){
			L = abs(q->liter);//����Ӿ�ĵ�һ��δɾ����Ԫ 
			break;
		}
		q = q->next;
	}
	if(visit==0){
		L=-1;//�Ӿ伯Ϊ�� 
		return L;
	}
	if(L>0){
		valuation[L] = 1;//Ĭ�ϸ�ֵΪ1  
		valuation[0]--;
	} 
	return L;
}
void liternum(Root root, Word *lb) {//������Ԫ�� 
	clause*p;
	word *t, *w;
	literal*r;
	int i, j;
	int data;
	int flag = 0;
	p = root->fircal;
	for (i = 0, j = 0; i < root->calnum; i++) {
		r = p->first;
		litnum[i + 1] = p->litnum;
		while (r) {
			t = (word*)malloc(sizeof(word));
			t->clahead = p;
			t->liter = r;
			t->L = i + 1;
			data = abs(r->liter);
			if (r->liter > 0) {
				if ((*lb)[data].next == NULL) {
					(*lb)[data].next = t;
					t->next = NULL;
				}
				else {
					t->next = (*lb)[data].next;
					(*lb)[data].next = t;
				}
			}
			else {
				if ((*lb)[root->varnum + data].next == NULL) {
					(*lb)[root->varnum + data].next = t;
					t->next = NULL;
				}
				else {
					t->next = (*lb)[data + root->varnum].next;
					(*lb)[root->varnum + data].next = t;
				}
			}
			r = r->next;
		}
		p = p->nextcal;
	}
}
status Testcnf(Root root) {//��֤������ȷ�� 
	clause* p;
	literal *r;
	int i = 0;
	p = root->fircal;
	for (; i < root->calnum; i++) {
		r = p->first;
		while (r) {
			printf("%d ", r->liter);
			r = r->next;
		}
		printf("\n");
		p = p->nextcal;
	}
	return OK;
}
status Loadcnf(char *filename, Root* root, int flag) {//��ȡ����cnf��ʽ 
	char c, d;
	int flag2=0; 
	clause* p, *t;
	literal*q, *r;
	int data;
	int i = 0;
	if (flag) {
		printf("����cnf�ļ�����\n");
		scanf("%s", filename);
	}
	FILE *fp;
	if ((fp = fopen(filename, "r")) == NULL) {
		printf("File open error\n ");
		return ERROR;
	}
	fscanf(fp, "%c", &c);
	if (c == 'p') {
		do {
			flag2=1;
			fscanf(fp, "%c%c", &c, &d);
			fscanf(fp, "%c%c", &c, &d);
			(*root) = (Root)malloc(sizeof(root));
			(*root)->calnum = 0;
			(*root)->varnum = 0;
			fscanf(fp, "%d %d", &((*root)->varnum), &((*root)->calnum));
			if ((*root)->calnum) {
				break;
			}
		} while (fscanf(fp, "%c", &c) != EOF);
	}
	else {
		while (fscanf(fp, "%c", &c) != EOF) {
			if (c == 'p') {
				flag2=1;
				fscanf(fp, "%c%c", &c, &d);
				fscanf(fp, "%c%c", &c, &d);
				(*root) = (Root)malloc(sizeof(root));
				(*root)->calnum = 0;
				(*root)->varnum = 0;
				fscanf(fp, "%d %d", &((*root)->varnum), &((*root)->calnum));
				if ((*root)->calnum) {
					break;
				}
			}
		}
	}
	if ((*root)->calnum) {
		fscanf(fp, "%d", &data);
		p = (clause*)malloc(sizeof(clause));
		t = p;
		p->litnum = 1;
		p->clamark = 0;flag=1;
		q = (literal*)malloc(sizeof(literal));
		p->first = q;
		r = q;
		q->liter = data;
		q->litmark = 0;
		fscanf(fp, "%d", &data);
		while (data) {
			q = (literal*)malloc(sizeof(literal));
			q->liter = data;
			q->litmark = 0;
			r->next = q;flag=1;
			r = q;
			p->litnum++;
			p->clamark = 0;
			fscanf(fp, "%d", &data);
		}
		r->next = q;
		q->next = NULL;
		(*root)->fircal = p;
		p->nextcal = NULL;
	}
	if ((*root)->calnum > 1) {
		for (i = 0; i < (*root)->calnum; i++) {
			fscanf(fp, "%d", &data);
			p = (clause*)malloc(sizeof(clause));
			p->litnum = 1;
			p->clamark = 0;
			q = (literal*)malloc(sizeof(literal));
			p->first = q;
			r = q;
			q->liter = data;
			q->litmark = 0;
			fscanf(fp, "%d", &data);
			while (data != 0) {
				q = (literal*)malloc(sizeof(literal));
				q->liter = data;
				q->litmark = 0;
				r->next = q;
				r = q;
				p->litnum++;
				fscanf(fp, "%d", &data);
			}
			r->next = q;
			q->next = NULL;
			t->nextcal = p;
			t = p;
			p->nextcal = NULL;
		}
	}
	fclose(fp);
	if(flag2){
		printf("�ļ�������ɣ�\n");
		return OK;
	}
	else printf("�ļ�����ʧ��"); 
	return ERROR;
	
}

status savefile(char *filename, int *valuation, Root root, int flag, double t) {//�����ļ� 
	FILE *fp;
	int i = 0;
	for (i = 0; i < 60; i++) {//���ļ�����׺�ĳ�.res 
		if (filename[i] == '\0') {
			filename[i -3 ] = 'r';
			filename[i -2] = 'e';
			filename[i -1] = 's';
			break;
		}
	}
	if ((fp = fopen(filename, "w")) == NULL) {
		printf("File open error\n ");
		return ERROR;
	}
	fprintf(fp, "s %d\nv ", flag);//���°�Ҫ��洢���� 
	if (flag) {
		for (i = 1; i < root->varnum + 1; i++) {
			if (valuation[i] == 1)fprintf(fp, "%d ", i);//Ϊ1 �����ֵ 
			else fprintf(fp, "-%d ", i);//����渺ֵ 
		}
	}
	fprintf(fp, "\n");
	fprintf(fp, "t %f", t);
	fclose(fp);
	printf("�������ɹ���\n");
	return OK;
}

status createsudoku() {//����ģ�� 
	int ls[3][3];
	int num = 0;
	int i, j, k, t;
	int r, s, w;
	int op = 0;
	char filename[60]; 
	FILE *slove, *fp;
	Root root2;
	int *valuation2;
	srand((unsigned)time(NULL));
	k = rand();
	for (i = 3; i < 6; i++) {//���������// 
		for (j = 3; j < 6; j++) {
			ls[i - 3][j - 3] = (k % 9) + 1;
			sudoku[i][j] = (k % 9) + 1;
			k++;
		}
	}
	//���ݾ�������б任����������ʼ������� 
	//����˳�򲻿ɱ�
	for (i = 3; i < 6; i++) {//���ĸ�����
		for (j = 0; j < 3; j++) {
			sudoku[i][j] = sudoku[(i + 2) % 3 + 3][j + 3];
		}
	}
	for (i = 3; i < 6; i++) {//����������
		for (j = 6; j < 9; j++) {
			sudoku[i][j] = sudoku[(i + 1) % 3 + 3][j - 3];
		}
	}
	for (i = 0; i < 3; i++) {//�ڶ�������
		for (j = 3; j < 6; j++) {
			sudoku[i][j] = ls[i][(j + 2) % 3];
		}
	}
	for (i = 0; i < 3; i++) {//��һ������
		for (j = 0; j < 3; j++) {
			sudoku[i][j] = sudoku[i + 3][(j + 2) % 3];
		}
	}
	for (i = 0; i < 3; i++) {//����������
		for (j = 6; j < 9; j++) {
			sudoku[i][j] = sudoku[i + 3][(j - 1) % 3 + 6];
		}
	}
	for (i = 6; i < 9; i++) {//��7������
		for (j = 0; j < 3; j++) {
			sudoku[i][j] = sudoku[i - 3][(j + 1) % 3];
		}
	}
	for (i = 6; i < 9; i++) {//��8������
		for (j = 3; j < 6; j++) {
			sudoku[i][j] = sudoku[i - 3][(j + 1) % 3 + 3];
		}
	}
	for (i = 6; i < 9; i++) {//�ھŸ�����
		for (j = 6; j < 9; j++) {
			sudoku[i][j] = sudoku[i - 3][(j + 1) % 3 + 6];
		}
	}
	slove = fopen("slove.txt", "w");
	for (i = 0; i < 9; i++) {//��ԭʼ������������
		for (j = 0; j < 9; j++) {
			fprintf(slove, "%d ", sudoku[i][j]);
		}
		fprintf(slove, "\n");
	}

	for (i = 81; i > 0; i--) {
		k = rand() % 81;
		sudoku[k / 9][k % 9] = 0;
	}
	printf("Ŀǰ������������£�\n");
	for (i = 0; i < 9; i++) {
		for (j = 0; j < 9; j++) {
			if (sudoku[i][j])
				printf("%d ", sudoku[i][j]);
			else printf("_ ");
		}
		printf("\n");
	}
	printf("�Ƿ�Ҫ������������\n");
	printf("0.NOֱ�ӿ��� 1.YES��Ҫ������\n");
	scanf("%d", &op);
	while (op) {//�����ݵĻ� 
		printf("��������ֵ\n");
		scanf("%d %d %d", &r, &s, &w);
		sudoku[r - 1][s - 1] = w;//�ӵ�����Ϊw 
		getchar();
		if ((fp = fopen("sudoku.cnf", "w")) == NULL)
		{
			printf("File open error\n ");
		}
		for (t = 0, i = 0; i < 9; i++) {
			for (j = 0; j < 9; j++) {
				if (sudoku[i][j]) t++;
			}
		}
		//��������Ϊcnf��ʽ������sudoku.cnf�ļ���
		fprintf(fp, "p cnf 729 %d\n", t + 10530); 
		for (i = 0; i < 9; i++) {//�����Ѿ����ڵ���
			for (j = 0; j < 9; j++) {
				if (k = sudoku[i][j]) {//���������ڵĵ��Ӿ� 
					fprintf(fp, "%d 0\n", 81 * i + 9 * j + k);//���� 81 * i + 9 * j + k�Ĺ��򽫵�i+1��j+1��ֵΪkת���ɱ�Ԫ 
				}
			}
		}
		for (i = 1; i < 10; i++) {
			for (j = 1; j < 10; j++) {
				for (k = 1; k < 10; k++) {
					fprintf(fp, "%d ", 81 * (i - 1) + 9 * (j - 1) + k);//ÿ��cell��Ϊ1-9 
				}
				fprintf(fp, "0\n");
			}
		}
		for (i = 1; i < 10; i++) {//
			for (j = 1; j < 10; j++) {
				for (k = 1; k < 9; k++) {
					for (t = k + 1; t < 10; t++) {
						fprintf(fp, "-%d ", 81 * (i - 1) + 9 * (j - 1) + k);//ÿ��cell������ͬʱΪ1 2��1 3...... 
						fprintf(fp, "-%d 0\n", 81 * (i - 1) + 9 * (j - 1) + t);
					}
				}
			}
		}
		for (i = 1; i < 10; i++) {//���д���ÿһ��һ������1-9&&ÿһ�в�������ͬ����
			for (k = 1; k < 10; k++) {
				for (j = 1; j < 10; j++) {
					fprintf(fp, "%d ", 81 * (i - 1) + 9 * (j - 1) + k);
				}
				fprintf(fp, "0\n");
			}
			for (k = 1; k < 10; k++) {//ÿһ�в�������ͬ���� 
				for (j = 1; j < 9; j++) {
					for (t = j + 1; t < 10; t++) {
						fprintf(fp, "-%d ", 81 * (i - 1) + 9 * (j - 1) + k);
						fprintf(fp, "-%d 0\n", 81 * (i - 1) + 9 * (t - 1) + k);
					}
				}
			}
		}
		for (j = 1; j < 10; j++) {//���д���  ��ʽͬ��
			for (k = 1; k < 10; k++) {
				for (i = 1; i < 10; i++) {
					fprintf(fp, "%d ", 81 * (i - 1) + 9 * (j - 1) + k);
				}
				fprintf(fp, "0\n");
			}
			for (k = 1; k < 10; k++) {
				for (i = 1; i < 9; i++) {
					for (t = i + 1; t < 10; t++) {
						fprintf(fp, "-%d ", 81 * (i - 1) + 9 * (j - 1) + k);
						fprintf(fp, "-%d 0\n", 81 * (t - 1) + 9 * (j - 1) + k);
					}
				}
			}
		}
		int m, n;
		//��3*3�鴦�� 
		for (m = 0; m < 3; m++) {//��m+1�е�3*3�� 
			for (n = 0; n < 3; n++) {//��n+1�е�3*3�� 
				for (k = 1; k < 10; k++) {
					for (i = 1; i < 4; i++) {
						for (j = 1; j < 4; j++) {
							fprintf(fp, "%d ", 81 * ((i - 1) + 3 * m) + 9 * ((j - 1) + 3 * n) + k);//ÿ�������1 2 3 4 ....9 
						}
					}
					fprintf(fp, "0\n");
				}
				//��ÿ���鲻��������ͬ���� 
				for (k = 1; k < 10; k++) {//���µ������� 
					i = 1;
					j = 1;
					fprintf(fp, "-%d ", 81 * (3 * m + i - 1) + 9 * (3 * n + j - 1) + k);
					fprintf(fp, "-%d 0\n", 81 * (3 * m + i) + 9 * (3 * n + j) + k);
					fprintf(fp, "-%d ", 81 * (3 * m + i - 1) + 9 * (3 * n + j - 1) + k);
					fprintf(fp, "-%d 0\n", 81 * (3 * m + i) + 9 * (3 * n + j + 1) + k);
					fprintf(fp, "-%d ", 81 * (3 * m + i - 1) + 9 * (3 * n + j - 1) + k);
					fprintf(fp, "-%d 0\n", 81 * (3 * m + i + 1) + 9 * (3 * n + j) + k);
					fprintf(fp, "-%d ", 81 * (3 * m + i - 1) + 9 * (3 * n + j - 1) + k);
					fprintf(fp, "-%d 0\n", 81 * (3 * m + i + 1) + 9 * (3 * n + j + 1) + k);
					j = 2;
					fprintf(fp, "-%d ", 81 * (3 * m + i - 1) + 9 * (3 * n + j - 1) + k);
					fprintf(fp, "-%d 0\n", 81 * (3 * m + i) + 9 * (3 * n + j - 2) + k);
					fprintf(fp, "-%d ", 81 * (3 * m + i - 1) + 9 * (3 * n + j - 1) + k);
					fprintf(fp, "-%d 0\n", 81 * (3 * m + i) + 9 * (3 * n + j) + k);
					fprintf(fp, "-%d ", 81 * (3 * m + i - 1) + 9 * (3 * n + j - 1) + k);
					fprintf(fp, "-%d 0\n", 81 * (3 * m + i + 1) + 9 * (3 * n + j - 2) + k);
					fprintf(fp, "-%d ", 81 * (3 * m + i - 1) + 9 * (3 * n + j - 1) + k);
					fprintf(fp, "-%d 0\n", 81 * (3 * m + i + 1) + 9 * (3 * n + j) + k);
					j = 3;
					fprintf(fp, "-%d ", 81 * (3 * m + i - 1) + 9 * (3 * n + j - 1) + k);
					fprintf(fp, "-%d 0\n", 81 * (3 * m + i) + 9 * (3 * n + j - 1 - 2) + k);
					fprintf(fp, "-%d ", 81 * (3 * m + i - 1) + 9 * (3 * n + j - 1) + k);
					fprintf(fp, "-%d 0\n", 81 * (3 * m + i) + 9 * (3 * n + j - 1 - 1) + k);
					fprintf(fp, "-%d ", 81 * (3 * m + i - 1) + 9 * (3 * n + j - 1) + k);
					fprintf(fp, "-%d 0\n", 81 * (3 * m + i + 1) + 9 * (3 * n + j - 3) + k);
					fprintf(fp, "-%d ", 81 * (3 * m + i - 1) + 9 * (3 * n + j - 1) + k);
					fprintf(fp, "-%d 0\n", 81 * (3 * m + i + 1) + 9 * (3 * n + j - 2) + k);
					i = 2;
					j = 1;
					fprintf(fp, "-%d ", 81 * (3 * m + i - 1) + 9 * (3 * n + j - 1) + k);
					fprintf(fp, "-%d 0\n", 81 * (3 * m + i) + 9 * (3 * n + j) + k);
					fprintf(fp, "-%d ", 81 * (3 * m + i - 1) + 9 * (3 * n + j - 1) + k);
					fprintf(fp, "-%d 0\n", 81 * (3 * m + i) + 9 * (3 * n + j + 1) + k);
					j = 2;
					fprintf(fp, "-%d ", 81 * (3 * m + i - 1) + 9 * (3 * n + j - 1) + k);
					fprintf(fp, "-%d 0\n", 81 * (3 * m + i) + 9 * (3 * n + j - 2) + k);
					fprintf(fp, "-%d ", 81 * (3 * m + i - 1) + 9 * (3 * n + j - 1) + k);
					fprintf(fp, "-%d 0\n", 81 * (3 * m + i) + 9 * (3 * n + j) + k);
					j = 3;
					fprintf(fp, "-%d ", 81 * (3 * m + i - 1) + 9 * (3 * n + j - 1) + k);
					fprintf(fp, "-%d 0\n", 81 * (3 * m + i) + 9 * (3 * n + j - 3) + k);
					fprintf(fp, "-%d ", 81 * (3 * m + i - 1) + 9 * (3 * n + j - 1) + k);
					fprintf(fp, "-%d 0\n", 81 * (3 * m + i) + 9 * (3 * n + j - 2) + k);
				}
			}
		}
		fclose(fp); fclose(slove);
		strcpy(filename, "sudoku.cnf");
		if (Loadcnf(filename, &root2, 0)) {//����DPLL������ 
			num = root2->varnum + 1;
			valuation2 = (int*)malloc(sizeof(int)*(num));
			valuation2[0] = root2->varnum;
			for (i = 1; i <= root2->varnum; i++) {
				valuation2[i] = 0;
			}
			system("cls");
			printf("\n\n\n\n");
			if (DPLL(root2, valuation2) == 0) {//�����һ������ֵ�����������򷵻ػָ���һ���ĸ�� 
				printf("�ò����޽⣡\n���������룡\n");
				sudoku[r - 1][s - 1] = 0;
			}
			else {
				printf("�ɽ⣡\n");
			}
			printf("\n\nĿǰ������������£�\n");
			for (i = 0; i < 9; i++) {
				for (j = 0; j < 9; j++) {
					if (sudoku[i][j])
						printf("%d ", sudoku[i][j]);
					else printf("_ ");
				}
				printf("\n");
			}
		}
		free(valuation2);
		valuation2 = NULL;
		printf("�Ƿ�Ҫ������������\n");
		printf("0.�����ֱ�ӿ���  1.�����\n");
		scanf("%d", &op);
	}
	if ((fp = fopen("sudoku.cnf", "w")) == NULL)
	{
		printf("File open error\n ");
	}
	for (t = 0, i = 0; i < 9; i++) {
		for (j = 0; j < 9; j++) {
			if (sudoku[i][j]) t++;
		}
	}
	//��������Ϊcnf��ʽ������sudoku.cnf�ļ���
	//����ע��ͬ�� 
	fprintf(fp, "p cnf 729 %d\n", t + 10530);
	for (i = 0; i < 9; i++) {//�����Ѿ����ڵ���
		for (j = 0; j < 9; j++) {
			if (k = sudoku[i][j]) {
				fprintf(fp, "%d 0\n", 81 * i + 9 * j + k);
			}
		}
	}
	for (i = 1; i < 10; i++) {
		for (j = 1; j < 10; j++) {
			for (k = 1; k < 10; k++) {
				fprintf(fp, "%d ", 81 * (i - 1) + 9 * (j - 1) + k);
			}
			fprintf(fp, "0\n");
		}
	}
	for (i = 1; i < 10; i++) {
		for (j = 1; j < 10; j++) {
			for (k = 1; k < 9; k++) {
				for (t = k + 1; t < 10; t++) {
					fprintf(fp, "-%d ", 81 * (i - 1) + 9 * (j - 1) + k);
					fprintf(fp, "-%d 0\n", 81 * (i - 1) + 9 * (j - 1) + t);
				}
			}
		}
	}
	for (i = 1; i < 10; i++) {//���д���ÿһ��һ������1-9&&ÿһ�в�������ͬ����
		for (k = 1; k < 10; k++) {
			for (j = 1; j < 10; j++) {
				fprintf(fp, "%d ", 81 * (i - 1) + 9 * (j - 1) + k);
			}
			fprintf(fp, "0\n");
		}
		for (k = 1; k < 10; k++) {
			for (j = 1; j < 9; j++) {
				for (t = j + 1; t < 10; t++) {
					fprintf(fp, "-%d ", 81 * (i - 1) + 9 * (j - 1) + k);
					fprintf(fp, "-%d 0\n", 81 * (i - 1) + 9 * (t - 1) + k);
				}
			}
		}
	}
	for (j = 1; j < 10; j++) {//���д���  ��ʽͬ��
		for (k = 1; k < 10; k++) {
			for (i = 1; i < 10; i++) {
				fprintf(fp, "%d ", 81 * (i - 1) + 9 * (j - 1) + k);
			}
			fprintf(fp, "0\n");
		}
		for (k = 1; k < 10; k++) {
			for (i = 1; i < 9; i++) {
				for (t = i + 1; t < 10; t++) {
					fprintf(fp, "-%d ", 81 * (i - 1) + 9 * (j - 1) + k);
					fprintf(fp, "-%d 0\n", 81 * (t - 1) + 9 * (j - 1) + k);
				}
			}
		}
	}
	int m, n;
	for (m = 0; m < 3; m++) {
		for (n = 0; n < 3; n++) {
			for (k = 1; k < 10; k++) {
				for (i = 1; i < 4; i++) {
					for (j = 1; j < 4; j++) {
						fprintf(fp, "%d ", 81 * ((i - 1) + 3 * m) + 9 * ((j - 1) + 3 * n) + k);
					}
				}
				fprintf(fp, "0\n");
			}
			for (k = 1; k < 10; k++) {
				i = 1;
				j = 1;
				fprintf(fp, "-%d ", 81 * (3 * m + i - 1) + 9 * (3 * n + j - 1) + k);
				fprintf(fp, "-%d 0\n", 81 * (3 * m + i) + 9 * (3 * n + j) + k);
				fprintf(fp, "-%d ", 81 * (3 * m + i - 1) + 9 * (3 * n + j - 1) + k);
				fprintf(fp, "-%d 0\n", 81 * (3 * m + i) + 9 * (3 * n + j + 1) + k);
				fprintf(fp, "-%d ", 81 * (3 * m + i - 1) + 9 * (3 * n + j - 1) + k);
				fprintf(fp, "-%d 0\n", 81 * (3 * m + i + 1) + 9 * (3 * n + j) + k);
				fprintf(fp, "-%d ", 81 * (3 * m + i - 1) + 9 * (3 * n + j - 1) + k);
				fprintf(fp, "-%d 0\n", 81 * (3 * m + i + 1) + 9 * (3 * n + j + 1) + k);
				j = 2;
				fprintf(fp, "-%d ", 81 * (3 * m + i - 1) + 9 * (3 * n + j - 1) + k);
				fprintf(fp, "-%d 0\n", 81 * (3 * m + i) + 9 * (3 * n + j - 2) + k);
				fprintf(fp, "-%d ", 81 * (3 * m + i - 1) + 9 * (3 * n + j - 1) + k);
				fprintf(fp, "-%d 0\n", 81 * (3 * m + i) + 9 * (3 * n + j) + k);
				fprintf(fp, "-%d ", 81 * (3 * m + i - 1) + 9 * (3 * n + j - 1) + k);
				fprintf(fp, "-%d 0\n", 81 * (3 * m + i + 1) + 9 * (3 * n + j - 2) + k);
				fprintf(fp, "-%d ", 81 * (3 * m + i - 1) + 9 * (3 * n + j - 1) + k);
				fprintf(fp, "-%d 0\n", 81 * (3 * m + i + 1) + 9 * (3 * n + j) + k);
				j = 3;
				fprintf(fp, "-%d ", 81 * (3 * m + i - 1) + 9 * (3 * n + j - 1) + k);
				fprintf(fp, "-%d 0\n", 81 * (3 * m + i) + 9 * (3 * n + j - 1 - 2) + k);
				fprintf(fp, "-%d ", 81 * (3 * m + i - 1) + 9 * (3 * n + j - 1) + k);
				fprintf(fp, "-%d 0\n", 81 * (3 * m + i) + 9 * (3 * n + j - 1 - 1) + k);
				fprintf(fp, "-%d ", 81 * (3 * m + i - 1) + 9 * (3 * n + j - 1) + k);
				fprintf(fp, "-%d 0\n", 81 * (3 * m + i + 1) + 9 * (3 * n + j - 3) + k);
				fprintf(fp, "-%d ", 81 * (3 * m + i - 1) + 9 * (3 * n + j - 1) + k);
				fprintf(fp, "-%d 0\n", 81 * (3 * m + i + 1) + 9 * (3 * n + j - 2) + k);
				i = 2;
				j = 1;
				fprintf(fp, "-%d ", 81 * (3 * m + i - 1) + 9 * (3 * n + j - 1) + k);
				fprintf(fp, "-%d 0\n", 81 * (3 * m + i) + 9 * (3 * n + j) + k);
				fprintf(fp, "-%d ", 81 * (3 * m + i - 1) + 9 * (3 * n + j - 1) + k);
				fprintf(fp, "-%d 0\n", 81 * (3 * m + i) + 9 * (3 * n + j + 1) + k);
				j = 2;
				fprintf(fp, "-%d ", 81 * (3 * m + i - 1) + 9 * (3 * n + j - 1) + k);
				fprintf(fp, "-%d 0\n", 81 * (3 * m + i) + 9 * (3 * n + j - 2) + k);
				fprintf(fp, "-%d ", 81 * (3 * m + i - 1) + 9 * (3 * n + j - 1) + k);
				fprintf(fp, "-%d 0\n", 81 * (3 * m + i) + 9 * (3 * n + j) + k);
				j = 3;
				fprintf(fp, "-%d ", 81 * (3 * m + i - 1) + 9 * (3 * n + j - 1) + k);
				fprintf(fp, "-%d 0\n", 81 * (3 * m + i) + 9 * (3 * n + j - 3) + k);
				fprintf(fp, "-%d ", 81 * (3 * m + i - 1) + 9 * (3 * n + j - 1) + k);
				fprintf(fp, "-%d 0\n", 81 * (3 * m + i) + 9 * (3 * n + j - 2) + k);
			}
		}
	}
	fclose(fp); fclose(slove);
	strcpy(filename, "sudoku.cnf");
	if (Loadcnf(filename, &root2, 0)) {
		valuation2 = (int*)malloc(sizeof(int)*(root2->varnum + 1));
		valuation2[0] = root2->varnum;
		for (i = 1; i <= root2->varnum; i++) {
			valuation2[i] = 0;
		}
		system("cls");
		printf("\n\n\n\n");

		printf("\n\nĿǰ������������£�\n");
		for (i = 0; i < 9; i++) {
			for (j = 0; j < 9; j++) {
				if (sudoku[i][j])
					printf("%d ", sudoku[i][j]);
				else printf("_ ");
			}
			printf("\n");
		}
		if (DPLL(root2, valuation2)) {
			for (w = 1; w < 730; w++) {
				if (valuation2[w]) {
					k = w % 9;
					if (k == 0)k = 9;
					j = ((w - k) % 81) / 9 + 1;
					i = (w - k - 9 * (j - 1)) / 81 + 1;
					sudoku[i - 1][j - 1] = k;
				}
			}
			printf("�����Ľ�Ϊ:\n");
			for (i = 0; i < 9; i++) {
				for (j = 0; j < 9; j++) {
					printf("%d ", sudoku[i][j]);
				}
				printf("\n");
			}
			getchar(); getchar();
		}
	}
	return OK;
}
