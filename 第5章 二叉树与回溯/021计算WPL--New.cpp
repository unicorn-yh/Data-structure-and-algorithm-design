/*Huffman编码是通信系统中常用的一种不等长编码，它的特点是：能够使编码之后的电文长度最短。

输入：
第一行为要编码的符号数量n
第二行～第n+1行为每个符号出现的频率

输出：
对应哈夫曼树的带权路径长度WPL*/

#include <bits/stdc++.h>
using namespace std;
int main(){
    int Elemnum=0,temp1=0,temp2=0,total=0;
    priority_queue<int,vector<int>,greater<int>>p;
    scanf("%d",&Elemnum);
    for(int i=0;i<Elemnum;i++){
        scanf("%d",&temp1);
        p.push(temp1);
    }
    for(int i=0;i<Elemnum-1;i++){
        temp1=p.top();
        p.pop();
        temp2=p.top();
        p.pop();
        p.push(temp1+temp2);
        total+=temp1+temp2;
    }
    printf("WPL=%d\n",total);
    return 0;
}

