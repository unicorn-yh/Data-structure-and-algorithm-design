#include <bits/stdc++.h>
#define MAXSIZE 1000
typedef int ElemType;
typedef int Status;
#define OK 1
#define ERROR 0

typedef struct{
    int i,j;             //存储非0元数的行和列
    ElemType e;          //非0元素的值
}Triple;

typedef struct{
    Triple data[MAXSIZE]; 
    int rownum,colnum,elemnum;            //行数、列数、非0元个数
}TSMatrix;

typedef struct{
    Triple data[MAXSIZE];
    int rpos[MAXSIZE];                //每行第一个元素的位置表
    int rownum,colnum,elemnum;
}RSLMatrix;

Status FastTransMatrix(TSMatrix M,TSMatrix &T){
    T.rownum=M.colnum;
    T.colnum=M.rownum;
    T.elemnum=M.elemnum;
    if(T.elemnum){
        for(int k=0;k<M.colnum;++k) num[k]=0;    //初始化
        for(int k=0;k<M.elemnum;++k) ++num[M.data[k].j];   //找出每列的非0元素个数
        cpot[0]=1;
        for(int k=0;k<M.colnum;++k)cpot[k]=cpot[k]+num[k];  //列中第一个非0元素在T.data中的序号
        for(int k=1;k<M.elemnum;++k){
            int p=cpot[M.data[k].j];
            T.data[p].i=M.data[k].j;
            T.data[p].j=M.data[k].i;
            T.data[p].e=M.data[k].e;
            ++cpot[M.data[k].j];
        }
    }
    return OK;
}

Status MultiplyMatrix(RSLMatrix M1,RSLMatrix M2,RSLMatrix &Q){
    int rpos[1000];
    if(M1.colnum!=M2.rownum)return ERROR;
    Q.rownum=M1.rownum;
    Q.colnum=M2.colnum;
    Q.elemnum=0;
    if(M1.elemnum*M2.elemnum!=0){
        for(int k=1;k<M1.rownum;k++){
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

