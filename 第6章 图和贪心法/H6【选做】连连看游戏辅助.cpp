/*《连连看》是由一款益智类游戏。《连连看》只要将相同的两张牌用三根以内的直线连在一起就可以消除，规则简单容易上手。
本题编写程序模拟人进行连连看游戏，电脑模拟人玩连连看的过程如下：
1、分析本局游戏，将本局游戏转化成一个二位数组。0表示空白区域，数字表示该游戏牌为出现在游戏中的第几类游戏牌。
2、利用广度优先搜索算法，判断两个游戏牌是否可以消除。
3、程序模拟人点击可以消除的一对游戏牌进行消除。
对某局游戏转化成二维数组如下：
0 0 0 0 0
0 1 2 0 0
0 0 3 4 0
0 0 0 1 0
输入二位数组的行、列，二位数组、起始元素的的坐标、终止元素的坐标，判断起始游戏牌和终止游戏牌是否可以消除。
对上例输入：
4 5
0 0 0 0 0  0 1 2 0 0  0 0 3 4 0  0 0 0 1 0
1 1
3 3
输出：TRUE */

#include <bits/stdc++.h>
using namespace std;

int m,n,StartX,StartY,EndX,EndY,vir[1000][1000]={0},Map[1000][1000]={0};
int trend[4][2]={{0,1},{0,-1},{1,0},{-1,0}};    //0-下，1-上，2-右，3-左
struct Node{
    int x,y;//坐标
    int dir; //方向
    int turn;//转弯次数
};

void BFS(){
    queue<Node> q;
    Node k0,k1,t0;
    bool flag=false;
    for (int i = 0; i < 4; i++){   //初始化四个方向的点
        t0.x = StartX + trend[i][0];
        t0.y = StartY + trend[i][1];
        t0.dir = i;
        t0.turn = 1;
        vir[t0.x][t0.y] = t0.turn;
        q.push(t0);
    }
    while (!q.empty()){      //在队列中开始广度优先搜索
        k0 = q.front();
        q.pop();
        if (k0.x==EndX && k0.y==EndY){   //找到了终点
            flag = true;
            printf("TRUE\n");
            break;
        }
        for (int i = 0; i < 4; i++){  //对当前点遍历四个方向
            k1.x = k0.x + trend[i][0];
            k1.y = k0.y + trend[i][1];
            k1.dir = i;
            if (k1.dir != k0.dir) k1.turn = k0.turn + 1;  //方向发生改变则相当于转弯了
            else k1.turn = k0.turn;
            if (k1.turn > 3 || k1.x < 0 || k1.y < 0 || k1.x > m - 1 || k1.y > n - 1)
            {//如果边树大于三条边了或者是超出地图范围了就不考虑了直接下一个
                continue;
            }
            if (Map[k1.x][k1.y] != 0 && Map[k1.x][k1.y] != Map[EndX][EndY])
            {//如果在地图上这个点不是0且不是终点，相当于走不通，也不考虑了直接下一个
                continue;
            }
            if (vir[k1.x][k1.y] == 0 || vir[k1.x][k1.y] >= k1.turn)
            {   //如果是个未访问对点，或者是转向角度低于图中的点。
                //因为图中转向角度大的点相当于已经访问过了，甚至是已经到3不符合要求的点
                vir[k1.x][k1.y] = k1.turn;//更新我们刚算的转向值
                q.push(k1);//并压入队列等待下一轮判定
            }
        }
    }
    if (!flag) printf("FALSE\n");
}

int main(){
    scanf("%d %d",&m,&n);
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            scanf("%d",&Map[i][j]);
    scanf("%d %d",&StartX,&StartY);
    scanf("%d %d",&EndX,&EndY);
    BFS();
    return 0;
}
