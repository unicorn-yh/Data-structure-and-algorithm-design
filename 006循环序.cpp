/*对于任意的真分数 N/M （ 0 < N < M ），均可以求出对应的小数。
如果采用链表存储各位小数，对于循环节采用循环链表表示，则所有分数均可以表示为如下链表形式。
输入： N M
输出：整个循环节
要求：编写一个尽可能高效的查找循环节起始点的函数： NODE * find( NODE * head, int * n ) 。
函数的返回值为循环节的起点（即图中的指针p），n为循环节的长度。
说明：提交程序时请同时提交将分数转换为小数的函数 change( int n, int m, NODE * head ) （前面题目中已经编写）。*/

#include <stdio.h>  
#include <stdlib.h>  
typedef struct node{   
    int data;  
    struct node *next;  
}NODE;  
  
NODE *find(NODE*,int*);  
void outputring(NODE*);  
void change(int,int,NODE*);  

void outputring(NODE *pring){   
    NODE *p;  
    p = pring;  
    if (p==NULL)printf("NULL");  
    else  
        do {   
            printf("%d",p->data);  
            p = p->next;  
        } while (p!=pring);  
    printf("\n");  
    return;  
}  
  
int main(){   
    int n, m;  
    NODE *head, *pring;
    scanf("%d%d",&n,&m);  
    head=(NODE*)malloc(sizeof(NODE));  
    head->next=NULL;  
    head->data=-1;
    change(n,m,head);  
    pring=find(head,&n);  
    printf("ring=%d\n",n);  
    outputring(pring);  
    return 0;  
}  

#include <bits/stdc++.h>
int a=0;
int b=0;
void change(int n,int m,NODE *head){   //将分数换为小数
    int divide[10010],modnum[10010];
    memset(divide,0,sizeof(divide));
    memset(modnum,0,sizeof(modnum));
    int flag=0,i,j;
    n*=10;
    for(i=0;;i++){
        divide[i]=n/m;
        modnum[i]=n%m;
        for(j=0;j<i;j++){
            if(divide[i]==divide[j] && modnum[i]==modnum[j]){
                a=j;
                b=i;
                flag=1;   //表示存在循环
                break;
            }
        }
        n=modnum[i]*10;
        if(!n){    //如果n被除尽，变为0，则没有循环
            a=i+1;
            break;
        }
        if(flag) break;
    }
    /*根据 p1 的位置，如果没有循环，则建立完整链表；
    	如果有循环，则建立的是前缀。 */
    NODE *h=head;
    for(i=0;i<a;i++){
        NODE *p=(NODE*)malloc(sizeof(NODE)); //尾插法建立链表
        p->data=divide[i];
        p->next=NULL;
        h->next=p;
        h=p;
    }
    if(flag){        //补上循环
        NODE *hsave=h;
        for(i=a;i<b;i++){
            NODE *p=(NODE*)malloc(sizeof(NODE));
            p->data=divide[i];
            p->next=NULL;
            h->next=p;
            h=p;
        }
        h->next=hsave->next;
    }
}

NODE * find(NODE *head, int *n){    //查询循环节起始点
    if(b>a){                              //存在循环
        NODE *q=head->next;               //初始化
        *n=b-a;                           //计算长度
        for(int i=0;i<a;i++)q=q->next;    //越过前缀
        return q;
    }
    else{                          //不存在循环
        *n=0;
        return NULL;
    }
}
