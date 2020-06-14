#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<algorithm>
#include<fstream>
#include<graphics.h>
#include <windows.h>


using namespace std;

class road//公交路线类，可能需要根据站点找到最近的公交线路
{
public:
	~road();
	const int num;//几号线
	const int direction;//表示方向,C顺时针表示1，R逆时针表示0
	const int stopsnum;//站点总个数
	int* a;//所经过的站点
	void inputdata(int x1, int x2, int x3) {
		*(int*)&num = x1;
		*(int*)&direction = x2;//表示不存在
		*(int*)&stopsnum = x3;
	}
	void make(int n) {
		a = new int[n + 1];
		a[n] = 0;//0表示结束
	}
	void makenum(int i, int n) {
		a[i] = n;
	}
	road(int x1 = 0, int x2 = 0, int x3 = 0) :num(x1), direction(x2), stopsnum(x3) { a = NULL; }

};
road::~road()
{
	*(int*)&num = 0;
	*(int*)&direction = -1;//表示不存在
	*(int*)&stopsnum = 0;
	if (a)	delete[]a;
	a = NULL;
}


class stop {//站点类,需要读取数据并写入数据，可能需要根据坐标查找最近的站点
public:
	const int num;//站点总数目
	const int* x;//站点坐标x
	const int* y;//站点坐标y
	stop(int x1) :num(x1), x(new int[x1]), y(new int[x1]) {}
	void inputdata(int i, int x1, int x2) {
		*(int*)&x[i] = x1;
		*(int*)&y[i] = x2;
	}
	void selectstop(int x1, int y1, int* result, road* lines, int linesnum) {//选择最近的站点
		int* s;
		int* t;
		int* r;
		int i = 0; int j = 1;
		s = new int[num];
		t = new int[num];
		r = new int[num + 1];
		for (i = 0; i < num; i++) r[i + 1] = 0; r[num] = 0;
		for (i = 0; i < linesnum; i++) {
			for (j = 0; j < lines[i].stopsnum; j++) {
				r[lines[i].a[j]]++;//找到在公交线上的站点
			}
		}
		for (i = 0; i < num; i++) {
			if (r[i + 1]) {
				s[i] = pow(x[i] - x1, 2) + pow(y[i] - y1, 2);
				t[i] = s[i];
			}
			else {
				s[i] = 2147483647;//表示该站点到不了
				t[i] = s[i];
			}
		}
		sort(s, s + num);

		for (i = 0, j = 1; i < num; i++) {
			if (t[i] == s[0]) {
				result[j++] = i + 1;
			}
		}
		result[0] = j - 1;
		if (s)delete[]s;
		s = NULL;
		if (t) delete[]t;
		t = NULL;
		if (r) delete[]r;
		r = NULL;
	}
	~stop() {
		if (x) {
			delete[]x;
			x = NULL;
		}
		if (y) {
			delete[]y;
			y = NULL;
		}
	}
};






class transfer {//定义转乘类，包括转乘的两条线路和经过的站点
public:
	int prepline;//转乘前的路线
	int nextline;//转乘后的路线
	int station;//经过的站点
	class transfer* transferline;//指向下一条线转乘的指针
	class transfer* nextmethod;//该转乘的经过其他站点的方法
	~transfer() {//析构函数自动释放所有的内存
		if (transferline) {
			delete transferline;
			transferline = NULL;
		}
		if (nextmethod) {
			delete nextmethod;
			nextmethod = NULL;
		}
	}
};


class matrix {
public:
	const int m;//公交线路数
	const int n;//具体路线数,区分方向
	transfer*** A;//一次换乘
	transfer*** B;//

