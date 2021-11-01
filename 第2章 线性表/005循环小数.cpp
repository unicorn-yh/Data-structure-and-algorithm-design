/*对于任意的真分数 N/M （ 0 < N < M ），均可以求出对应的小数。
如果采用链表表示各个小数，对于循环节采用循环链表表示，则所有分数均可以表示为如下链表形式。*/

#include <bits/stdc++.h>

typedef struct node{   
    int data;  
    struct node* next;  
} NODE;  
  
void output(NODE*,int);  
void change(int,int,NODE*);  
  
void output(NODE* head,int kk){   
    int k=0;
    printf("0.");  
    while (head->next && k<kk){   
        printf("%d",head->next->data);  
        head=head->next;  
        k++;  
    }  
    printf("\n");  
}  

void change(int n,int m,NODE *head){
    int divide[10010],modnum[10010];
    memset(divide,0,sizeof(divide));
    memset(modnum,0,sizeof(modnum));
    int a=0,b=0,flag=0,i,j;
    n*=10;
    for(i=0;;i++){
        divide[i]=n/m;
        modnum[i]=n%m;
        for(j=0;j<i;j++){
            if(divide[i]==divide[j] && modnum[i]==modnum[j]){
                a=j;
                b=i;
                flag=1;
                break;
            }
        }
        n=modnum[i]*10;
        if(!n){
            a=i+1;
            break;
        }
        if(flag) break;
    }
    NODE *h=head;
    for(i=0;i<a;i++){
        NODE *p=(NODE*)malloc(sizeof(NODE));
        p->data=divide[i];
        p->next=NULL;
        h->next=p;
        h=p;
    }
    if(flag){
        NODE *hsave=h;
        for(i=a;i<b;i++){
            NODE *p=(NODE*)malloc(sizeof(NODE));
            p->data=divide[i];
            p->next=NULL;
            h->next=p;
            h=p;
        }
        h->next=hsave->next;
    }
}

int main(){   
    int n,m,k;  
    NODE* head;
    scanf("%d%d%d",&n,&m,&k);  
    head = (NODE*)malloc(sizeof(NODE));  
    head->next=NULL;  
    head->data=-1;  
    change(n,m,head);  
    output(head,k);  
    return 0;  
}  