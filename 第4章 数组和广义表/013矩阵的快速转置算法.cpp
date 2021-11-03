/*矩阵的快速转置算法
数据压缩是提高传输、存储效率一种技术。教材第5章介绍了两种简单的压缩存储方法。本实验要求实现三元组顺序表表示下的矩阵快速转置算法。

输入：
稀疏矩阵的行数、列数、非零元个数(三个数都大于0)
以行为主序输入稀疏矩阵三元组表

输出：
辅助数组num[ ]
辅助数组cpot[ ]
以行为主序输出对应的转置矩阵三元组表*/

#include <bits/stdc++.h>
typedef int ElemType;
typedef int Status;
#define OK 1
#define MAXSIZE 100
int num[MAXSIZE],cpot[MAXSIZE];

typedef struct{
    int i,j;      //非0元素的行和列
    ElemType e;   //非0元素的值
}Triple;

typedef struct{
    Triple data[MAXSIZE];    
    int rownum,colnum,elemnum;  //行数，列数，元素个数
}TSMatrix;
TSMatrix input,trans;

Status FastTransMatrix(TSMatrix M,TSMatrix &T){
	T.rownum=M.rownum;
	T.colnum=M.colnum;
	T.elemnum=M.elemnum;
	if(T.elemnum){
		for(int k=0;k<100;k++) num[k]=0;    //初始化
        for(int k=1;k<=M.elemnum;++k) ++num[M.data[k].j];   //找出每列的非0元素个数
        cpot[1]=1;
        for(int k=2;k<=M.colnum;k++)cpot[k]=cpot[k-1]+num[k-1];  //列中第一个非0元素在T.data中的序号
		printf("num:");
    	for(int k=1;k<=M.colnum;k++)printf("%d,",num[k]);
    	printf("\n");
    	printf("cpot:");
    	for(int k=1;k<=M.colnum;k++)printf("%d,",cpot[k]);
    	printf("\n");
        for(int k=1;k<=M.elemnum;++k){
            int p=cpot[M.data[k].j];
            T.data[p].i=M.data[k].j;
            T.data[p].j=M.data[k].i;
            T.data[p].e=M.data[k].e;
            ++cpot[M.data[k].j];
        }	
	}
	return OK;
}

int main(){
	scanf("%d %d %d",&input.rownum,&input.colnum,&input.elemnum);	
	for(int k=1;k<=input.elemnum;k++)scanf("%d %d %d",&input.data[k].i,&input.data[k].j,&input.data[k].e);
    FastTransMatrix(input,trans);
	for(int k=1;k<=trans.elemnum;k++)printf("%d,%d,%d\n",trans.data[k].i,trans.data[k].j,trans.data[k].e);
    return 0;
}