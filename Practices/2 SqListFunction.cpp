//顺序线性表
#include <bits/stdc++.h>
#define LIST_INIT_SIZE 100   //线性表存储空间的初始分配量
#define LISTINCREMENT 10   //线性表存储空间分配增量
#define OK 1
#define ERROR 0
typedef int ElemType;
typedef int Status;
typedef struct{
    ElemType *elem; //存储空间地址
    int length;     //长度
    int listsize;   //存储容量
}SqList;
Status InitList_Sq(SqList &L){   //构造一个空的线性链表
   L.elem=(ElemType*)malloc(sizeof(ElemType));
   if(!L.elem)exit(OVERFLOW);
   L.length=0;
   L.listsize=LIST_INIT_SIZE;
   return OK;
}
Status DestroyList_Sq(SqList &L){

}
Status ClearList_Sq(SqList &L){

}
int ListLength_Sq(SqList L){
    return L.length;
}
Status GetElem_Sq(SqList L,int i,ElemType &e){
    if(i<1||i>L.length)return ERROR;
    e=L.elem[i-1];
    return OK;
}
Status PriorElem_Sq(SqList L,ElemType current_e,ElemType &previous_e){

}
Status NextElem_Sq(SqList L,ElemType current_e,ElemType &next_e){

}
Status ListTraverse_Sq(SqList L,Status(*visit)(ElemType)){
    ElemType e;
    for(int i=1;i<=L.length;i++){
        GetElem_Sq(L,i,e);
        (*visit)(e);
    }
}
Status ListInsert_Sq(SqList &L,int i,ElemType e){
    if(i<1||i>L.length+1)return ERROR;
    if(L.length>=L.listsize){
        ElemType* newbase=(ElemType*)realloc(L.elem,(L.listsize+LISTINCREMENT)*sizeof(ElemType));
        if(!newbase)exit(OVERFLOW);
        L.elem=newbase;
        L.listsize+=LISTINCREMENT;
    }
    ElemType *q=&(L.elem[i-1]);
    for(ElemType *p=&(L.elem[L.length-1]);p>=q;--p)*(p+1)=*p;
    *q=e;
    ++L.length;
    return OK;
}

Status DeleteElem_Sq(SqList &L,int i,ElemType &e){
    if(i<1||i>L.length)return ERROR;
    ElemType *p=&(L.elem[i-1]);
    e=*p;
    for(;p<=L.elem+L.length-1;++p) *p=*(p+1);
    --L.length;
    return OK;
}
int LocateElem_Sq(SqList &L,ElemType e,Status(*compare)(ElemType,ElemType)){  
   int i=1;
   ElemType *p=L.elem;
   while(i<=L.length && !(compare(e,*p++)))++i;
   if(i<=L.length)return i;
   else return 0;
}

void MergeList_Sq(SqList La,SqList Lb,SqList &Lc){
    InitList_Sq(Lc);
    ElemType a,b;
    int i=1,j=1,k=0;
    int alen=ListLength_Sq(La);
    int blen=ListLength_Sq(Lb);
    while(i<=alen && j<=blen){
        GetElem_Sq(La,i,a);
        GetElem_Sq(Lb,j,b);
        if(a<=b){
            ListInsert_Sq(Lc,++k,a);
            i++;
        }
        else{
            ListInsert_Sq(Lc,++k,b);
            j++;
        }
    }
    while(i<=alen){
        GetElem_Sq(La,i++,a);
        ListInsert_Sq(Lc,++k,a);
    }
    while(j<=blen){
        GetElem_Sq(Lb,j++,b);
        ListInsert_Sq(Lc,++k,b);
    }
}

void MergeList_Sq2(SqList La,SqList Lb,SqList &Lc){
    ElemType* pa=La.elem;    //指针头
    ElemType* pb=Lb.elem;
    Lc.length=La.length+Lb.length;
    Lc.listsize=Lc.length;
    Lc.elem==(ElemType*)malloc(Lc.listsize*sizeof(ElemType));
    ElemType* pc=Lc.elem;
    if(!Lc.elem)exit(OVERFLOW);
    ElemType* pa_tail=La.elem+La.length-1;
    ElemType* pb_tail=Lb.elem+Lb.length-1;
    while(pa<=pa_tail && pb<=pb_tail){
        if(*pa<=*pb) *pc++=*pa++;
        else *pc++=*pb++;
    }
    while(pa<=pa_tail)*pc++=*pa++;
    while(pb<=pb_tail)*pc++=*pb++;
}
