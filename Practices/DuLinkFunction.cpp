//双向链表
#include <bits/stdc++.h>
typedef int ElemType;
typedef int Status;
#define OK 1
#define ERROR 0
typedef struct DuLNode{
    ElemType data;
    struct DuLNode *prior;
    struct DuLNode *next;
}DuLNode,*DuLinkList;
Status GetElemP_DuL(DuLinkList &L,int i){

}
Status ListInsert_DuL(DuLinkList &L,int i,ElemType e){
    DuLinkList s,p;
    if(!(p=GetElemP_DuL(L,i))) return ERROR;   //在 L 中确定插入位置指针 p
    if(!(s=(DuLinkList)malloc(sizeof(DuLNode))))return ERROR;  
    s->data=e;
    s->prior=s->prior;
    s->prior->next=s;
    s->next=p;
    p->prior=s;
    return OK;
}
Status ListDelete_DuL(DuLinkList &L,int i,ElemType &e){  //删除第 i 个元素
    DuLinkList p;
    if(!(p=GetElemP_DuL(L,i)))return ERROR;  //确定第 i个元素的指针 p
    e=p->data;
    p->prior->next=p->next;
    p->next->prior=p->prior;
    free(p);
    return OK;
}
