#include <bits/stdc++.h>
int count;  
typedef enum{ATOM,LIST}ListTag;  
typedef struct node{  
    ListTag tag;    //判断是子表还是原子
    union{  
        char data;  
        struct node *hp;  
    } ptr;  
    struct node *tp;  
}GLNode;  
GLNode* reverse(GLNode*);  

void Substring(char *sub,char *s, int pos,int len){  
    //sub为 pos位置开始，长度为len的字符串
    s=s+pos;  
    while(len>0){   
        *sub=*s;  
        sub++; 
        s++;
        len--;
    }
    *sub='\0';
}  
  
void sever(char *str,char *headstr){   //分割str成：hstr为第一个','之前的子串,str为之后的子串
    int n, i, k;  
    char ch[50];  
    n=strlen(str);  
    i=k=0;  
    do{   
        Substring(ch,str,i++,1);  
        if(*ch=='(') k++;  
        else if(*ch==')') k--;  
    } while (i<n&&(*ch!=','||k!=0));  
    if(i<n){   
        Substring(headstr,str,0,i-1);  
        Substring(str,str,i,n-i);  
    }  
    else{   
        strcpy(headstr,str);  
        str[0]='\0';  
    }  
}
  
int PrintGList(GLNode *T){  
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
    return 1;  
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
  
int CreateGList(GLNode* *L,char *s){  
    GLNode *p, *q;  
    char sub[100],hsub[100];
    p=*L;  
    if (strcmp(s,"()")==0) *L = NULL;    // 创建空表  
    else{  
        *L=(GLNode*)malloc(sizeof(GLNode));  
        if(strlen(s)==1){   
            (*L)->tag=ATOM;  
            (*L)->ptr.data=s[0];  
        }  
        else{   
            (*L)->tag=LIST;  
            p=*L;  
            Substring(sub,s,1,strlen(s)-2);  
            do{   
                sever(sub,hsub);  
                CreateGList(&p->ptr.hp,hsub);  
                q=p;  
                if(strlen(sub)>0){   
                    p=(GLNode*)malloc(sizeof(GLNode));  
                    p->tag=LIST;  
                    q->tp=p;  
                }  
            }while(strlen(sub)>0);  
            q->tp=NULL;  
        }     
    }
    return 1;  
}  
 
GLNode *reverse(GLNode *p){
    GLNode *F=p,*q;
    if(p!=NULL && p->tag==LIST){   //是子表的话
        p->tp=reverse(p->tp);      //递归
        while(p->tp!=NULL)p=p->tp;
        p->tp=(GLNode*)malloc(sizeof(GLNode));
        q=p->tp;
        q->tp=NULL;
        q->tag=F->tag;
        q->ptr.hp=reverse(F->ptr.hp);
        p->tp=q;
        F=F->tp;
    }
    else return F;    //ATOM 原子
    return F;
}
  
int main(){  
    char list[100];  
    GLNode *L,*G;  
    count=0;  
    scanf("%s",list);  
    CreateGList(&L,list);  
    // print(L);  
    G=reverse(L);  
    count=0;  
    print(G);  
    return 0;  
}  