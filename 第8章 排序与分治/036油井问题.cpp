/*主油管道为东西向，确定主油管道的南北位置，使南北向油井喷油管道和最小。要求线性时间完成。
1<= 油井数量 <=2 000 000
输入要求：
输入有油井数量行，第 K 行为第 K 油井的坐标 X ,Y 。其中， 0<=X<2^31,0<=Y<2^31 。
输出要求：
输出有一行， N 为主管道最优位置的最小值
注意：用快排做的不给分！！
友情提示：可以采用while(scanf("%d,%d",&x,&y) != EOF)的数据读入方式。*/

#include <bits/stdc++.h>
using namespace std;
vector<int> q;
int Partition(int l, int h) { 
    /*对顺序表L中子表r[low..high]的记录作一趟快速排序，并返回pivot记录所在位置。*/
    int low=l,high=h; //用第一个记录作pivot记录
    int pivotkey=q[low]; // pivotkey是pivot关键字
    while(low<high){ //从表的两端交替地向中间扫描
        while(low<high && q[high]>=pivotkey)--high;
        if(low<high)q[low++]=q[high];
        while (low<high && q[low]<=pivotkey)++low;
        if(low<high)q[high--]=q[low]; 
    } // 交替扫描结束
   q[low]=pivotkey; //pivot位置
    return low; //返回pivot位置
}
void Search(int well){
    int i=0,low=0,high=q.size()-1;
    while(1){
        i=Partition(low,high);
        if(i<well)low=i+1;
        else if(i>well)high=i-1;
        else break;
    }
}
int median(int length){
    if(length%2==0)return length/2-1;
    else return length/2;
}
int main(){
    int x,y,n;
    while(scanf("%d,%d",&x,&y)!=EOF)q.push_back(y);
    n=median(q.size());
    Search(n);
    printf("%d\n",q[n]);
    return 0;
}

/*41,969978
26500,413356
11478,550396
24464,567225
23281,613747
491,766290
4827,77476
14604,597006
292,706822
18716,289610
5447,914746

597006*/