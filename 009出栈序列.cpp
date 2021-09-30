/*
1.求解规定序列能否由入栈出栈操作得到
输入：有若干组数据输入
每组数据中，第一行为两个个整数 n 和 m。n 表示需要依次从 1~n 入栈，m 表示这组数据有 m 个出栈序列需要判断，
当 n=0 且 m=0 时停止。
接下来有行，每行表示一个出栈序列
输出：对每一个出栈序列,如果能正常出栈,输出Yes，否则输出 No。
*/

#include <bits/stdc++.h>
using namespace std;
int x[1010]={0},y[1010]={0};
int main(){
    int n,m,flag=0;
    while(scanf("%d%d",&n,&m) && n+m){
        if(flag)printf("\n");
        for(int i=1;i<=n;i++)x[i]=i;
        while(m--){
            for(int j=1;j<=n;j++)scanf("%d",&y[j]);
            stack<int>s;
            int a=1,b=1;
            while(b<=n){
                if(x[a]==y[b]){   
                    a++;
                    b++;
                }
                else if(!s.empty()&&s.top()==y[b]){  //栈顶元素和输入元素相同则弹栈
                    s.pop();
                    ++b;
                }
                else if(a<=n){      //初始数据压线
                    s.push(x[a]);
                    ++a;
                }
                else break;
            }
            if(s.empty())printf("Yes\n");
            else printf("No\n");
        }
        flag=1;
    }
    return 0;
}