#include <bits/stdc++.h>
typedef char AtomType;
typedef int Status;
typedef int Boolean;
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define INFEASTIBLE -1
#define OVERFLOW -2

typedef enum{
    ATOM,LIST   //原子 ATOM==0，子表 LIST==1
}ElemTag;

typedef struct GLNode{  //广义表的头尾链表存储表示
    ElemTag tag;
    union{
        AtomType atom;    //原子节点的值域，AtomType 由用户定义，
        struct{  
            struct GLNode *hp;   //指向表头
            struct GLNode *tp;   //指向表尾
        }ptr;   //表节点的指针域
    }a;
}*GList,GLNode;

/*typedef struct GLNode{   //广义表的扩展线性链表存储表示
    ElemTag tag;         //公共部分，区分原子节点和表节点
    union{               //原子节点和表节点的联合部分
        AtomType atom;   //原子节点的值域
        struct GLNode *hp;  //表节点的表头指针
    };
    struct GLNode *tp;   //指向下一个元素节点，相当于线性链表的 next
}*GList1;   */    

typedef struct MPNode{    //m元多项式广义表类型
    ElemTag tag;     //区分原子节点和表节点
    int exp;         //指数域
    union{
        float coef;  //系数域
        struct MPNode *hp;   //表节点的表头指针
    };
    struct MPNode *tp;   //指向下一个元素节点，相当于线性链表的 next
}MPList;

typedef struct{
    char *ch;  //若是非空串,则按串长分配存储区,否则ch为NUL
    int length;  //串长度
}HString;

Status InitGList(GList *L){   //创建空的广义表
    *L=NULL;
    return OK;
}
void InitString(HString *T){  //产生空串 T
    (*T).length=0;
    (*T).ch=NULL;
}
Status StrAssign(HString *T, char *chars){ //生成一个其值等于串常量chars的串T 
	int i, j;
	if ((*T).ch) free((*T).ch);           //释放T原有空间 
	i = strlen(chars);                   //求chars的长度i 
	if (!i){                             //chars的长度为0 
		(*T).ch = NULL;
		(*T).length = 0;
	}
	else{                        //chars的长度不为0 
		(*T).ch = (char*)malloc(i * sizeof(char));  //分配串空间 
		if (!(*T).ch) exit(OVERFLOW);           //分配串空间失败 
		for (j = 0; j < i; j++) (*T).ch[j] = chars[j]; //拷贝串
		(*T).length = i;
	}
	return OK;
}
int StrLength(HString S){
    return S.length;
}
int StrCompare(HString S,HString T){  //S>T,返回值>0;S=T,返回值=0;S<T,返回值<0
    for(int i=0;i<S.length&&i;++i)
        if(S.ch[i]!=T.ch[i])
            return S.ch[i]-T.ch[i];
    return S.length-T.length;
}
Status SubString(HString *Sub, HString S, int pos, int len){ 
    //用Sub返回串S的第pos个字符起长度为len的子串。 
    //其中,1≤pos≤StrLength(S)且0≤len≤StrLength(S)-pos+1 
	if (pos<1||pos>S.length||len<0||len>S.length-pos+1)return ERROR;
	if ((*Sub).ch)free((*Sub).ch); /* 释放旧空间 */
	if (!len){  //空子串 
		(*Sub).ch = NULL;
		(*Sub).length = 0;
	}
	else{      //完整子串
		(*Sub).ch = (char*)malloc(len*sizeof(char));
		if (!(*Sub).ch)exit(OVERFLOW);
		for (int i=0;i<=len-1;i++)(*Sub).ch[i]= S.ch[pos-1+i];
		(*Sub).length=len;
	}
	return OK;
}
Status sever(HString *str,HString *hstr){  //分割str成：hstr为第一个','之前的子串,str为之后的子串
    int n,i=1,k=0;
    HString ch,c1,c2,c3;
    InitString(&ch);
    InitString(&c1);
    InitString(&c2);
    InitString(&c3);
    StrAssign(&c1,",");
    StrAssign(&c2,"(");
    StrAssign(&c3,")");
    n=StrLength(*str);
    do{
        SubString(&ch,*str,i,1);
        if(!StrCompare(ch,c2))++k;
        else if(!StrCompare(ch,c3))--k;
        ++i;
    }while(i<=n&&StrCompare(ch,c1)||k!=0);
    if(i<=n){
        StrCopy(&ch,*str);
        SubString(hstr,ch,1,i-2);
        SubString(str,ch,i,n-i+1);
    }
    else{
        StrCopy(hstr,*str);
        ClearString(str);
    }
    return OK;

}
Status CreateGList(GList *L,HString S){   //根据字符串S表示的广义表内容建立广义表数据结构
    HString emp,sub,hsub;
    GList p,q;
    InitString(&emp);
    InitString(&sub);
    InitString(&hsub);
    StrAssign(&emp,"()");
    if(!StrCompare(S,emp))*L=NULL;   //创建空表
    else{
        if(!(*L=(GList)malloc(sizeof(GLNode))))exit(OVERFLOW);  //建表结点
        if(StrLength(S)==1){   
            (*L)->tag=ATOM;
            (*L)->a.atom=S.ch[0];       //创建单原子广义表
        }
        else{
            (*L)->tag=LIST;
            p=*L;
            SubString(&sub,S,2,StrLength(S)-2);   //脱外层括号
            do{      //重复建n个子表
                sever(sub,hsub);    //从sub中分离出表头串hsub
                CreateGList(p->ptr.hp,hsub);
                q=p;
                if(!StrEmpty(sub)){   //表尾不空
                    if(!(p=(GList*)malloc(sizeof(GLNode))))exit(OVERFLOW);
                    p->tag=LIST;
                    q->a.ptr.tp=p;
                }
            }while(!StrEmpty(sub));
            q->a.ptr.tp=NULL;
        }
    }
    return OK;
}
Status CopyGlist(GList *T,GList L){  //头尾链表存储结构，复制广义表L，得到广义表T
    if(!L)*T=NULL;  //复制空表
    else{
        *T=(GList)malloc(sizeof(GLNode));   //建表结点
        if(!*T)exit(OVERFLOW);
        (*T)->tag=L->tag;
        if(L->tag==ATOM)(*T)->a.atom=L->a.atom;    //复制单原子
        else{
            CopyGlist(&((*T)->a.ptr.hp),L->a.ptr.hp);   //复制广义表 L->ptr.hp 的一个副本 T->ptr.tp;
            CopyGlist(&((*T)->a.ptr.tp),L->a.ptr.tp);   //复制广义表 L->ptr.tp的一个副本 T->ptr.tp;
        }
    }
    return OK;
}
int GListLength(GList L){
    int len=0;
    if(!L)return 0;
    if(L->tag==ATOM)return 1;
    while(L){
        L=L->a.ptr.tp;
        len++;
    }
    return len;
}
int GListDepth(GList L){
    int max,depth;
    GList p;
    if(!L)return 1;    //空表深度为1
    if(L->tag==ATOM)return 0;  //原子深度为0
    for(max=0,p=L;p;p=p->a.ptr.tp){
        depth=GListDepth(p->a.ptr.hp);  //求以 p->a.ptr.hp为头指针的子表深度
        if(depth>max)max=depth;
    }
    return max+1;    //非空表的深度是各元素的深度的最大值加1
}
Status GListEmpty(GList L){    //判断广义表是否为空
    if(!L)return TRUE;
    else return FALSE;
}
GList GetHead(GList L){  //取广义表L表头
    GList head,tail;
    if(!L) exit(0);
    p=L->a.ptr.tp;
    L->a.ptr.tp=NULL;
    CopyGlist(&head,L);
    L->a.ptr.tp=p;
    return head;
}

