
//用折半法求 x^2+2x-1=0 在区间 [a,b] 中的根
#include <bits/stdc++.h>
#define Fa a*a+2*a-1
#define Fb b*b+2*b-1
#define Fm mid*mid+2*mid-1
float findRoot(float a,float b){
    float x,y,mid,fa,fb,fm;
    int i,n=100;          //n是最大迭代次数
    fa=Fa,fb=Fb;          //区间两端点的函数值
    if(fa*fb<=0){         //区间中有根则继续执行
        x=a,y=b;          //区域的左右两个端点
        for(i=0;i<n;i++){
            mid=(x+y)/2;
            fm=Fm;
            if(fabs(Fm)<0.001 || fabs(y-x)<0.001)break;  //求到跳出循环
            if(Fa*Fm>0){      //fa与fm正负号相同，区间没有根，舍弃区间 [a,m]，向右缩小区间
                fa=fm;
                x=mid; 
            }
            else{             //fa与fm正负号相反，区间内有根，舍弃区间 (m,b)，向左缩小区间
                fb=fm;
                y=mid;
            }
        }
        return mid;
    }
}
