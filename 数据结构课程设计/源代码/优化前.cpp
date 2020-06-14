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
typedef struct literal {//����
	int liter;//��Ԫ
	struct literal* next;
	int litmark;//����Ƿ�ɾ��
}literal;
typedef struct clause {//�Ӿ�ͷ
	int litnum;//���Ӿ��Ԫ����
	struct clause* nextcal;
	struct literal* first;
	int clamark;
}clause;
typedef struct root {//��
	int onecla;
	int varnum;
	int calnum;
	struct clause* fircal;
}*Root;
typedef struct stack {
	int literal;
	int value;
}*Stack;

status Loadcnf(char*filename, Root* root, int flag);//����cnf�ļ�
status Testcnf(Root root);//���Խ����Ƿ���ȷ
int isUnitClause(Root root);//�ж��Ƿ��е��Ӿ�
int emptycla(Root root);//�ж��Ӿ��Ƿ�Ϊ�գ��п��Ӿ䷵��0�޿��Ӿ䷵��1
status emptycnf(Root root);//�жϹ�ʽ�Ƿ�Ϊ��
void liternum(Root root, int *sum);
status DPLL(Root root, int *valuation);
int variable_decide(Root root, int *valuation, int *sum);
status cnfdeduce(Root *root, int L, int flag, int *sum);
void cnfrestore(Root *root, int L, int *sum);
void visitvalue(Root root, int *value);
status evaluateClause(Root root, int L, int *value);
status createsudoku();//��ʼ���������
status savefile(char *filename, int *valuation, Root root, int flag, double t);//��������������res�ļ���
int sudoku[9][9];
int main(void) {
	clock_t start, finish;//ʱ��
	double tim;
	int op = 1;
	int i = 0;
	int j, k, w;
	int flag; int select = 0;
	char filename[60];
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
				printf("��ʼ��⣡\n");
			}
			else return 0;
			int *valuation;
			valuation = (int*)malloc(sizeof(int)*(root->varnum + 1));
			valuation[0] = root->varnum;
			for (i = 1; i <= root->varnum; i++) {
				valuation[i] = 0;
			}
			start = clock();;
			if (DPLL(root, valuation)) {
				flag = 1;
				finish = clock();
				printf("SAT!\n��Ϊ\n");
				for (i = 1; i < root->varnum + 1; i++) {
					printf("%d %d \n", i, valuation[i]);
				}
			}
			else {
				flag = 0;
				finish = clock();
				printf("UNSAT��\n");
			}
			tim = (double)(finish - start);
			printf("DPLL��ִ��ʱ����%fms.\n", tim);
			savefile(filename, valuation, root, flag, tim);
			getchar();
			break;
		case 2:
			Root root2;
			if (createsudoku()) {
				printf("sudoku������ɣ�\n");
			}
			strcpy(filename, "sudoku.cnf");
			if (Loadcnf(filename, &root2, 0)) {
				int *valuation2;
				valuation2 = (int*)malloc(sizeof(int)*(root2->varnum + 1));
				valuation2[0] = root2->varnum;
				for (i = 1; i <= root2->varnum; i++) {
					valuation2[i] = 0;
				}
				start = clock();;
				printf("��ʼ��⣡\n");
				if (DPLL(root2, valuation2)) {
					printf("SAT!\n");
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
				else {
					printf("�������޽⣡\n");
					getchar();
				}
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
status DPLL(Root root, int *valuation) {
	int t, flag, L;
	int i = 0;
	int j = 0;
	int lp;
	int *sum;
	flag = 1;
	Stack visit;
	sum = (int *)malloc(sizeof(int)*(root->varnum + 1));
	for (i = 0; i < root->varnum + 1; i++) {
		sum[i] = 0;
	}
	liternum(root, sum);
	visit = (Stack)malloc(sizeof(stack)*root->varnum + 1);
	for (i = 0; i < root->varnum + 1; i++) {
		visit[i].literal = 0;
		visit[i].value = 0;
	}
	i = 0;
	while (1) {
		L = variable_decide(root, valuation, sum);
		if (L == 0) return OK;
		visit[i].literal = L;
		visit[i].value = valuation[L];
		i++;
		while (1) {
			if (evaluateClause(root, L, valuation)) {
				cnfdeduce(&root, L, valuation[L], sum);
				if (emptycnf(root)) return OK;
				else if (emptycla(root)) {
					for (j = i - 1; j >= 0; j--) {
						t = visit[j].literal;
						if (visit[j].value == 1) {
							visit[j].value = 0;
							i--;
							valuation[t] = 0;
							valuation[0]++;
							cnfrestore(&root, t, sum);
							continue;
						}
						else if (visit[j].value == 0) {
							visit[j].value = 1;
							cnfrestore(&root, t, sum);
							valuation[t] = 1;
							L = t;
							i = j + 1;
							break;
						}
					}
					if (j == -1) return ERROR;
				}
				else break;
			}
			else {
				for (j = i - 1; j >= 0; j--) {
					t = visit[j].literal;
					if (visit[j].value == 1) {
						visit[j].value = 0;
						valuation[t] = 0;
						valuation[0]++;
						if (j != i - 1)	cnfrestore(&root, t, sum);
						continue;
					}
					else if (visit[j].value == 0) {
						visit[j].value = 1;
						valuation[t] = 1;
						L = t;
						if (j != i - 1)	cnfrestore(&root, L, sum);
						i = j + 1;
						break;
					}
				}
				if (j == -1) return ERROR;
			}
		}
	}
}
status evaluateClause(Root root, int L, int *value) {
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
				}
				q = q->next;
			}
		}
		p = p->nextcal;
	}
	return OK;
}
void cnfrestore(Root *root, int L, int *sum) {
	clause *p;
	literal *q, *r;
	p = (*root)->fircal;
	int i = 0;
	for (i = 0; i < (*root)->calnum; i++) {
		q = p->first;
		r = p->first;
		if (p->clamark == 0) {
			while (q) {
				if (q->litmark == L) {
					q->litmark = 0;
					p->litnum++;
					sum[L]++;
				}
				q = q->next;
			}
		}
		else if (p->clamark == L) {
			p->clamark = 0;
			while (r) {
				if (r->litmark == 0)
					sum[abs(r->liter)]++;
				r = r->next;
			}
		}
		p = p->nextcal;
	}
}
status cnfdeduce(Root *root, int L, int flag, int *sum) {
	clause *p;
	literal *q, *r;
	p = (*root)->fircal;
	int i;
	int t = 0;//��־
	if (flag) {
		for (i = 0; i < (*root)->calnum; i++) {
			if (p->clamark == 0) {
				q = p->first;
				r = p->first;
				while (q) {
					if (q->litmark == 0 && q->liter == L) {
						p->clamark = L;
						while (r) {
							if (r->litmark == 0)
								sum[abs(r->liter)]--;
							r = r->next;
						}
						sum[L] = 0;;
						t = 1;
					}
					else if (q->litmark == 0 && q->liter == (L*(-1))) {
						q->litmark = L;
						p->litnum--;
						sum[L] = 0;;
						t = 1;
					}
					q = q->next;
				}
			}
			p = p->nextcal;
		}
	}
	else {
		for (i = 0; i < (*root)->calnum; i++) {
			if (p->clamark == 0) {
				q = p->first;
				r = p->first;
				while (q) {
					if (q->litmark == 0 && q->liter == L) {
						q->litmark = L;
						p->litnum--;
						sum[L] = 0;
						t = 1;
					}
					else if (q->litmark == 0 && q->liter == (L*(-1))) {
						p->clamark = L;
						while (r) {
							if (r->litmark == 0) {
								sum[abs(r->liter)]--;
							}
							r = r->next;
						}
						t = 1;
						sum[L] = 0;
					}
					q = q->next;
				}
			}
			p = p->nextcal;
		}
	}
	return t;
}
int variable_decide(Root root, int *valuation, int *sum) {//���߱���
	if (valuation[0] == 0)return 0;
	int L, t, max;
	int i = 0;
	if (L = isUnitClause(root)) {
		t = abs(L);
		if (L < 0) {
			valuation[t] = 0;
			valuation[0]--;
			return t;
		}
		else {
			valuation[L] = 1;
			valuation[0]--;
			return L;
		}
	}
	else {
		max = sum[1];
		sum[0] = 1;
		for (i = 1; i < root->varnum + 1; i++) {
			if (max < sum[i]) {
				max = sum[i];
				sum[0] = i;
			}
		}
		valuation[sum[0]] = 0;
		valuation[0]--;
		return sum[0];
	}
}
void liternum(Root root, int *sum) {
	clause*p;
	literal*r;
	//word *s,*t;
	int i, data;
	int flag = 0;
	p = root->fircal;
	//for (i = 0; i < root->calnum + 1; i++) {
		//vs[i]->wordnum = 0;
		//vs[i]->first == NULL;
	//}
	for (i = 0; i < root->calnum; i++) {
		if (p->clamark == 0) {
			r = p->first;
			while (r) {
				if (r->litmark == 0) {
					data = abs(r->liter);
					sum[data]++;
				}
				r = r->next;
			}
		}
		p = p->nextcal;
	}
}
int isUnitClause(Root root) {//�е��Ӿ䷵�ظ��Ӿ�����֣�û���򷵻�0
	clause*p;
	literal*q;
	p = root->fircal;
	int i;
	for (i = 0; i < root->calnum; i++) {
		if (p->clamark == 0 && p->litnum == 1) {
			q = p->first;
			while (q) {
				if (q->litmark == 0) return q->liter;
				q = q->next;
			}
		}
		p = p->nextcal;
	}
	return 0;
}
status emptycnf(Root root) {//�ǿշ���1�ǿշ���0
	clause *p;
	int i;
	p = root->fircal;
	for (i = 0; i < root->calnum; i++) {
		if (p->clamark == 0)
			return 0;//�ǿշ���2 
		p = p->nextcal;
	}
	return OK;
}

