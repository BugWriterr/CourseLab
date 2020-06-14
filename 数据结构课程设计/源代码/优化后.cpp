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
typedef struct root {//根
	int varnum;//变元数 
	int calnum;//子句数 
	struct clause* fircal;//指向第一个子句 
}*Root;//根类型 

typedef struct clause {//子句头 
	int litnum;//该子句变元个数
	struct clause* nextcal;//指向下一个子句 
	struct literal* first;//指向第一个文字 
	int clamark;//标记子句是否删除 
}clause;//子句类型 

typedef struct literal {//文字
	int liter;//变元
	struct literal* next;//指向下一个文字 
	int litmark;//标记是否删除
}literal;//文字类型 

typedef struct word {//变元表 
	clause *clahead;//指向该变元所在的子句头 
	literal* liter;//指向该变元所在的文字 
	int L;//该变元所在的子句序号 
	word *next;//指向下一个相同变元 
}word, *Word;//变元表类型 

typedef struct stack {//栈，方便回溯时使用 
	int literal;//存入赋值的值 
	int value;//变元的值 
}*Stack;//栈指针，动态分配数组 
status Loadcnf(char*filename, Root* root, int flag);//解析cnf文件
status Testcnf(Root root);//测试解析是否正确
status DPLL(Root root, int *valuation);//DPLL算法 
status evaluateClause(Root root, int L, int *value);//判断公式是否存在冲突 
status createsudoku();//数独游戏，算法自动生成数独格局，同时解数独，具有人机交互 
status savefile(char *filename, int *valuation, Root root, int flag, double t);//将输出结果保存在res文件中
int variable_decide(Root root, int *valuation);//决策变量，选取单子句或者出现最短子句第一个变元 
void liternum(Root root, Word *lb);//遍历，建立变元表，同时统计每个子句变元个数 
void cnfdeduce(Root *root, int L, int flag, Word *lb);//化简cnf公式，删除 
void cnfrestore(Root *root, int L, Word *lb);//回溯cnf公式。回溯时 
int sudoku[9][9];//数独格局 
int litnum[10000000];//子句个数，人工设定。若子句个数大于，则增加数组大小 
int main(void) {
	clock_t start, finish;//时间
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
		printf("      Menu for 综合课设 \n");
		printf("-------------------------------------------------\n");
		printf("    	  1. SAT       2. sudoku\n    	  0.EXIT\n");
		scanf("%d", &op);
		switch (op) {
		case 1:
			Root root;
			if (Loadcnf(filename, &root, 1)) {
				printf("该公式包含%d个变元， %d个子句！\n", root->varnum, root->calnum);
				printf("是否需要验证！\n1.YES    0.NO\n");
				scanf("%d", &select);
				if (select == 1) {
					printf("输入回车开始验证！\n");
					if (Testcnf(root))
						printf("遍历完成！\n");
				}
				getchar();
				printf("输入回车开始求解！\n");
				getchar();
				printf("求解ing...\n");
			}
			else return 0;
			int *valuation;
			valuation = (int*)malloc(sizeof(int)*(root->varnum + 1));
			valuation[0] = root->varnum;
			for (i = 1; i <= root->varnum; i++) {
				valuation[i] = 0;
			}
			start = clock();
			printf("文件：%s\n",filename);
			if (DPLL(root, valuation)) {
				finish = clock();
				flag = 1;
				printf("SAT!\n");
			}
			else {
				flag = 0;
				finish = clock();
				printf("UNSAT！\n");
			}
			tim = (double)(finish - start);
			printf("DPLL的执行时间是%fms.\n", tim);
			printf("                %fs.\n", tim / CLK_TCK);
			printf("如需要计算优化率，请确定该sat已在优化前.cpp运行！\n");
			printf("是否完成上述要求\n0:NO(不计算优化率)   1.YES(计算且已完成优化前的运行)\n");
			scanf("%d", &oooo);
			if (oooo) {
				if(fp = fopen("t.txt", "r")){
				fscanf(fp, "%lf", &tim2);
				}
				else {
					printf("优化前未运行。\n");
				}
				fclose(fp);
				printf("优化前的执行时间为%fms\n", tim2);
				if(tim2==0){
					printf("优化率为%f%%\n", (1 - tim) / 1.0 * 100);
				}
				else printf("优化率为%f%%\n", (tim2 - tim) / tim2 * 100);
				getchar();
			}
			savefile(filename, valuation, root, flag, tim);
			getchar();
			break;
		case 2:
			if (createsudoku()) {
				printf("GAME OVER！\n");
			}
			getchar();
			break;
		case 0:
			break;
		}
	}
	printf("欢迎再次体验本系统！\n");
	return 0;
}

