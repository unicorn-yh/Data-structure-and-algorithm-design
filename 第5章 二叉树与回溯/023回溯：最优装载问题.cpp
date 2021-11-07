/*数据输入: 第1行有两个正整数c和n, 0<c<=100000，n<=100 . 接下来一行是n个正整数w1,w2,...,wn，表示n个集装箱的重量(保证在int内).
现要将集装箱放进载重量为c的一艘船上, 并在满足载重量限制的条件下, 求能放进船中的最大重量和对应的方案. 为此将这个问题表述为如下的优化问题:
对所有长为n的0,1序列(x1,x2,...,xn)，求在满足 w1x1+w2x2+...+wnxn ≤ c 条件下, w1x1+w2x2+...+wnxn的最大值. 
称这个最大值为最优值, 称能达到最优值的0,1序列(x1,x2,...,xn)为最优解. 当最优解不唯一时，称x1x2...xn作为二进制数最大的最优解为第一最优解.
结果输出:最优值和第一最优解. 最优解输出格式: 从小到大输出非零xi的编号i, 注意输出最后有个空格.

输入样例：
180 8
5 20 10 40 30 50 60 70

输出样例：
180
2 3 4 6 7
*/

#include<bits/stdc++.h>
using namespace std;
int numbox,cargo,weight[101],currentweight=0,bestweight=0,x[101]={0},isLoaded[101]={0};

void backtrack(int i){      //搜索第i层结点
	if(i>numbox){           //到达叶节点
        if(currentweight>bestweight){    //更新最优装载重量 bestw
            bestweight=currentweight;
            for(int i=1;i<=numbox;i++)isLoaded[i]=x[i];
        }
        return;     
    }
	if(currentweight+weight[i]<=cargo){    //搜索左子树，即 x[i]=1
        x[i]=1;
		currentweight+=weight[i];           
		backtrack(i+1);
        x[i]=0;
		currentweight-=weight[i];      
	}
    backtrack(i+1);                     //搜索右子树
}

int main()
{
    scanf("%d %d",&cargo,&numbox);
    for(int i=1;i<=numbox;i++) scanf("%d",&weight[i]);
    backtrack(1);
	printf("%d\n",bestweight);
    for(int i=1;i<=numbox;i++) if(isLoaded[i])printf("%d ",i);
    printf("\n");
	return 0;
}