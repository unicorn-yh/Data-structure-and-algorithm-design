//静态链表
#include <bits/stdc++.h>
#define MAXSIZE 1000
typedef int ElemType;
typedef struct{
    ElemType data;
    int cur;         //结点在数组中的位置
}component,SLinkList[MAXSIZE];

int LocateElem_SL(SLinkList S,ElemType e){
    int i=S[0].cur;   //第一个结点，S[i].data 存储第一个数据元素，S[i].cur 指向第二个结点
    while(i && S[i].data!=e)i=S[i].cur; //顺链查找
    return i;
}
void InitSpace_SL(SLinkList &S){  //将一维数组 S 中各分量链成一个备用链表
    for(int i=0;i<MAXSIZE-1;i++){
        S[i].cur=i+1;
    }
    S[MAXSIZE-1].cur=0; 
}
int Malloc_SL(SLinkList &S){  //备用空间链表非空则返回分配的结点下标
    int i=S[0].cur;           
    if(S[0].cur)S[0].cur=S[i].cur;
    return i;
}
void Free_SL(SLinkList &S,int k){   //将下标为 k 的空闲结点回收到备用链表  
    S[k].cur=S[0].cur;
    S[0].cur=k;
}
void difference(SLinkList &S,int &T){
    InitSpace_SL(S);    //初始化备用空间
    T=Malloc_SL(S);    //生成 T 的头结点
    int r=T;
    int m,n,b;
    scanf("%d %d",&m,&n);         //输入 A 和 B 的元素个数
    for(int j=1;j<=m;j++){        //建立集合A的链表
        int i=Malloc_SL(S);       //分配结点
        scanf("%d",&S[i].data);   //输入 A 的元素值
        S[r].cur=i;               //插入到表尾
        r=i;
    }
    S[r].cur=0;               //尾结点的指针为空
    for(int j=1;j<=n;j++){
        scanf("%d",&b);      //依次输入 B 的元素，若不在表中则插入，否则删除
        int p=T;
        int k=S[T].cur;     //k 指向集合 A 的第一个结点
        while(k!=S[r].cur && S[k].data!=b){   //当前表中查找
            p=k;
            k=S[k].cur;
        }
        if(k==S[r].cur){   //表中不存在该元素，插入在 r 所指的结点后，r位置不变
            T=Malloc_SL(S);
            S[T].data=b;
            S[T].cur=S[r].cur;
            S[r].cur=T;
        }
        else{             //该元素已在表中，删除该元素
            S[p].cur=S[k].cur;
            Free_SL(S,k);
            if(r==k)r=p;  //若删除的是 r 结点则需修改尾指针
        }
    }
}