	void makeAonetransfer(const road* lines) {//创建一个一次转乘矩阵,B同步建立
		int i, j, k, x;
		int flag = 0;
		transfer* p;
		transfer* q;
		for (i = 0; i < n; i++) {
			for (j = 0; j < n; j++) {
				flag = 0;
				p = A[i][j];
				q = B[i][j];
				if (i == j) {//相同路线不转乘
					A[i][j] = NULL;
					B[i][j] = NULL;
				}
				else {
					for (k = 0; k < lines[i].stopsnum; k++) {//遍历第i条线所经过的站点k
						for (x = 0; x < lines[j].stopsnum; x++) {//遍历第j条线所经过的站点x
							if (lines[i].a[k] == lines[j].a[x]) {//如果站点相同，说明可以转乘
								if (flag == 0) {//此时还没有可以转乘的情况
									p = new transfer;//构建相应的转乘对象
									q = new transfer;
									A[i][j] = p;
									B[i][j] = q;
									flag = 1;//将标志改为已有转乘方法	
								}
								else {//此时已有转乘的方法
									p->nextmethod = new transfer;//构建相应的转乘对象，表示下一条转乘方法
									q->nextmethod = new transfer;
									p = p->nextmethod;
									q = q->nextmethod;
								}
								p->prepline = i;//转乘前路线为i
								p->nextline = j;//转乘后路线为j
								p->station = lines[i].a[k];//在该站点转乘
								p->transferline = NULL;
								q->prepline = i;
								q->nextline = j;
								q->station = lines[i].a[k];
								q->transferline = NULL;
								break;
							}
						}
					}
					if (flag == 0) {//不能转乘
						A[i][j] = NULL;
						B[i][j] = NULL;
					}
					else {
						p->nextmethod = NULL;
						q->nextmethod = NULL;
					}
				}
			}
		}
	}

	void makeBtransfermartix(const road* lines) {//求转乘矩阵
		transfer*** C;//
		transfer* p, * q, * r, * t, * t2;
		int i = 0, j = 0, k = 0;
		int num1, num2;
		int flag1 = 0;
		C = new transfer * *[n];
		for (i = 0; i < n; i++) {
			C[i] = new transfer * [n];//构造临时矩阵C
		}
		for (i = 0; i < n; i++) {
			for (j = 0; j < n; j++) {
				flag1 = 0;
				for (k = 0; k < n; k++) {
					p = A[i][k]; q = B[k][j];//p,q分别指向i转乘到k，k转乘到j的转乘方法
					if (p == NULL || q == NULL) {//通过当前k不能转乘
						continue;
					}
					while (p) {//p不为空，即当前仍存在着转乘方法
						num1 = p->station;//在num1转乘
						q = B[k][j];
						while (q) {
							num2 = q->station;//在num2转乘
							if (isorder(num1, num2, lines, k)) {//num2在num1后面
								//以下为创建n+1次转乘矩阵C
								//
								if (flag1 == 0) {//当前还没有转乘过
									C[i][j] = new transfer;
									r = C[i][j];
									flag1 = 1;
								}
								else {//转乘过
									r->nextmethod = new transfer;
									r = r->nextmethod;
								}
								t = q; t2 = r;
								r->prepline = p->prepline; r->nextline = p->nextline; r->station = p->station;
								while (t) {
									r->transferline = new transfer;
									r = r->transferline;
									r->prepline = t->prepline;
									r->nextline = t->nextline;
									r->station = t->station;
									r->nextmethod = NULL;
									t = t->transferline;
								}
								r->transferline = NULL;
								r = t2;
							}
							q = q->nextmethod;
						}
						p = p->nextmethod;
					}
				}
				if (flag1 == 0) C[i][j] = NULL;
				else  r->nextmethod = NULL;
			}
		}
		for (i = 0; i < n; i++) {
			for (j = 0; j < n; j++) {
				if (B[i][j])
					delete B[i][j];
				B[i][j] = C[i][j];
				C[i][j] = NULL;
			}
		}


	}

	int isorder(int num1, int num2, const road* lines, int k) {//判断站点num1能否坐到num2
		int i = 0, j = 0;
		int flag = 0;
		for (i = 0; i < lines[k].stopsnum; i++) {
			if (num1 == lines[k].a[i]) break;
		}
		for (j = i + 1; j < lines[k].stopsnum; j++) {
			if (num2 == lines[k].a[j]) {
				flag = 1;
				break;
			}
		}
		if (flag == 1) return 1;
		else return 0;
	}

