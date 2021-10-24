#include <bits/stdc++.h>
typedef int ElemType;
typedef int Status;
#define MAX_ARRAY_DIM 8
#define OK 1
#define ERROR 0

typedef struct{
    ElemType *base;   //数组元素基址，由 InitArray分配
    int dim;          //数组维数  dimension
    int *bounds;      //数组维界基址，由 InitArray分配
    int *constants;   //数组映像函数常量基址，由 InitArray分配
}Array;

Status InitArray(Array &A,int dim);
Status DestroyArray(Array &A);
Status Value(Array A,ElemType &e);
Status Assign(Array &A,ElemType &e);

Status InitArray(Array &A,int dim){   //维数 dim
    if(dim<1||dim>MAX_ARRAY_DIM) return ERROR;
    A.dim=dim;
    A.bounds=(int*)malloc(dim*sizeof(int));
    if(!A.bounds)exit(OVERFLOW);
    int elemtotal=1;
    va_list ap;       //存放变长参数表信息的数组
    va_start(ap,dim);
    for(int i=0;i<dim;i++){
        A.bounds[i]=va_arg(ap,int);
        if(A.bounds[i]<0) return UNDERFLOW;
        elemtotal*=A.bounds[i];
    }
    va_end(ap);
    A.base=(ElemType*)malloc(elemtotal*sizeof(ElemType));
    if(!A.base)exit(OVERFLOW);
    

}


