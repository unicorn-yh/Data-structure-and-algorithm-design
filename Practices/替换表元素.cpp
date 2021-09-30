//在A里找 x，用 y 代替 x
#include <bits/stdc++.h>
int x,y;
int find(int A[],int x,int i,int n){
    int k;
    if(i<0||i>=n) return -1;
    for(k=i;k<n && A[k]!=x;k++);
    return (k==n)?-1:k;
}
void replace(int A[],int n){
    int i=0,j,k=0;
    while(i<n){
        j=find(A,x,i,n);
        if(j!=-1){
            A[j]=y;     //找到含x的整数，用y替换x
            i=j+1;
        }
        else return;
    }
}