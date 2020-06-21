// int fac(int a)
// {
//     if (a==1) return 1;
//     return a*fac(a-1);
// }
// int main()
// {
//     int x;
//     x=read();
//     write(fac(x));
//    return 1;
// }
/*int main()  
{
    int x[10][20],i,j=1;
    for(i=0;i<10;i++)
        x[i][j]=read();
    return 1;
}
*/

int a[10];
int b[5][6];
int c,d;

int main()
{
    int x[10],i,j;
    for (i = 0; i < 10; i++)
       x[i]=read();
     for (i = 0; i < 10; i++){
         j=x[i];
         write(j);
         write(x[i]);
     }
    return 1;
}

/*
int main()
{
    int x[10], i;
    for (i = 0; i < 10; i++)
        i = read();
    for (i = 0; i < 10; i++)
        write(i);
    return 1;
}*/
