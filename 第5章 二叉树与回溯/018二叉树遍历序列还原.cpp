/*题目信息
给出二叉树的中序遍历序列和后序遍历序列，编程还原该二叉树。

输入
第1行:二叉树的中序遍历序列
第2行:二叉树的后序遍历序列

输出
二叉树的按层遍历序列
*/

#include <bits/stdc++.h>
using namespace std;
typedef char ElemType;

struct BiTNode{
    ElemType data;
    struct BiTNode *lchild,*rchild;
};

void PrintNode(BiTNode *T){     //根据层次输出
    queue <BiTNode*> q;
    if(!T)return;
    else{
        q.push(T);
        while(!q.empty()){
            BiTNode *temp=q.front();
            printf("%c",temp->data);
            q.pop();
            if(temp->lchild->data!='#' && temp->lchild->data!='\0')q.push(temp->lchild);
            if(temp->rchild->data!='#' && temp->rchild->data!='\0')q.push(temp->rchild);
        }
    }
}

BiTNode *FindPreStr(string InStr,string PostStr,int length){
    if(length==0)return NULL;
    BiTNode *T=new BiTNode;
    T->data=PostStr[length-1];  //根据后序序列的最后一个元素建立根结点
    int rootIndex;
    for(rootIndex=0;rootIndex<length;++rootIndex)
        if(InStr[rootIndex]==PostStr[length-1])break; 
         //在中序序列中找到该元素，确定根结点的左右子树的中序序列

    //由左子树的后序序列和中序序列建立左子树
    T->lchild=FindPreStr(InStr,PostStr,rootIndex); 
    if(T->lchild==NULL){
        T->lchild=new BiTNode;
        T->lchild->data='#';
    }

    //由右子树的后序序列和中序序列建立右子树
    string PostIn(InStr,rootIndex+1);
    string PostPost(PostStr,rootIndex);
    T->rchild=FindPreStr(PostIn,PostPost,length-rootIndex-1);
    if(T->rchild==NULL){
        T->rchild=new BiTNode;
        T->rchild->data='#';
    }
    return T;
}

int main(){
    string InString,PostString;
    cin >> InString >> PostString;
    PrintNode(FindPreStr(InString,PostString,PostString.length()));
    printf("\n");
    return 0;
}