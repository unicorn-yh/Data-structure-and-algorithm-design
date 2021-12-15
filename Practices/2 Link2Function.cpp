
#include <bits/stdc++.h>
typedef int ElemType;
typedef int Position;
typedef int Status;
typedef struct LNode{
    ElemType data;
    struct LNode *next;
}*Link,*Position;
typedef struct{
    Link head,tail;
    int len;
}LinkList;

Position GetHead(LinkList L){

}
Position GetLast(LinkList L){

}
Position PriorPos(LinkList L,Link p){

}
Position NextPos(LinkList L,Link p){

}
Status LocatePos(LinkList L,int i,Link &p){

}
Position LocateElem(LinkList L,ElemType e,Status(*compare)(ElemType,ElemType))

