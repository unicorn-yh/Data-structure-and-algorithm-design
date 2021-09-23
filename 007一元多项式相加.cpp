/*题目说明：
编写一元多项式加法运算程序。要求用线性链表存储一元多项式（参照课本）。该程序有以下几个功能：

1. 多项式求和
输入：输入三个多项式，建立三个多项式链表Pa、Pb、Pc（提示：调用CreatePolyn(polynomial &P,int m)。
输出：显示三个输入多项式Pa、Pb、Pc、和多项式Pa+Pb、多项式Pa+Pb+Pc
提示：调用AddPolyn(polynomial &Pa, polynomial Pb), 调用PrintPolyn(polynomial P))。
0. 退出

输入：
根据所选功能的不同，输入格式要求如下所示（第一个数据是功能选择编号，参见测试用例）：
1
多项式A包含的项数，以指数递增的顺序输入多项式A各项的系数（整数）、指数（整数）
多项式B包含的项数，以指数递增的顺序输入多项式B各项的系数（整数）、指数（整数）
多项式C包含的项数，以指数递增的顺序输入多项式C各项的系数（整数）、指数（整数）
0 －－－操作终止，退出。

输出：
对应一组输入，输出一次操作的结果（参见测试用例）。

1 多项式输出格式：以指数递增的顺序输出: <系数,指数>,<系数,指数>,<系数,指数>,参见测试用例。零多项式的输出格式为<0,0>
0 无输出*/

#include <bits/stdc++.h>
typedef struct node{
    float coef;
    int expn;
    struct node *next;
}Polyn;

void InitializeList(Polyn *&L){     //初始化多项式单链表
    L=(Polyn*)malloc(sizeof(Polyn));
    L->next=NULL;
}
int PolynLength(Polyn *&L){     //多项式单链表长度
    int k=0;
    Polyn *q=L->next;
    while(q){
        q=q->next;
        k++;
    }
    return k;
}
void SortPolyn(Polyn *L){     //将多项式单链表按expn域递增排序
    Polyn *q=L->next;
    Polyn *r,*temp;
    L->next=NULL;
    while(q){
        if(!L->next){        //处理第一个结点
            L->next=q;       //插入
            q=q->next;
            L->next->next=NULL;
        }
        else{
            temp=L;
            r=temp->next;
            while(r && q->expn>r->expn){
                temp=r;
                r=r->next;
            }
            r=q->next;   //在temp结点之后插入q
            q->next=temp->next;
            temp->next=q;
            q=r;
        }
    }
}
Polyn *AddPolyn(Polyn *a,Polyn *b){    //结合多项式链表 a和 b
    Polyn *c,*p,*tempc,*r;
    Polyn *p1=a->next;
    Polyn *p2=b->next;
    c=(Polyn*)malloc(sizeof(Polyn));  //新建头结点 c
    c->next=NULL;    
    tempc=c;
    while(p1 && p2){
        if(p1->expn<p2->expn){   //复制 p1结点到 *r, 并链到 c尾
            r=(Polyn*)malloc(sizeof(Polyn));
            r->coef=p1->coef;
            r->expn=p1->expn;
            r->next=NULL;
            tempc->next=r;
            tempc=r;
            p1=p1->next;
        }
        else if(p1->expn>p2->expn){
            r=(Polyn*)malloc(sizeof(Polyn));
            r->coef=p2->coef;
            r->expn=p2->expn;
            r->next=NULL;
            tempc->next=r;
            tempc=r;
            p2=p2->next;
        }
        else{
            if(p1->coef+p2->coef!=0){
                r=(Polyn*)malloc(sizeof(Polyn));
                r->coef=p1->coef+p2->coef;
                r->expn=p1->expn;
                r->next=NULL;
                tempc->next=r;
                tempc=r;
            }
            p1=p1->next;
            p2=p2->next;
        }
    }
    if(p1)p=p1;
    else p=p2;
    while(p){
        r=(Polyn*)malloc(sizeof(Polyn));
        r->coef=p->coef;
        r->expn=p->expn;
        r->next=NULL;
        tempc->next=r;
        tempc=r;
        p=p->next;
    }
    tempc->next=NULL;
    return c;
}
int InsertElem(Polyn *&L,float cf,int ex,int i){   //多项式链表中插入一个节点
    int k=1;
    Polyn *q=L;
    Polyn *r;
    r=(Polyn*)malloc(sizeof(Polyn));
    r->coef=cf;
    r->expn=ex;
    r->next=NULL;
    if(i<1||i>PolynLength(L)+1)return 0;
    while(k<i){       //查找单链表的第 i-1个结点
        q=q->next;
        k++;
    }
    r->next=q->next;   //插入结点
    q->next=r;
    return 1; 
}
int DeleteElem(Polyn *L,int i){   //多项式链表中删除一个节点
    int k=1;
    Polyn *q=L;
    Polyn *r;
    if(i<1||i>PolynLength(L))return 0;
    while(k<i){        //查找单链表的第 i-1个结点
        q=q->next;
        k++;
    }
    r=q->next;       //删除结点
    q->next=r->next;
    free(r);
    return 1;
}
void CreatePolyn(Polyn *&L,float cf[],int ex[],int n){
    int i;
    InitializeList(L);
    for(int i=0;i<n;i++) InsertElem(L,cf[i],ex[i],i+1);
}
void OutputPolyn(Polyn *L){    //输出
    Polyn *q=L->next;
    int flag=0;
    while(q){
        printf("<%g,%d>",q->coef,q->expn);
        if(q->next!=NULL)printf(",");
        q=q->next;
        flag=1;
    }
    if(!flag)printf("<0,0>");
    printf("\n");
}
int main(){
    Polyn *A,*B,*C;
    float cf[10010];
    int ex[10010];
    InitializeList(A);
    InitializeList(B);
    InitializeList(C);
    int input,num;
    scanf("%d",&input);
    if(!input) return 0;
     for(int k=0;k<3;k++){
        scanf("%d",&num);
        for(int i=0;i<num;i++){
            scanf("%f",&cf[i]);
            scanf("%d",&ex[i]);
        }
        if(k==0)CreatePolyn(A,cf,ex,num);
        if(k==1)CreatePolyn(B,cf,ex,num);
        if(k==2)CreatePolyn(C,cf,ex,num);
    }
    OutputPolyn(A);
    OutputPolyn(B);
    OutputPolyn(C);
    SortPolyn(A);
    SortPolyn(B);
    SortPolyn(C);
    OutputPolyn(AddPolyn(A,B));
    OutputPolyn(AddPolyn(AddPolyn(A,B),C));
    return 0; 
}