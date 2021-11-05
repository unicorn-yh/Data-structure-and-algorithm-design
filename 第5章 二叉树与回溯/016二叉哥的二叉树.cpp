/*题目描述
传说计算机学院有一位前辈叫做二叉哥，他十八般算法样样精通。他当年在程设的时候由于二叉树一举成名。
大家为了纪念这一事件，尊称他为二叉哥！二叉树是一个什么样的东西呢？现在我们就来揭开二叉哥的二叉树的神秘面纱吧！
下图就是一棵有着9个节点的二叉树。顾名思义，二叉树就像一棵倒着生长的树，每个分叉点可以分出去两个枝条。
我们把分叉点叫做"节点”，因为每个分叉点最多可以分出去两个枝条，所以就叫做"二叉”树。
最顶层只有一个节点，我们把它叫做根节点。下图中，标号为1的节点就是根节点，它有两个孩子：节点2和节点3。
节点2只有一个孩子，标号为4，而节点3有两个孩子，标号分别为5和6。下图中的二叉树第3层有3个节点，分别是7、8和9号节点。

二叉哥对于二叉树的掌握已经到了出神入化的程度，为了维护他的二叉树霸主地位，他准备了2^2^2^2^2个问题来迎接挑战者，
现在我们来看下第0道吧。一个有n个节点的二叉树的第m层至多有多少个节点？

 输入
输入的第一行为一个数字T（1 <= T <= 10000），表示有T组数据。
接下来的T行每行有两个数字n和m（0 <= n, m <= 10^8），表示二叉树有n个节点，求m层最多有多少个节点。
根节点所在的为第0层。

输出
每个用例输出一个数字，表示最多的节点个数。
*/

#include <bits/stdc++.h>
int count,t,flag;
void countNode(int n,int m){
    if(t>m||n==0)return;
    int a=pow(2,t)-1;
    if(n-a>0){
        count+=pow(2,t-1);
        if(flag==0)t++;
        countNode(n-a,m);
    }
    if(n-a==0){
        count+=pow(2,t-1);
        return;
    }
    if(n-a<0){
        t--;
        flag=1;
        countNode(n-1,m);
    }
    return;
}
int main(){
    int T,n,m;
    scanf("%d",&T);
    while(T--){
        scanf("%d %d",&n,&m);
        if(n<m+1){
            printf("0\n");
            continue;
        }
        if(n==m+1){
            printf("1\n");
            continue;
        }
        n-=(m+1);
        t=1;
        count=1;
        flag=0;
        countNode(n,m);
        printf("%d\n",count);
    }
    return 0;
}