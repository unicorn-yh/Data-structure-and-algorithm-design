#include <bits/stdc++.h>
#define MAX_TREE_SIZE 100
#define OK 1
#define ERROR 0
typedef int ElemType;
typedef int TElemType;
typedef int Status;

//二叉链表
typedef struct BiTNode{               
    ElemType data;                    //数据域
    struct BiTNode *lchild,*rchild;   //左指针域 右指针域
    struct BiTNode *parent;           //双亲指针域
}BiTNode,*BiTree;

//静态二叉链表
typedef struct BPTNode{            //结点结构
    TElemType data;
    int lchild,rchild;
}BNode; 
typedef struct BTree{             //树结构         
    BNode nodes[MAX_TREE_SIZE];
    int num_node;                 //结点数目
    int root;                     //根结点位置
}BTree;

//双亲链表
typedef struct BPTNode{   //结点结构
    TElemType data;
    int parent;           //指向双亲的指针
    char LRTag;          //左右孩子的标志域
}BPTNode;
typedef struct BPTree{    //树结构
    BPTNode nodes[MAX_TREE_SIZE];
    int num_node;
    int root;
}BTree;

//先序遍历的递归算法  DLR
void PreOrderTraverse(BiTree T,Status(*Visit)(ElemType e)){
    if(T){                 //若二叉树不为空
        Visit(T->data);    //访问根结点
        PreOrderTraverse(T->lchild,Visit);     //先序遍历左子树
        PreOrderTraverse(T->rchild,Visit);     //先序遍历右子树
    }
}

void PreOrderTraverse(BiTree T,Status(*Visit)(ElemType e)){
    if(T){                 //若二叉树不为空
        if(Visit(T->data))  //访问根结点成功则继续
            if(PreOrderTraverse(T->lchild,Visit))     //左子树
                if(PreOrderTraverse(T->rchild,Visit)  //右子树
                    return OK;  
        return ERROR;
    }
    else return OK;
}

//中序遍历的递归算法  LDR
void InOrderTraverse(BiTree T,Status(*Visit)(ElemType e)){
    if(T){
        InOrderTraverse(T->lchild,Visit);
        Visit(T->data);
        InOrderTraverse(T->rchild,Visit);
    }
}

//中序遍历的非递归算法  用栈
Status InTrav(BiTree T,void(*Visit)(TElemType e)){
    InitStack(S);
    BiTree p=T;
    while(p||!StackEmpty(S)){    //树非空 或 栈非空
        if(p){
            Push(S,p);     //p有左子树则一直入栈，直到最左下结点
            p=p->lchild;
        }
        else{
            Pop(S,p);         //退栈 访问
            Visit(p->data);
            p=p->rchild;     //p指向右子树
        }
    }
    DestroyStack(S);
    return OK;
}

//后序遍历的递归算法  LRD
void PostOrderTraverse(BiTree T,Status(*Visit)(ElemType e)){
    if(T){
        PostOrderTraverse(T->lchild,Visit);
        PostOrderTraverse(T->rchild,Visit);
        Visit(T->data);
    }
}

//最简单的 Visit 函数
Status PrintElement(TElemType e){
    output(e);
    return OK;
}

int numleaf;
//求二叉树的叶子节点个数的算法
void leaf(BiTree T){
    if(T){
        if(T->lchild==NULL && T->rchild==NULL) numleaf+=1;
        else{
            leaf(T->lchild);
            leaf(T->rchild);
        }
    }
}
int countLeaf(BiTree T){
    if(!T)return 0;
    if(T->lchild==NULL && T->rchild==NULL)return 1;
    else return countLeaf(T->lchild)+countLeaf(T->rchild);
}

//先序建立二叉树
Status CreateBiTree(BiTree &T){
    char c;
    scanf("%c",&c);
    if(c=='*')T=NULL;   //空子树
    else{
        if(!(T=(BiTNode*)malloc(sizeof(BiTNode))))exit(OVERFLOW);
        T->data=c;                //建立根结点
        CreateBiTree(T->lchild);  //递归构造左子树链表
        CreateBiTree(T->rchild);  //递归构造右子树链表
        if(T.lchild==NULL && T.rchild==NULL) numleaf++;
    }
    return OK;
}

//后序遍历 复制二叉链表
void CopyBiTree(BiTree T,BiTree &newT){
    BiTree *plchild,*prchild;
    if(!T)newT=NULL;   //若T为空
    else{
        CopyBiTree(T->lchild,plchild);   //复制左子树
        CopyBiTree(T->rchild,prchild);   //复制右子树
        newT=(BiTree)malloc(sizeof(BiTNode));
        newT->data=T->data;
        newT->lchild=plchild;   //链接新结点的左子树
        newT->rchild=prchild;   //链接新结点的右子树
    }
}

//线索链表
typedef enum{link,thread}PointerTag;   //link=0,thread=1
typedef struct BiThrNode{
    TElemType data;
    struct BiThrNode *lchild,*rchild;
    PointerTag Ltag,Rtag;      //左右标志域
}BiThrNode,*BiThrTree;

//中序线索二叉树
Status InTra_ThrT(BiThrTree ThrT,void(*Visit)(TElemType e)){
    BiThrTree p=ThrT->lchild; //p指针指向根结点
    while(p!=ThrT){        //p 不等于 D（0层的结点）
        while(p->Ltag==link)p=p->lchild;   //延至最左下结点
        Visit(p->data);     //p->Ltag == thread
        while(p->Rtag==thread && p->rchild!=ThrT){
            p=p->rchild;    //右孩子域是线索
            Visit(p->data);
        }
        p=p->rchild;      //右孩子域不是线索
    }
    return OK;
}

//中序 建立线索二叉树   LDR
BiThrTree pre;
Status InOrderThreading(BiThrTree &Thrt,BiThrTree T){
    if(!(Thrt=(BiThrTree)malloc(sizeof(BiThrNode))))exit(OVERFLOW);
    Thrt->Ltag=link;   //0
    Thrt->Rtag=thread; //1,建头结点
    Thrt->rchild=Thrt; //右指针指向头结点
    if(!T)Thrt->lchild=Thrt;  //若二叉树为空，则左指针回指
    else{
        Thrt->lchild=T;
        pre=Thrt;
        InThreading(T);
        pre->rchild=Thrt;
        pre->Rtag=thread;
        Thrt->rchild=pre;
    }
    return OK;
}

//中序线索化二叉树
void InThreading(BiThrTree p){
    if(p){
        InThreading(p->lchild);  //左子树线索化
        if(p->lchild==NULL){
            p->Ltag=thread;
            p->lchild=pre;    //为当前结点加前趋线索
        }
        if(p->rchild==NULL){   //为前趋结点加后继线索
            p->Rtag=thread;
            pre->Rtag=p;
        }
        pre=p;                //pre指向p
        InThreading(p->rchild);
    }
}