	matrix(int x, int y) :m(x), n(y) {//构造函数
		int i = 0, j = 0;
		A = new transfer * *[y];
		B = new transfer * *[y];
		for (i; i < y; i++) {
			A[i] = new transfer * [y];
			B[i] = new transfer * [y];
		}
		for (i = 0; i < y; i++) {
			for (j = 0; j < y; j++) {
				A[i][j] = NULL;
				B[i][j] = NULL;
			}
		}
	}
	~matrix()
	{
		transfer* p, * q, * r;
		int i, j = 0;
		for (i = 0; i < n; i++) {
			for (j = 0; j < n; j++) {
				if (B[i][j])
					delete B[i][j];
				/*p = B[i][j];
				while (p) {//释放原来B矩阵中的内容
					r = p->nextmethod;
					q = p->transferline;
					while (q) {
						delete p;
						p = q;
						q = q->transferline;
					}
					delete p;
					p = r;
				}*/
				B[i][j] = NULL;
			}
		}
		for (i = 0; i < n; i++) {
			for (j = 0; j < n; j++) {
				if (A[i][j])
					delete A[i][j];
				
				A[i][j] = NULL;
			}
		}
		for (i = 0; i < n; i++) {
			if (B[i]) {
				delete[]B[i];
				B[i] = NULL;
			}
			if (A[i]) {
				delete[]A[i];
				A[i] = NULL;
			}
		}
		if (A) {
			delete[]A;
			A = nullptr;
		}
		if (B) {
			delete[]B;
			B = nullptr;
		}
	}
};


class DJSpath {
#define INFINITY 65535//表示无穷大
public:
	int vexnum;//结点数量
	int** arc;//邻接矩阵
	DJSpath(int m, const int linesnum, const road* lines, const stop* stops) {
		vexnum = m;
		int i = 0, j = 0; int t;
		arc = new int* [vexnum];
		for (i = 0; i < vexnum; i++) {
			arc[i] = new int[vexnum];
		}
		int vex1, vex2;
		for (i = 0; i < vexnum; i++) {
			for (j = 0; j < vexnum; j++) {
				if (i == j) arc[i][j] = 0;
				else arc[i][j] = INFINITY;
			}
		}
		for (i = 0; i < linesnum; i++) {
			for (j = 0; j < lines[i].stopsnum - 1; j++) {
				vex1 = lines[i].a[j] - 1;
				vex2 = lines[i].a[j + 1] - 1;
				t = pow(abs(stops->x[vex1] - stops->x[vex2]), 2) + pow(abs(stops->y[vex1] - stops->y[vex2]), 2);
				arc[vex1][vex2] = sqrt(t);
			}
		}
	}
	~DJSpath() {
		int i = 0;
		if (arc == NULL) return;
		for (i = 0; i < vexnum; i++) {
			if (arc[i]) {
				delete[]arc[i];
				arc[i] = NULL;
			}
		}
		if (arc) {
			delete[]arc;
			arc = NULL;
		}
	}

	void ShortestPath_DIJ(int v0, int* Path)
	{
		int* Dist, * final; int k = 1;
		Dist = new int[vexnum];
		final = new int[vexnum];
		int i, j, v, w, min;
		for (v = 0; v < vexnum; ++v)
		{
			final[v] = FALSE;//标志未求得最短路径
			Dist[v] = arc[v0][v];
			if (arc[v0][v] < INFINITY) Path[v] = v0;
			else Path[v] = -1;

		}
		Dist[v0] = 0;
		final[v0] = TRUE;
		Path[v0] = -1;
		for (i = 0; i < vexnum; ++i)        
		{
			min = INFINITY;
			for (w = 0; w < vexnum; ++w) {
				if (!final[w])
					if (Dist[w] < min)
					{
						v = w;
						min = Dist[w];
					}
			}

			final[v] = TRUE;
			for (w = 0; w < vexnum; ++w)
			{
				if (!final[w] && (min + arc[v][w] < Dist[w]))
				{
					Dist[w] = min + arc[v][w];
					Path[w] = v;
				}
			}

		}
		if (final) {
			delete[]final;
			final = NULL;
		}
		if (Dist) {
			delete[]Dist;;
			Dist = NULL;
		}
	}


};

