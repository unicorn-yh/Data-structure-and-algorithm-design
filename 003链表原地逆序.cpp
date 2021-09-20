/*请编写函数 void inverse( LinkList )，实现单链表的原地置逆。
即利用原来的结点将线性表：L =（a1, a2, …… , an）
变换为：L =（ an,  …… , a2, a1）*/

#include <iostream>  
using namespace std;  
  
typedef int ElemType;  
typedef struct node{   
    ElemType data;  
    struct node* next;  
}NODE;  
typedef NODE* LinkList;  
  
void output(LinkList);  
void change(int,int,NODE*);  
LinkList createList(ElemType);  
void inverse(LinkList);   
  
LinkList createList(ElemType finish){  //finish：数据结束标记   
    ElemType x;  
    NODE *newNode;   
    LinkList first=new NODE;   // 建立头结点  
    first->next=NULL;  
    first->data=finish;  
    cin >> x;                 // 约定以finish结束连续输入  
    while(x!=finish){  
        newNode=new NODE;      // 建立新结点  
        newNode->data=x;  
        newNode->next=first->next; // ①  
        first->next=newNode;       // ②  
        cin >> x;  
    }  
    return first;  
}  
  
void output(LinkList head){   
    cout << "List:";  
    while(head->next!=NULL){   
        cout << head->next->data << ",";  
        head=head->next;  
    }  
    cout << endl;  
}  

void inverse(LinkList L){
    LinkList tail=L->next;
    L->next=NULL;
    while(tail){
        LinkList temp=tail->next;
        tail->next=L->next;
        L->next=tail;
        tail=temp;
    }
} 

int main(int argc, char** argv){  
    LinkList head;
    head=createList(-1);  
    output(head);  
    inverse(head);  
    output(head);  
    return 0;  
}  

