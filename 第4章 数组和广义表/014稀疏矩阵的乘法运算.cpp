/*数据压缩是提高传输、存储效率一种技术。教材第5章介绍了两种简单的压缩存储方法。
本实验要求实现两个稀疏矩阵相乘积的算法。其中稀疏矩阵非零元素数量小于100.

输入：
第1个稀疏矩阵的行数，列数，非零元个数(三个数都大于0)，三元组
第2个稀疏矩阵的行数，列数，非零元个数(三个数都大于0)，三元组   
以行为主序输入稀疏矩阵三元组表

输出：
乘积矩阵的行数
列数
非零元个数(三个数都大于0)
三元组*/

#include <bits/stdc++.h>
#define MAXSIZE 1000
typedef int ElemType;
typedef int Status;
#define OK 1
#define ERROR 0
int rpos[MAXSIZE],num[MAXSIZE];

typedef struct{
    int i,j;             //存储非0元数的行和列
    ElemType e;          //非0元素的值
}Triple;

typedef struct{
    Triple data[MAXSIZE];
    int rpos[MAXSIZE];                //每行第一个元素的位置表
    int rownum,colnum,elemnum;
}RSLMatrix;

Status MultiplyMatrix(RSLMatrix M1,RSLMatrix M2,RSLMatrix &Q){
    if(M1.colnum!=M2.rownum)return ERROR;
    Q.rownum=M1.rownum;
    Q.colnum=M2.colnum;
    Q.elemnum=0;
    if(M1.elemnum*M2.elemnum!=0){
        for(int k=1;k<=M1.rownum;k++){
            int temp,temp2,col;
            memset(rpos,0,sizeof(rpos));
            Q.rpos[k]=Q.elemnum+1;        //Q行中非0元素的个数  累加
            if(k<M1.rownum)temp=M1.rpos[k+1];  //取该行M1非0元素的个数
            else temp=M1.elemnum+1;
            for(int p=M1.rpos[k];p<temp;p++){  //遍历M1行的非0元素
                int b=M1.data[p].j;            //获取该非0元素的列 
                if(b<M2.rownum)temp2=M2.rpos[b+1];   //取该行M2非0元素的个数
                else temp2=M2.elemnum+1;
                for(int q=M2.rpos[b];q<temp2;q++){   //遍历M2行的非0元素
                    col=M2.data[q].j;                //获取该非0元素的列
                    rpos[col]+=M1.data[p].e*M2.data[q].e;   //相乘后存入rpos数组，rpos为Q的非0元素位置表
                }
            }
            for(col=1;col<=Q.colnum;col++){
                if(rpos[col]){     //Q列中有非0元素
                    ++Q.elemnum;
                    Q.data[Q.elemnum].i=k;
                    Q.data[Q.elemnum].j=col;
                    Q.data[Q.elemnum].e=rpos[col];
                }
            }
        }
    }
    return OK;
}

RSLMatrix matrix1,matrix2,multiplymatrix;

int main(){
    scanf("%d%d%d",&matrix1.rownum,&matrix1.colnum,&matrix1.elemnum);
    for(int k=1;k<=matrix1.elemnum;k++)scanf("%d%d%d",&matrix1.data[k].i,&matrix1.data[k].j,&matrix1.data[k].e);
    scanf("%d%d%d",&matrix2.rownum,&matrix2.colnum,&matrix2.elemnum);
    for(int k=1;k<=matrix2.elemnum;k++)scanf("%d%d%d",&matrix2.data[k].i,&matrix2.data[k].j,&matrix2.data[k].e);

    for(int k=1;k<=matrix1.rownum;k++)num[k]=0;
    for(int k=1;k<=matrix1.elemnum;k++)++num[matrix1.data[k].i];   //找出每行的非0元个数
    matrix1.rpos[1]=1;
    for(int k=2;k<=matrix1.rownum;k++)matrix1.rpos[k]=matrix1.rpos[k-1]+num[k-1];
    for(int k=1;k<=matrix2.rownum;k++)num[k]=0;
    for(int k=1;k<=matrix2.elemnum;k++)++num[matrix2.data[k].i];   //找出每行的非0元个数
    matrix2.rpos[1]=1;
    for(int k=2;k<=matrix2.rownum;k++)matrix2.rpos[k]=matrix2.rpos[k-1]+num[k-1];

    MultiplyMatrix(matrix1,matrix2,multiplymatrix);

    printf("%d\n%d\n%d\n",multiplymatrix.rownum,multiplymatrix.colnum,multiplymatrix.elemnum);
    for(int k=1;k<=multiplymatrix.elemnum;k++)printf("%d,%d,%d\n",multiplymatrix.data[k].i,multiplymatrix.data[k].j,multiplymatrix.data[k].e);
    return 0;
}