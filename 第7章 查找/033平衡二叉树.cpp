/*程序输入一个字符串（只包含小写字母），请按照字符的输入顺序建立平衡二叉排序树，并分别输出二叉树的先序序列、中序序列和后序序列，最后输出该二叉树向左旋转 90 度后的结构。
例如：向左旋转 90 度后，以每层向里缩进 4 个空格的方式输出，输出结果为：

        i
    g
        f
a
        d
    c
        b

输入：agxnzyimk

输出：
Preorder: xigamknzy
Inorder: agikmnxyz
Postorder: agknmiyzx
Tree:
    z
        y
x
            n
        m
            k
    i
        g
            a*/

#include <bits/stdc++.h>
typedef struct BiTNode{
    char data;
    struct BiTNode *lchild,*rchild;
}BiTNode,*BiTree;

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

int height(BiTree T){       //返回左右子树中 高度较大的高度
    int leftheight,rightheight;
    if(T==NULL)return 0;
    else{
        leftheight=height(T->lchild);
        rightheight=height(T->rchild);
        return (leftheight>rightheight?leftheight+1:rightheight+1);
    }
}

BiTree singleRotationLL(BiTree T){  //LL 向右转
    BiTree A=T->lchild;  //根=左
    T->lchild=A->rchild;
    A->rchild=T;
    return A;
}

BiTree singleRotationRR(BiTree T){  //RR 向左转
    BiTree A=T->rchild;
    T->rchild=A->lchild;
    A->lchild=T;
    return A;
}

BiTree doubleRotationLR(BiTree T3){  //LR 孩子左转、右转
    BiTree T2,T1;
    T1=T3->lchild;
    T2=T1->rchild;
    T1->rchild=T2->lchild;
    T3->lchild=T2->rchild;
    T2->lchild=T1;
    T2->rchild=T3;
    return T2;
}

BiTree doubleRotationRL(BiTree T1){   //RL 孩子右转、左转
    BiTree T2,T3;
    T3=T1->rchild;
    T2=T3->lchild;
    T1->rchild=T2->lchild;
    T3->lchild=T2->rchild;
    T2->lchild=T1;
    T2->rchild=T3;
    return T2;
}

BiTree insert(char c,BiTree T){
    if(T==NULL){
        T=(BiTree)malloc(sizeof(BiTNode));
        T->data=c;
        T->lchild=T->rchild=NULL;
    }
    else{
        if(c<T->data){
            T->lchild=insert(c,T->lchild);
            if(height(T->lchild)-height(T->rchild)==2){
                if(c<T->lchild->data)T=singleRotationLL(T);
                else T=singleRotationLR(T);
            }
        }
        else if(c>T->data){
            T->rchild=insert(c,T->rchild);
            if(height(T->rchild)-hieght(T->lchild)==2){
                if(c>T->rchild->data)T=singleRotationRR(T);
                else T=doubleRotationRL(T);
            }
        }
    }
    return T;
}

void turnTree90DegreeLeft(BiTree T,int depth){    //右根左
    if(T->rchild)turnTree90DegreeLeft(T->rchild,depth+1);  
    for(int i=1;i<depth;i++)printf("    ");
    printf("%c\n",T->data);
    if(T->lchild)turnTree90DegreeLeft(T->lchild,depth+1);
}

BiTree root=NULL;

int main(){
    char ch;
    while(scanf("%c",&ch)&&ch!='\n')root=insert(ch,root);  //按平衡原则插入
    printf("Preorder: "); PreOrder(root); printf("\n");
    printf("Inorder: "); InOrder(root); printf("\n");
    printf("Postorder: "); PostOrder(root); printf("\n");
    printf("Tree: \n"); turnTree90DegreeLeft(root,1);
    return 0;
}





