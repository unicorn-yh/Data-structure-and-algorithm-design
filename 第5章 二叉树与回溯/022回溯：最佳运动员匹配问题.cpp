/*羽毛球队有男女运动员各n人. 给定2个n*n矩阵P和Q. P[i][j]是男运动员i与女运动员j配混合双打的男运动员竞赛优势; 
Q[i][j]是女运动员i与男运动员j配混合双打的女运动员竞赛优势. 由于技术配合和心理状态等各种因素影响, 
P[i][j]不一定等于Q[j][i]. 男运动员i和女运动员j配对的竞赛优势是P[i][j]*Q[j][i]. 
设计一个算法, 计算男女运动员最佳配对法, 使得各组男女双方竞赛优势的总和达到最大.

数据输入:第1行有一个正整数n(1<=n<=12), 接下来2n行是P和Q

结果输出:最佳配对的各组男女双方竞赛优势总和 
*/

#include<bits/stdc++.h>
using namespace std;
#define N 13
int P[N][N],Q[N][N],PQ[N][N];
int maxPQ[N]={0};   // 0-i 男女运动员匹配的最大优势
bool visitQ[N]={false};  //记录女运动员是否被访问过
int n,tempScore=0,maxScore=0;  //当前优势，最大优势

void backtrack(int t){  //回溯的终点
	if(t>n){
        maxScore=max(maxScore,tempScore);   //更新最大优势
        return;
    }
    if(tempScore+maxPQ[n]-maxPQ[t-1]<maxScore)return;  //剪枝操作：就算后面都不合理贪心选择都不能超过
    for(int i=1;i<=n;i++){
        if(visitQ[i])continue;   //女运动员已被选择匹配
        visitQ[i]=true;
        tempScore+=PQ[t][i];
        backtrack(t+1);
        visitQ[i]=false;
        tempScore-=PQ[t][i];
    }
}

int main(){
	scanf("%d",&n);

	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			scanf("%d",&P[i][j]);   //男运动员i与女运动员j配混合双打的男运动员竞赛优势
		
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			scanf("%d",&Q[i][j]);  //女运动员i与男运动员j配混合双打的女运动员竞赛优势

    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            PQ[i][j]=P[i][j]*Q[j][i];

    for(int i=1;i<=n;i++){       //贪心获取 0-i 男女运动员匹配的最大优势，女运动员重复被选取
        for(int j=1;j<=n;j++)
            maxPQ[i]=max(maxPQ[i],PQ[i][j]);  //更新男女运动员匹配的最大优势
        maxPQ[i]+=maxPQ[i-1];
    }
	backtrack(1); 
	printf("%d\n",maxScore);
	return 0;
} 