status DPLL(Root root, int *valuation) {//DPLL解SAT 
int t, flag, L;
int flag3=0; 
	int i = 0;
	int j = 0;
	flag = 1;
	Stack visit;//栈
	Word lb;//新建一个链表
	lb = (Word)malloc(sizeof(word)*(2 * root->varnum + 1));//变元表 
	visit = (Stack)malloc(sizeof(stack)*(root->varnum + 1));//栈，方便回溯 
	for (i = 0; i < root->varnum + 1; i++) {//初始化 
		visit[i].literal = 0;
		visit[i].value = 0;
		lb[i].clahead = NULL;
		lb[i].liter = NULL;
		lb[i].next = NULL;
		lb[i].L = 0;
	}
	for (i; i <= 2 * root->varnum; i++) {///初始化
		lb[i].clahead = NULL;
		lb[i].liter = NULL;
		lb[i].next = NULL;
		lb[i].L = 0;
	}
	liternum(root, &lb);//建立变元表 
	i = 0;
	L = variable_decide(root, valuation);//决策变量 
	visit[i].literal = L;
	visit[i].value = valuation[L];
	i++; 
	while (1) {
		if (flag3!=-2&&evaluateClause(root, L, valuation)){//flag==-2表示存在空子句，判断是否存在冲突 
			cnfdeduce(&root, L, valuation[L], &lb);//化简 
			if ((L = variable_decide(root, valuation))==-1) //如果子句集为空，则说明可满足， 如果存在空子句，L==-2, 
			return OK; //可满足 
			else if(L!=-2){//L!=-2，说明决策出变量，入栈 
				visit[i].literal = L;
				visit[i].value = valuation[L];
				i++;
			}
			else{//存在冲突 
				flag3=-2;//含有空子句，不满足 
			}
		}
		else {//回溯， 
			flag3=0;
			for (j = i - 1; j >= 0; j--) {
				t = visit[j].literal;
				if (visit[j].value == 0) {//栈顶是0，则说明已翻转， 
					visit[j].value = 1;//恢复 
					valuation[t] = 1;
					valuation[0]++;
					if(j!=i-1)cnfrestore(&root, t,&lb);
					continue;
				}
				else if (visit[j].value == 1) {//栈里第一个未翻转变量 
					visit[j].value = 0;//翻转 
					valuation[t] = 0;
					L = t;
					if(j!=i-1)cnfrestore(&root, L,&lb);//恢复 
					i = j + 1;
					break;
				}
			}
			if (j == -1) return ERROR;
		}
	}
}

