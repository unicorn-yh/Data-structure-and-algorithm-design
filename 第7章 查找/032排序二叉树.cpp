/*排序二叉树是指左子树的所有节点的值均小于它根节点的值，右子树的所有节点的值均大于它根节点的值。
输入：输入有一行，表示若干个要排序的数，输入0时停止
输出：
二叉树的凹入表示
和二叉树的中序遍历序列

sample：
input:
56 78 34 89 12 35 67 77 22 57 0

output:
        12
            22
    34
        35
56
            57
        67
            77
    78
        89

12 22 34 35 56 57 67 77 78 89*/

#include <bits/stdc++.h>
#define EQ(a,b) (a==b)
#define LT(a,b) (a<b)
typedef struct BiTNode {
    int data;
    struct BiTNode *lchild, *rchild;
} BiTNode,*BiTree; 

//二叉排序树的查找（算法9.5a）——递归算法
BiTree SearchBST(BiTree T,int key){ 
    //将二叉链表作为二叉排序树的存储结构
    if (LT(key,T->data)){
        if(T->lchild==NULL)return T;
        else return SearchBST(T->lchild,key);
    }
    else{
        if(T->rchild==NULL)return T;
        else return SearchBST(T->rchild,key);
    }
}

void printTree(BiTree T,int step){  //step从0开始 T从根开始
    if(T->lchild!=NULL)printTree(T->lchild,step+1);  //左
    for(int k=0;k<step;k++)printf("    ");
    printf("%d\n",T->data);                          //根
    if(T->rchild!=NULL)printTree(T->rchild,step+1);  //右
}

void printMidSequence(BiTree T){  //中序遍历 T为根结点
    if(T->lchild!=NULL)printMidSequence(T->lchild);
    printf(" %d",T->data);
    if(T->rchild!=NULL)printMidSequence(T->rchild);
}

int main(){
    int key;
    scanf("%d",&key);
    BiTree root=(BiTree)malloc(sizeof(BiTNode));
    root->data=key;
    root->lchild=root->rchild=NULL;
    while(scanf("%d",&key)&&key!=0){
        BiTree t=SearchBST(root,key); //查找key，返回key的指针位置
        if(LT(key,t->data)){
            t->lchild=(BiTree)malloc(sizeof(BiTNode));
            t->lchild->data=key;
            t->lchild->lchild=t->lchild->rchild=NULL;
        }
        else{
            t->rchild=(BiTree)malloc(sizeof(BiTNode));
            t->rchild->data=key;
            t->rchild->lchild=t->rchild->rchild=NULL;
        }
    }
    printTree(root,0);
    printf("\n");
    printMidSequence(root);
    printf("\n");
    return 0;
}
