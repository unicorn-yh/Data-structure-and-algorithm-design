#include <bits/stdc++.h>
#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10
#define OK 1
#define ERROR 0
typedef int SElemType;
typedef int Status;
typedef struct{
    SElemType *base;
    SElemType *top;
    int stacksize;
}SqStack;
Status InitStack(SqStack &S){
    S.base=(SElemType*)malloc(STACK_INIT_SIZE*sizeof(SElemType));
    if(!S.base)exit(OVERFLOW);
    S.top=S.base;
    S.stacksize=STACK_INIT_SIZE;
    return OK;
}
Status DestroyStack(SqStack &S){   //销毁

}
Status ClearStack(SqStack S){    //清空

}
Status StackEmpty(SqStack &S){
    if(S.base==S.top) return OK;
    else return ERROR;
}
int StackLength(){

}
Status GetTop(SqStack S,SElemType &e){   //返回栈顶元素
    if(S.base==S.top)return ERROR;   //栈为空
    e=*(S.top-1);
    return OK;
}
Status Push(SqStack &S,SElemType e){   //插入新的栈顶元素 e
    if(S.top-S.base>=S.stacksize){     //栈满了，追加新存储空间
        S.base=(SElemType*)realloc(S.base,(S.stacksize+STACKINCREMENT)*sizeof(SElemType));
        if(!S.base)exit(OVERFLOW);
        S.top=S.base+S.stacksize;
        S.stacksize+=STACKINCREMENT;
    }
    *S.top++=e;
    return OK;
}
Status Pop(SqStack &S,SElemType &e){   //删除栈顶元素
    if(S.top==S.base)return ERROR;  //空栈
    e=*(--S.top);
    return OK;
}
Status StackTraverse(){

}
void conversion(){
    
}
