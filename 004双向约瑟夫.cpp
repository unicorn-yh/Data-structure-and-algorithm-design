/*我们不妨将经典的约瑟夫问题进行扩展，变成一个双向的约瑟夫问题。
已知 n 个人（不妨分别以编号 1，2，3，...，n 代表 ）围坐在一张圆桌周围，
首先从编号为 k 的人从 1 开始顺时针报数，1, 2, 3, ...，记下顺时针数到 m 的那个人，
同时从编号为 k 的人开始逆时针报数，1, 2, 3, ...，数到 m 后，两个人同时出列。
然后从出列的下一个人又从 1 开始继续进行双向报数，数到 m 的那两个人同时出列，...；。
依此重复下去，直到圆桌周围的人全部出列。直到圆桌周围只剩一个人为止。
如果双向报数报到 m 时落在同一个人身上，那本次出列的只有一个人。
例如：5,1,2。则总共5个人，从1开始顺时针报数，数到2，定位编号2；同时从1开始报数数到2，定位编号5；
2和5同时出列。然后继续开始报数，顺时针报数3,4，定位到4；逆时针报数4,3，定位3；4和3同时出列。
最后剩余的为编号1。输出为：2-5,4-3,1,。
如果输入：6,2,3。则输出：4-6,2,1-3,5,。其中第2次只输出一个2，表示第二次双向报数时，
恰好都落在编号2上，所以只有一个编号出列。

输入：
n,k,m

输出：
按照出列的顺序依次输出编号。同时出列编号中间用减号"-”连接。

非法输入的对应输出如下
a)输入：n、k、m任一个为0; 输出：n,m,k must bigger than 0.
b)输入：k>n; 输出：k should not bigger than n.*/

#include <bits/stdc++.h>
using namespace std;
typedef struct node{
    int num;
    struct node *clockwise;
    struct node *anticlockwise;
}NODE;
int main(){
    int n,k,m;
    scanf("%d,%d,%d",&n,&k,&m);
    if(n<1||k<1||m<1){
        printf("n,m,k must bigger than 0.\n");
        return 0;
    }
    else if(k>n){
        printf("k should not bigger than n.\n");
        return 0;
    }
    int cnt=n;
    NODE *head,*q,*q0,*q1,*q2; //q0用来赋值，q1和q2用来走顺时逆时
    q0=(NODE*)malloc(sizeof(NODE));
    head=q0;
    q0->num=1;
    for(int j=2;j<=n;j++){
        q=(NODE*)malloc(sizeof(NODE));
        q->num=j;
        q0->clockwise=q;
        q0=q0->clockwise;
        q->clockwise=head;
    }
    q=head;
    q0=q->clockwise;
    for(int j=0;j<n;j++){
        q0->anticlockwise=q;
        q0=q0->clockwise;
        q=q->clockwise;
    }
    q=head;
    for(int j=1;j<k;j++) q=q->clockwise;
    q1=q;
    q2=q;
    while(cnt){
        for(int j=1;j<m;j++){
            q1=q1->clockwise;
            q2=q2->anticlockwise;
        }
        if(q1->num==q2->num){
            cnt--;
            printf("%d,",q1->num);
            NODE *temp1=q1->anticlockwise;
            NODE *temp2=q2->clockwise;
            temp1->clockwise=temp2;
            temp2->anticlockwise=temp1;
            q1=temp2;
            q2=temp1;
        }
        else{
            cnt-=2;
            printf("%d-%d,",q1->num,q2->num);
            NODE *temp1=q1->anticlockwise;
            temp1->clockwise=q1->clockwise;
            temp1->clockwise->anticlockwise=temp1;
            q1=temp1->clockwise;
            NODE *temp2=q2->clockwise;
            temp2->anticlockwise=q2->anticlockwise;
            temp2->anticlockwise->clockwise=temp2;
            q2=temp2->anticlockwise;
        }
    }
    printf("\n");
    return 0;
}