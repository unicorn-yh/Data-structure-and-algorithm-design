/*约瑟夫问题是一个经典的问题。已知 n 个人（不妨分别以编号 1，2 ，3，…，n 代表 ）围坐在一张圆桌周围，
从编号为 k 的人开始，从1开始顺时针报数 1, 2, 3, ...，顺时针数到m 的那个人，出列并输出。
然后从出列的下一个人开始，从1开始继续顺时针报数，数到 m的那个人，出列并输出，…依此重复下去，
直到圆桌周围的人全部出列。

输入：n, k, m
输出：按照出列的顺序依次输出出列人的编号，编号中间相隔一个空格,每10个编号为一行。

非法输入的对应输出如下：
a)输入：n、k、m任一个小于1；输出： n,m,k must bigger than 0.
b)输入：k>n；输出： k should not bigger than n.
例:输入：9,3,2；输出：4 6 8 1 3 7 2 9 5 */ 

#include <bits/stdc++.h>
using namespace std;
int a[100010]={0};
int main(){
    int n,k,m,i,j,count=0;
    scanf("%d,%d,%d",&n,&k,&m);
    if(n<1||k<1||m<1){
        printf("n,m,k must bigger than 0.\n");
        return 0;
    }
    if(k>n){
        printf("k should not bigger than n.\n");
        return 0;
    }
    for(int i=0;i<n;i++)a[i]=i+1;
    i=k-1;
    while(n>1){
        i=(i+m-1)%n;
        printf("%d",a[i]);
        count++;
        if(count%10==0)printf("\n");
        else printf(" ");
        for(j=i+1;j<n;j++)a[j-1]=a[j];
        n--;
        if(n==i)i=0;
    }
    printf("%d\n",a[i]);
    return 0;
}