status evaluateClause(Root root, int L, int *value) {//判断是否一定存在冲突，单子句冲突或含有空子句 
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
void cnfrestore(Root *root, int L, Word *lb) {//子句恢复
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
void cnfdeduce(Root *root, int L, int flag, Word *lb) {//子句化简 
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
	while (p) {//向后遍历
		r = p->clahead;
		if (r->clamark == 0)//未删除 
		r->clamark = L;//标记更改表示删除改
		p = p->next;
	}
	while (q) {//向后遍历 
		r = q->clahead;
		t = q->liter;
		if (r->clamark == 0) {//未删除 
			r->litnum--;
			litnum[q->L]--;//该子句变元数目减1  
			t->litmark = L;//标记更改表示删除 
		}
		q = q->next;
	}
}
int variable_decide(Root root, int *valuation) {//决策变量
	int ooo=valuation[0];
	int L, t, max;int visit=0;//查看cnf是否为空 
	int i = 0;L=-2;
	clause*p, *r;
	literal *q;
	int min;
	p = root->fircal;
	r = p;
	for (i = 0; i < root->calnum; i++) {
		if (p->clamark == 0) {//子句未删除 
			if(p->litnum==0) return -2;//存在空子句返回-2 
			min = p->litnum;
			r = p;
			visit=1; 
			break;
		}
		p = p->nextcal;
	}
	for (; i < root->calnum; i++) {
		if (p->clamark == 0) {//子句未删除 
			visit=1;
			if(p->litnum==0) return -2;//存在空子句返回-2 
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
						return t;//返回已赋值的变元 
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
			L = abs(q->liter);//最短子句的第一个未删除变元 
			break;
		}
		q = q->next;
	}
	if(visit==0){
		L=-1;//子句集为空 
		return L;
	}
	if(L>0){
		valuation[L] = 1;//默认赋值为1  
		valuation[0]--;
	} 
	return L;
}
void liternum(Root root, Word *lb) {//构建变元表 
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
status Testcnf(Root root) {//验证解析正确性 
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
status Loadcnf(char *filename, Root* root, int flag) {//读取解析cnf公式 
	char c, d;
	int flag2=0; 
	clause* p, *t;
	literal*q, *r;
	int data;
	int i = 0;
	if (flag) {
		printf("输入cnf文件名！\n");
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
		printf("文件加载完成！\n");
		return OK;
	}
	else printf("文件加载失败"); 
	return ERROR;
	
}

status savefile(char *filename, int *valuation, Root root, int flag, double t) {//保存文件 
	FILE *fp;
	int i = 0;
	for (i = 0; i < 60; i++) {//将文件名后缀改成.res 
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
	fprintf(fp, "s %d\nv ", flag);//以下按要求存储数据 
	if (flag) {
		for (i = 1; i < root->varnum + 1; i++) {
			if (valuation[i] == 1)fprintf(fp, "%d ", i);//为1 则存正值 
			else fprintf(fp, "-%d ", i);//否则存负值 
		}
	}
	fprintf(fp, "\n");
	fprintf(fp, "t %f", t);
	fclose(fp);
	printf("结果保存成功！\n");
	return OK;
}

status createsudoku() {//数独模块 
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
	for (i = 3; i < 6; i++) {//第五个宫格// 
		for (j = 3; j < 6; j++) {
			ls[i - 3][j - 3] = (k % 9) + 1;
			sudoku[i][j] = (k % 9) + 1;
			k++;
		}
	}
	//根据矩阵的行列变换生成数独初始完整格局 
	//以下顺序不可变
	for (i = 3; i < 6; i++) {//第四个宫格
		for (j = 0; j < 3; j++) {
			sudoku[i][j] = sudoku[(i + 2) % 3 + 3][j + 3];
		}
	}
	for (i = 3; i < 6; i++) {//第六个宫格
		for (j = 6; j < 9; j++) {
			sudoku[i][j] = sudoku[(i + 1) % 3 + 3][j - 3];
		}
	}
	for (i = 0; i < 3; i++) {//第二个宫格
		for (j = 3; j < 6; j++) {
			sudoku[i][j] = ls[i][(j + 2) % 3];
		}
	}
	for (i = 0; i < 3; i++) {//第一个宫格
		for (j = 0; j < 3; j++) {
			sudoku[i][j] = sudoku[i + 3][(j + 2) % 3];
		}
	}
	for (i = 0; i < 3; i++) {//第三个宫格
		for (j = 6; j < 9; j++) {
			sudoku[i][j] = sudoku[i + 3][(j - 1) % 3 + 6];
		}
	}
	for (i = 6; i < 9; i++) {//第7个宫格
		for (j = 0; j < 3; j++) {
			sudoku[i][j] = sudoku[i - 3][(j + 1) % 3];
		}
	}
	for (i = 6; i < 9; i++) {//第8个宫格
		for (j = 3; j < 6; j++) {
			sudoku[i][j] = sudoku[i - 3][(j + 1) % 3 + 3];
		}
	}
	for (i = 6; i < 9; i++) {//第九个宫格
		for (j = 6; j < 9; j++) {
			sudoku[i][j] = sudoku[i - 3][(j + 1) % 3 + 6];
		}
	}
	slove = fopen("slove.txt", "w");
	for (i = 0; i < 9; i++) {//将原始完整数独保存
		for (j = 0; j < 9; j++) {
			fprintf(slove, "%d ", sudoku[i][j]);
		}
		fprintf(slove, "\n");
	}

	for (i = 81; i > 0; i--) {
		k = rand() % 81;
		sudoku[k / 9][k % 9] = 0;
	}
	printf("目前的数独格局如下：\n");
	for (i = 0; i < 9; i++) {
		for (j = 0; j < 9; j++) {
			if (sudoku[i][j])
				printf("%d ", sudoku[i][j]);
			else printf("_ ");
		}
		printf("\n");
	}
	printf("是否要继续加入数据\n");
	printf("0.NO直接看答案 1.YES我要做数独\n");
	scanf("%d", &op);
	while (op) {//加数据的话 
		printf("输入行列值\n");
		scanf("%d %d %d", &r, &s, &w);
		sudoku[r - 1][s - 1] = w;//加的数据为w 
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
		//将数独变为cnf公式保存在sudoku.cnf文件中
		fprintf(fp, "p cnf 729 %d\n", t + 10530); 
		for (i = 0; i < 9; i++) {//保存已经存在的数
			for (j = 0; j < 9; j++) {
				if (k = sudoku[i][j]) {//处理本来存在的单子句 
					fprintf(fp, "%d 0\n", 81 * i + 9 * j + k);//按照 81 * i + 9 * j + k的规则将第i+1行j+1列值为k转换成变元 
				}
			}
		}
		for (i = 1; i < 10; i++) {
			for (j = 1; j < 10; j++) {
				for (k = 1; k < 10; k++) {
					fprintf(fp, "%d ", 81 * (i - 1) + 9 * (j - 1) + k);//每个cell必为1-9 
				}
				fprintf(fp, "0\n");
			}
		}
		for (i = 1; i < 10; i++) {//
			for (j = 1; j < 10; j++) {
				for (k = 1; k < 9; k++) {
					for (t = k + 1; t < 10; t++) {
						fprintf(fp, "-%d ", 81 * (i - 1) + 9 * (j - 1) + k);//每个cell不可能同时为1 2或1 3...... 
						fprintf(fp, "-%d 0\n", 81 * (i - 1) + 9 * (j - 1) + t);
					}
				}
			}
		}
		for (i = 1; i < 10; i++) {//对行处理，每一行一定存在1-9&&每一行不存在相同的数
			for (k = 1; k < 10; k++) {
				for (j = 1; j < 10; j++) {
					fprintf(fp, "%d ", 81 * (i - 1) + 9 * (j - 1) + k);
				}
				fprintf(fp, "0\n");
			}
			for (k = 1; k < 10; k++) {//每一行不存在相同的数 
				for (j = 1; j < 9; j++) {
					for (t = j + 1; t < 10; t++) {
						fprintf(fp, "-%d ", 81 * (i - 1) + 9 * (j - 1) + k);
						fprintf(fp, "-%d 0\n", 81 * (i - 1) + 9 * (t - 1) + k);
					}
				}
			}
		}
		for (j = 1; j < 10; j++) {//对列处理  方式同行
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
		//对3*3块处理 
		for (m = 0; m < 3; m++) {//第m+1行的3*3块 
			for (n = 0; n < 3; n++) {//第n+1列的3*3块 
				for (k = 1; k < 10; k++) {
					for (i = 1; i < 4; i++) {
						for (j = 1; j < 4; j++) {
							fprintf(fp, "%d ", 81 * ((i - 1) + 3 * m) + 9 * ((j - 1) + 3 * n) + k);//每个块必有1 2 3 4 ....9 
						}
					}
					fprintf(fp, "0\n");
				}
				//但每个块不可能有相同数字 
				for (k = 1; k < 10; k++) {//余下单独处理 
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
		if (Loadcnf(filename, &root2, 0)) {//调用DPLL解数独 
			num = root2->varnum + 1;
			valuation2 = (int*)malloc(sizeof(int)*(num));
			valuation2[0] = root2->varnum;
			for (i = 1; i <= root2->varnum; i++) {
				valuation2[i] = 0;
			}
			system("cls");
			printf("\n\n\n\n");
			if (DPLL(root2, valuation2) == 0) {//如果上一步赋的值数独不成立则返回恢复上一步的格局 
				printf("该步骤无解！\n请重新输入！\n");
				sudoku[r - 1][s - 1] = 0;
			}
			else {
				printf("可解！\n");
			}
			printf("\n\n目前的数独格局如下：\n");
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
		printf("是否要继续加入数据\n");
		printf("0.结束填补直接看答案  1.继续填补\n");
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
	//将数独变为cnf公式保存在sudoku.cnf文件中
	//以下注释同上 
	fprintf(fp, "p cnf 729 %d\n", t + 10530);
	for (i = 0; i < 9; i++) {//保存已经存在的数
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
	for (i = 1; i < 10; i++) {//对行处理，每一行一定存在1-9&&每一行不存在相同的数
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
	for (j = 1; j < 10; j++) {//对列处理  方式同行
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

		printf("\n\n目前的数独格局如下：\n");
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
			printf("数独的解为:\n");
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