int emptycla(Root root) {//�п��Ӿ䷵��0�޿��Ӿ䷵��1
	clause*p;
	int i;
	p = root->fircal;
	for (i = 0; i < root->calnum; i++) {
		if (p->litnum == 0)
			return 1;
		p = p->nextcal;
	}
	return 0;
}
void visitvalue(Root root, int *value) {
	int i = 0;
	for (i = 1; i < root->varnum + 1; i++) {
		printf("%d %d \n", i, value[i]);
	}
	printf("\n");
}
status Testcnf(Root root) {
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
status Loadcnf(char *filename, Root* root, int flag) {
	char c, d;
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
		p->clamark = 0;
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
			r->next = q;
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
	//printf("�ļ�������ɣ�\n");
	return OK;
}
status savefile(char *filename, int *valuation, Root root, int flag, double t) {
	FILE *fp,*fp2;
	int i = 0;
	fp2 = fopen("t.txt", "w+");
	for (i = 0; i < 60; i++) {
		if (filename[i] == '.') {
			filename[i + 1] = 'r';
			filename[i + 2] = 'e';
			filename[i + 3] = 's';
			break;
		}
	}
	if ((fp = fopen(filename, "w")) == NULL) {
		printf("File open error\n ");
		return ERROR;
	}
	fprintf(fp, "s %d\nv ", flag);
	if (flag) {
		for (i = 1; i < root->calnum + 1; i++) {
			if (valuation[i] == 1)fprintf(fp, "%d ", i);
			else fprintf(fp, "-%d ", i);
		}
	}
	fprintf(fp, "\n");
	fprintf(fp, "t %f", t);
	fprintf(fp2, "%f", t);
	fclose(fp);
	fclose(fp2);
	printf("�������ɹ���\n");
	return OK;
}

status createsudoku() {
	int ls[3][3];
	int i, j, k, t;
	int op = 0;
	FILE *slove, *fp;
	srand((unsigned)time(NULL));
	k = rand();
	for (i = 3; i < 6; i++) {//���������/
		for (j = 3; j < 6; j++) {
			ls[i - 3][j - 3] = (k % 9) + 1;
			sudoku[i][j] = (k % 9) + 1;
			k++;
		}
	}
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
			printf("%d ", sudoku[i][j]);
		}
		printf("\n");
	}
	printf("�Ƿ�Ҫ������������\n");
	printf("0.NO 1.YES\n");
	scanf("%d", &op);
	while (op) {
		printf("��������ֵ\n");
		scanf("%d %d %d", &i, &j, &k);
		sudoku[i - 1][j - 1] = k;
		getchar();
		system("cls");
		printf("\n\nĿǰ������������£�\n");
		for (i = 0; i < 9; i++) {
			for (j = 0; j < 9; j++) {
				printf("%d ", sudoku[i][j]);
			}
			printf("\n");
		}
		printf("�Ƿ�Ҫ������������\n");
		printf("0.NO  1.YES\n");
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
	return OK;
}
