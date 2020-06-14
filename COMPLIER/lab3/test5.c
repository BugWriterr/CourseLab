struct A {
       int  a;
       int b;
   };
int main()  
{
    struct A m,n;
    m=n;
    m.a=n.a+n.b;
    return 1;
}