GList GetTail(GList L){   //取表尾运算
    GList tail;
    if(!L) exit(0);
    CopyGlist(&tail,L->a.ptr.tp);
    return tail;
}
Status InsertFirst_GL(GList *L, GList e){ 
    // 初始条件: 广义表存在 
    // 操作结果: 插入元素e作为广义表L的第一元素(表头,也可能是子表) */
	GList p = (GList)malloc(sizeof(GLNode));
	if (!p) exit(OVERFLOW);
	p->tag = LIST;
	p->a.ptr.hp = e;
	p->a.ptr.tp = *L;
	*L = p;
	return OK;
}
Status DeleteFirst_GL(GList *L, GList *e){ 
    // 初始条件: 广义表L存在 
    // 操作结果: 删除广义表L的第一元素,并用e返回其值 
	GList p;
	*e = (*L)->a.ptr.hp;
	p = *L;
	*L = (*L)->a.ptr.tp;
	free(p);
	return OK;
}
void Traverse_GL(GList L, void(*v)(AtomType)){
     // 利用递归算法遍历广义表L 
	if (L) //L不空 
		if (L->tag == ATOM) //L为单原子 
			v(L->a.atom);
		else{ //L为广义表 
			Traverse_GL(L->a.ptr.hp, v);
			Traverse_GL(L->a.ptr.tp, v);
		}
}
void DestroyGList(GList &L){  //销毁广义表L
    GList q1,q2;
    if(*L){
        if((*L).tag==ATOM){
            free(*L);         //删除原子结点
            (*L)=NULL;
        }
        else{
            q1=(*L).a.ptr.hp;
            q2=(*L).a.ptr.tp;
            free(*L);
            *L=NULL;
            DestroyGList(&q1);
            DestroyGList(&q2);
        }
    }
}

Status PrintGList(GLNode *T){  
    GLNode *p=T, *q; 
    if(p==NULL) printf(")");  
    else{   
        if(p->tag==ATOM){   
            if(count>0) printf(",");  
            printf("%c",p->ptr.data);  
            count++;  
        }  
        else{   
            q=p->ptr.hp;  
            if(q==NULL){   
                if(count>0)printf(",");  
                printf("(");  
            }  
            else if(q->tag==LIST){   
                if (count>0)printf(",");  
                printf("(");  
                count = 0;  
            }  
            PrintGList(q);  
            PrintGList(p->tp);  
        }  
    }  
    return OK;  
}  
  
void print(GLNode *L){  
    if (L==NULL)printf("()");  
    else{  
        if (L->tag==LIST)printf("(");  
        if (L->ptr.hp!=NULL)PrintGList(L);  
        else{  
            printf("()");  
            if (L->tp==NULL)printf(")");  
        }  
    }  
    printf("\n");  
}  