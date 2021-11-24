/*本实验实现邻接表表示下无向图的广度优先遍历。
程序的输入是图的顶点序列和边序列(顶点序列以*为结束标志，边序列以-1,-1为结束标志)。
程序的输出为图的邻接表和广度优先遍历序列。
*/

#include<bits/stdc++.h>
using namespace std;
struct node{
    int data,isVisited,adjPoint[100],adjCount;
}PointList[100]; 

int main(){
    queue <node> q;
    int pointCount=0,point1,point2;
    scanf("%d",&pointCount);
    for(int i=0;i<pointCount;i++){
        PointList[i].data=i;
        PointList[i].adjCount=0;
        PointList[i].isVisited=0;   //flag记录顶点是否被访问过
    }
    while(1){                            //记录每个顶点的相邻顶点
        scanf("%d",&point1);
        if(point1==-1)break;
        scanf("%d",&point2);
        PointList[point1].adjPoint[PointList[point1].adjCount]=point2;  //更新point1的相邻节点：adjList数组
        PointList[point1].adjCount++;                                   //更新point1的相邻节点个数
        PointList[point2].adjPoint[PointList[point2].adjCount]=point1;  //更新point2的相邻节点：adjList数组
        PointList[point2].adjCount++;                                   //更新point2的相邻节点个数
    }
    for(int i=0;i<pointCount;i++){       //BFS 深度优先搜索
        if(PointList[i].isVisited==0){   //当前节点未被访问过
            int flag=0;
            q.push(PointList[i]);        //当前节点入队
            PointList[i].isVisited=1;    //记录：已被访问
            struct node tmp;
            while(!q.empty()){           //还有节点还未被访问
                tmp=q.front();
                q.pop();                //队头的所有相邻节点出队
                if(flag++)printf("-");
                printf("%d",tmp.data);  //输出队头节点
                if(tmp.adjCount==0)continue;
                sort(tmp.adjPoint,tmp.adjCount+tmp.adjPoint);
                for(int j=0;j<=tmp.adjCount;j++){    //遍历访问队头节点的相邻顶点
                    if(PointList[tmp.adjPoint[j]].isVisited==0){  //若该相邻节点未被访问过
                        q.push(PointList[tmp.adjPoint[j]]);       //当前相邻节点入队
                        PointList[tmp.adjPoint[j]].isVisited=1;   //记录：已被访问   
                    }
                } 
            }
            printf("\n");
        }
    }
    return 0;
}