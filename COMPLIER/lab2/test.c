
/*int a,b,c;
float m,n;
int fibo(int a){
    if(a==1||a==2)return 1;
    return fibo(a-1)+fibo(a-2);
}
int main(){
    int m,n,i;
    m=read();
    i-1;
    while(i<m){
        n=fibo(i);
        write(n);
        i=i+1;
    }
    //return 1;
}*/




int f3()
{
   int a,b=0;
   if (a-12.3) continue;
   else   break;
   while ( a || f3()) {while (1) break;continue;}
   for(a=1;a>0 && f3()>0;a++)
 	if (a+b==0.0) break;
   return 1;
}

/*
int f5(int a)  
{
    float x[10][20],y=12.3;
    x=a[1]+f5[1];
    x[1]=x[1][y]+x[1+1][1];
    return y;
}*/

/*
int f2(int a,int b)
{
    int a,b=0;
    a+b=10;
    (a+b)++;
    ++a++;
    return 12.3;
}
*/
/*int x,y[10],z[3][4][5];
int f1(int m,int n,int l)
{   
    int a;
    int m,n=0;//标识符重复定义
    f1=3;//对函数名采用非函数调用形式访问
    a = 0;//
    d=0;//使用未定义的变量
    b();//使用未声明的函数
    a();//对非函数名采用函数调用形式
    //没有return语句
}

int f2(int a,int b)
{
    
    f1(1,2);//函数调用参数不匹配
    f1(1,2,'a');//参数类型不匹配
    f1[0];//对非数组变量采用下标形式访问
    a[-5];//对非数组采用下标形式访问
    a+b=10;//赋值号左边不是左值
    a+'c';//类型不匹配，用的强类型
    (a+b)++;//对非左值进行自增
    ++a++;//对非左值进行自增
    return 12.3;//返回类型不一致
}
int f3()
{
   int a,b=0;
   if (a-b) continue;//continue不在循环内
   else break;//break不在循环内
   while ( a || f2(1,2)) {while(1) break;continue;}
   for(a=1;a>0 && f2(1,2)>0;a++)
 	if (a+b==0) break;
   return y;
}

int f5(int a)  
{
    float x[10][20],y=12.3;
    x=a[1];
    x[1][5]=x[1.2][3]+x[2][1];
    z[2][4]=5;//维数错误
    z[2][2][2]=1;//正常访问
    return y;//返回值类型错误
}*/
/*
float f4(float x)
{
    struct A
    {
        int a;
        float b;
        char c;
    }m;
    m=12;//赋值号左边不能是左值
    m++;
    m.b=17;
    x.a=m.b;
    m.d=m.a.a;
    
}
*/