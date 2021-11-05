/*编写程序实现二叉树的如下操作：
1) 建立二叉链表
2) 二叉树的先序、中序、后序遍历
3) 求二叉树的叶子结点个数
4) 将二叉树中所有结点的左、右子树相互交换

输入：扩展二叉树先序序列：ab#d##ce###。其中#代表空指针。

输出：
二叉树的凹入表示
二叉树的先序序列、中序序列、后序序列
二叉树叶子结点个数
左、右子树相互交换后的二叉树的凹入表示
左、右子树相互交换后的二叉树的先序序列、中序序列、后序序列。

说明：在输出凹入表示的二叉树时，先输出根结点，然后依次输出左右子树，上下层结点之间相隔 3 个空格。
*/

#include <bits/stdc++.h>
#define OK 1
typedef int Status;
typedef char ElemType;
int numleaf;

typedef struct BiTNode{
    ElemType data;
    struct BiTNode *lchild,*rchild;
}BiTNode,*BiTree;

Status CreateBiTree(BiTree &T){
    char c;
    scanf("%c",&c);
    if(c=='#')T=NULL;   //空子树
    else{
        if(!(T=(BiTNode*)malloc(sizeof(BiTNode))))exit(OVERFLOW);
        T->data=c;                //建立根结点
        CreateBiTree(T->lchild);  //递归构造左子树链表
        CreateBiTree(T->rchild);  //递归构造右子树链表
        if(T->lchild==NULL && T->rchild==NULL) numleaf++;  //叶子结点个数
    }
    return OK;
}

int countLeaf(BiTree T){   //也可以用函数计算叶子结点个数
    if(!T)return 0;
    if(T->lchild==NULL && T->rchild==NULL)return 1;
    else return countLeaf(T->lchild)+countLeaf(T->rchild);
}

void PreOrder(BiTree T){  //DLR 先序输出
    if(T){
        printf("%c",T->data);
        PreOrder(T->lchild);
        PreOrder(T->rchild);
    }
}

void InOrder(BiTree T){   //LDR 中序输出
    if(T){
        InOrder(T->lchild);
        printf("%c",T->data);
        InOrder(T->rchild);
    }
}

void PostOrder(BiTree T){   //LRD 后序输出
    if(T){
        PostOrder(T->lchild);
        PostOrder(T->rchild);
        printf("%c",T->data);
    }
}

void SwapLeftRight(BiTree T){   //互换左右子树的递归函数
    if(T){
        if(T->lchild || T->rchild){
            BiTree temp=T->lchild;
            T->lchild=T->rchild;
            T->rchild=temp;
            if(T->lchild)SwapLeftRight(T->lchild);
            if(T->rchild)SwapLeftRight(T->rchild);
        }
    }
}

void PrintLineSpace(char ch,int n){       //凹入法空格格式
    for(int k=0;k<4*n;k++)printf(" ");
    printf("%c\n",ch);
}

void PrintTreeList(BiTree T,int depth){   //以凹入法形式输出
    if(T){
        PrintLineSpace(T->data,depth);      //输出根结点
        PrintTreeList(T->lchild,depth+1);   //左子树
        PrintTreeList(T->rchild,depth+1);   //右子树
    }
}

BiTree tree=NULL;

int main(){
    printf("BiTree\n");
    CreateBiTree(tree);
    PrintTreeList(tree,0);      //凹入法输出

    printf("pre_sequence  : ");
    PreOrder(tree);
    printf("\n");
    printf("in_sequence   : ");
    InOrder(tree);
    printf("\n");
    printf("post_sequence : ");
    PostOrder(tree);
    printf("\n");

    printf("Number of leaf: %d\n",countLeaf(tree));
    printf("BiTree swapped\n");
    SwapLeftRight(tree);
    PrintTreeList(tree,0);

    printf("pre_sequence  : ");
    PreOrder(tree);
    printf("\n");
    printf("in_sequence   : ");
    InOrder(tree);
    printf("\n");
    printf("post_sequence : ");
    PostOrder(tree);
    printf("\n");

    return 0;
}