void play(int stopsnum, stop* stops, road* lines, int linesnum);
void selectline(int num, int* result, road lines[], int linesnum);
int isthesameline(int* result, int* result2, int v0, int v1, road* lines);
void iscantrasfer(int* result, int* result2, matrix* A, transfer** p, int v0, int v1, road* lines);
int isarrvive(int num1, int num2, road* lines, int k);
void palyline(int v0, int v1, int k, road* lines, stop* stops);


int main(void) {
	ifstream infile;//读取文件


	stop* stops;//站点坐标
	road* lines;//路线
	DJSpath* shortpath;
	int stopsnum;//站点总数
	int routenum;//指公交线路的总数 例如6条
	int linesnum;//具体的线路总数
	int  selectmodel;//选择模式

	char c;//判断
	char s[6];//输出路线数字
	MOUSEMSG getmouse1, getmouse2,getmouse;


	int x, y; int i = 0, j = 0; int x1, x2;

	infile.open("stop.txt");
	if (!infile.is_open()) {
		cout << "open file failure" << endl;
		system("pause");
		return 0;
	}

	infile >> stopsnum;
	stops = new stop(stopsnum);

	while (!infile.eof()) {
		infile >> x1;
		infile >> x2;
		stops->inputdata(i, x1, x2); i++;
	}
	i = 0;

	infile.close();
	infile.open("lines.txt");
	if (!infile.is_open()) {
		cout << "open file failure" << endl;
		system("pause");
		return 0;
	}

	infile >> routenum;
	lines = new road[2 * routenum];//最多2*routenum条线路
	for (i = 0; !infile.eof(); i++) {
		int x1, x3, x2;
		int j = 0; int snum;//记录下经过的站台
		infile >> x1;
		infile >> c;
		if (c == 'R') x2 = 0;//0表示R逆时针
		else x2 = 1;//C表示顺时针
		infile >> x3;//经过的站点总数
		lines[i].inputdata(x1, x2, x3);
		lines[i].make(lines[i].stopsnum);
		for (j = 0; j < lines[i].stopsnum; j++) {
			infile >> snum;
			lines[i].makenum(j, snum);
		}
	}
	linesnum = i;//具体的线路总数，区分顺时针和逆时针
	infile.close();//站点和路线记录完成

	cout << "请输入你选择的功能：\n";
	cout << "1.最短路径\n2:最少换乘\n0:退出" << endl;
	cin >> selectmodel;
	while (selectmodel) {
		play(stopsnum, stops, lines, linesnum);//画出站点路线图
	//cout << "点击选择起始点，和终点！" << endl;
		while (true) {//选出点击的第一个点和第二个点
			int x, y;
			getmouse1 = GetMouseMsg();
			if (getmouse1.uMsg == WM_LBUTTONDOWN) {
				getmouse2 = GetMouseMsg();
				while (true) {
					if (getmouse2.uMsg == WM_LBUTTONDOWN) break;
					else getmouse2 = GetMouseMsg();
				}
				break;
			}
		}
		int v0, v1, * result, * result2;//表示起始点
		int e1, e2;//选出与v0,v1对应的边
		result = new int[stopsnum];
		result2 = new int[stopsnum];
		stops->selectstop(getmouse1.x / 1.5, getmouse1.y / 1.5, result, lines, linesnum);//选出离出发点最近的站点
		v0 = result[1];
		stops->selectstop(getmouse2.x / 1.5, getmouse2.y / 1.5, result, lines, linesnum);
		v1 = result[1];
		selectline(v0, result, lines, linesnum);
		e1 = result[1];
		selectline(v1, result2, lines, linesnum);
		e2 = result2[1];
		setlinecolor(BLUE);
		settextcolor(RED);
		fillcircle(getmouse1.x / 1.5, getmouse1.y / 1.5, 3);
		fillcircle(getmouse2.x / 1.5, getmouse2.y / 1.5, 3);
		line(getmouse1.x / 1.5, getmouse1.y / 1.5, stops->x[v0 - 1], stops->y[v0 - 1]);
		line(stops->x[v1 - 1], stops->y[v1 - 1], getmouse2.x / 1.5, getmouse2.y / 1.5);
		char wordf[100];
		if (selectmodel == 1) {//计算最短路径
			shortpath = new DJSpath(stopsnum, linesnum, lines, stops);
			int* path; int m, n;//经过的站点
			path = new int[stopsnum];
			shortpath->ShortestPath_DIJ(v0 - 1, path);
			m = v1 - 1; n = path[m];
			
			sprintf(wordf, "%s", "最短路径路线为：");
			outtextxy(0, 0, wordf);
			while (n != -1) {
				line(stops->x[m], stops->y[m], stops->x[n], stops->y[n]);
				m = n; n = path[m];
			}

			delete shortpath;
			delete[]path;
		}
		else {
			int linet; int m, n; int k = 1;
			transfer* resultline = NULL, * p_temp;
			sprintf(wordf, "%s", "最少转乘路线为：");
			outtextxy(0, 0, wordf);

			if ((linet = isthesameline(result, result2, v0, v1, lines)) != -1) {//不用转乘的情况
				for (i = 0; i < lines[linet].stopsnum; i++) {
					if (v0 == lines[linet].a[i]) break;
				}
				palyline(v0, v1, linet, lines, stops);
			}
			else {
				matrix A(routenum, linesnum);
				A.makeAonetransfer(lines);//构建一次矩阵
				iscantrasfer(result, result2, &A, &resultline, v0, v1, lines);
				if (resultline) {//一次转乘可以到
					m = resultline->station;
					palyline(v0, m, resultline->prepline, lines, stops);
					palyline(m, v1, resultline->nextline, lines, stops);
				}
				else {//一次换乘不能到改多次
					while (1) {
						A.makeBtransfermartix(lines);
						iscantrasfer(result, result2, &A, &resultline, v0, v1, lines);
						if (resultline) {
							p_temp = resultline;
							m = resultline->station;
							palyline(v0, m, p_temp->prepline, lines, stops);

							while (p_temp->transferline) {
								m = p_temp->station;
								p_temp = p_temp->transferline;
								n = p_temp->station;
								palyline(m, n, p_temp->prepline, lines, stops);
							}
							m = p_temp->station;
							palyline(m, v1, p_temp->nextline, lines, stops);

						}
						break;
					}
					sprintf(wordf, "%s", "无法到达...");
					outtextxy(100, 0, wordf);
				}
			}
		}
		delete[] result;
		delete[]result2;
		sprintf(wordf, "%s", "点击屏幕继续.....");
		outtextxy(400, 000, wordf);
		while (true) {//点击退出
			getmouse = GetMouseMsg();
			if (getmouse.uMsg == WM_LBUTTONDOWN) {
				
				break;
			}
		}
		closegraph();
		system("cls");
		cout << "1.最短路径\n2:最少换乘\n0:退出" << endl;
		cin >> selectmodel;
	}
	
	delete stops;
	delete[]lines;
	system("pause");
	
	return 0;

}
void play(int stopsnum, stop* stops, road* lines, int linesnum) {//，作图初始化界面
	int i = 0, j = 0;
	initgraph(1300, 500);
	//setaspectratio(1, -1);
	setbkcolor(RGB(0, 128, 128));
	setaspectratio(1.5, 1.5);//设置放大因子为1.5
	cleardevice();
	setlinecolor(RGB(0, 0, 0));
	setlinestyle(PS_SOLID, 1);
	setfillcolor(RGB(0, 0, 0));
	char s[100];
	settextcolor(RED);
	settextstyle(16, 0, _T("宋体"));
	sprintf(s, "%s", "请单击分别选择起始点和终点！");
	outtextxy(300, 300, s);

	for (i = 0; i < stopsnum; i++) {
		settextcolor(BLACK);
		fillcircle(stops->x[i], stops->y[i], 3);
		sprintf(s, "%d", i + 1);
		outtextxy(stops->x[i] - 4, stops->y[i], s);
	}
	for (i = 0; i < linesnum; i++) {
		for (j = 0; j < lines[i].stopsnum - 1; j++) {
			line(stops->x[lines[i].a[j] - 1], stops->y[lines[i].a[j] - 1], stops->x[lines[i].a[j + 1] - 1], stops->y[lines[i].a[j + 1] - 1]);
			sprintf(s, "%d", lines[i].num);
			//outtextxy((stops->x[lines[i].a[j] - 1] + stops->x[lines[i].a[j + 1] - 1])/2-2, (stops->y[lines[i].a[j] - 1] + stops->y[lines[i].a[j + 1] - 1])/2-2, s);
		}
	}
}
void selectline(int num, int* result, road lines[], int linesnum) {//根据站点选路线,num为站点
	int i = 0; int j = 0; int k = 1;
	for (i = 0; i < linesnum; i++) {
		for (j = 0; j < lines[i].stopsnum; j++) {
			if (num == lines[i].a[j]) {
				result[k++] = i;//注意选出的路线为脚标
				break;
			}
		}
	}
	result[0] = k - 1;
}
int isthesameline(int* result, int* result2, int v0, int v1, road* lines) {
	int i = 0, j = 0, k = 0;
	int line;
	for (i = 1; i <= result[0]; i++) {
		for (j = 1; j <= result2[0]; j++) {
			if (result[i] == result2[j]) {
				line = result[i];
				for (k = 0; k < lines[line].stopsnum; k++) {
					if (lines[line].a[k] == v0) break;
				}
				for (k = k + 1; k < lines[line].stopsnum; k++) {
					if (lines[line].a[k] == v1) return line;
				}
			}
		}
	}
	return -1;
}
void iscantrasfer(int* result, int* result2, matrix* A, transfer** p, int v0, int v1, road* lines) {
	int i = 0, j = 0, k = 0;
	int m, n;
	int station;
	transfer* q, * r;
	for (i = 1; i <= result[0]; i++) {
		for (j = 1; j <= result2[0]; j++) {
			m = result[i]; n = result2[j];
			if (A->B[m][n]) {
				r = A->B[m][n];
				q = r;
				while (r->transferline)r = r->transferline;
				if (isarrvive(v0, q->station, lines, m) && isarrvive(r->station, v1, lines, n)) {
					*p = A->B[m][n];
					return;
				}
			}
		}
	}
	p = NULL;
}
int isarrvive(int num1, int num2, road* lines, int k) {
	int i = 0;
	for (i = 0; i < lines[k].stopsnum; i++) {
		if (num1 == lines[k].a[i]) break;
	}
	for (i = i + 1; i < lines[k].stopsnum; i++) {
		if (num2 == lines[k].a[i]) return 1;
	}
	return 0;
}
void palyline(int v0, int v1, int k, road* lines, stop* stops) {
	int i = 0; int m; char s[6];
	for (i = 0; i < lines[k].stopsnum; i++) {
		if (v0 == lines[k].a[i]) break;
	}
	for (; i < lines[k].stopsnum - 1; i++) {
		sprintf(s, "%d", lines[k].num);
		if (lines[k].direction) strcpy(&s[strlen(s)], "C");
		else strcpy(&s[strlen(s)], "R");
		outtextxy((stops->x[lines[k].a[i] - 1] + stops->x[lines[k].a[i + 1] - 1]) / 2 - 4, (stops->y[lines[k].a[i] - 1] + stops->y[lines[k].a[i + 1] - 1]) / 2, s);
		line(stops->x[lines[k].a[i] - 1], stops->y[lines[k].a[i] - 1], stops->x[lines[k].a[i + 1] - 1], stops->y[lines[k].a[i + 1] - 1]);
		if (lines[k].a[i + 1] == v1) break;
	}
}