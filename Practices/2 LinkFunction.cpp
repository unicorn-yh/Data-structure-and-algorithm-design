//单链表
#include <bits/stdc++.h>
#define ERROR 0
#define OK 1
typedef int ElemType;
typedef int Status;
typedef struct LNode{
    ElemType *data;
    struct LNode *next;
}LNode,*LinkList;
Status InitList(LinkList &L){

}
Status DestroyLIst(LinkList &L){

}
void ClearList(LinkList L){
    LinkList p=L->next;
    while(p){
        LinkList q=p->next;
        free(p);
        p=q;
    }
    L->next=NULL;
}
bool ListEmpty(LinkList L){
    int flag;
    LinkList p=L->next;
    while(p)flag ++;
    if(!flag)return true;
    else return false;
}
int ListLength(LinkList L){
    int i=0;
    LinkList p=L->next;
    while(p){
        ++i;
        p=p->next;
    }
    return i;
}
Status GetElem_L(LinkList L,int i,ElemType* &e){
    int j;
    LinkList p=L->next;
    while(p && j<i){
        p=p->next;
        ++j;
    }
    if(j>i && !p)return ERROR;
    e=p->data;
    return OK;
}
Status ListInsert_L(LinkList &L,int i,ElemType e){
    int j=0;
    LinkList p=L;
    while(p && j<i-1){
        p=p->next;
        ++j;
    }
    if(!p || j>i-1)return ERROR;      //i小于1 或者 i大于表长+1
    LinkList s=(LinkList)malloc(sizeof(LNode));
    s->data=&e;
    s->next=p->next;
    p->next=s;
    return OK;
}
Status ListDelete_L(LinkList &L,int i,ElemType* &e){
    int j=0;
    LinkList p=L;
    while(p->next && j<i-1){
        p=p->next;
        ++j;
    }
    if(!(p->next) || j>i-1)return ERROR;
    LinkList q=p->next;
    p->next=q->next;
    e=q->data;
    free(q);
    return OK;
}
void CreateList_L(LinkList &L,int n){
    L=(LinkList)malloc(sizeof(LNode));
    L->next=NULL;
    for(int i=0;i<n;i++){
        LinkList p=(LinkList)malloc(sizeof(LNode));
        scanf("%d",&p->data);
        p->next=L->next;
        L->next=p;
    }
}
void MergeList_L(LinkList &La,LinkList &Lb,LinkList &Lc){
    LinkList pa=La->next;
    LinkList pb=Lb->next;
    LinkList pc=La;
    Lc=pc;
    while(pa&&pb){
        if(pa->data<=pb->data){
            pc->next=pa;
            pc=pa;
            pa=pa->next;
        }
        else{
            pc->next=pb;
            pc=pb;
            pb=pb->next;
        }
    }
    if(pa)pc->next=pa;
    else pc->next=pb;
    free(Lb);
}


