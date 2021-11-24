/* 
求从指定源点出发到各个顶点的最短路径。
假设：图中结点名均为单个互不相同的字母，权值均>0。

输入：
第一行：结点数量n，弧数量e，源点
后续e行：<结点，结点，权值>

输出：
按结点的升序输出到达各个结点的最短路径长度
*/

#include<bits/stdc++.h>
using namespace std;
#define Inf 0x3f3f3f3f
int mapList[1005][1005];
int visit[1005]={0},power[1005];

void init(int sidecount){      //初始化 map 数组
    for(int i=0;i<sidecount;i++)
        for(int j=0;j<sidecount;j++)
            mapList[i][j]=(i==j)?0:Inf;
}
void GetMap(int sidecount){
    char point1,point2;
    int tmppower=0;
    for(int i=0;i<sidecount;i++){
        scanf("<%c,%c,%d>",&point1,&point2,&tmppower);
        getchar();
        int x=point1-'a';
        int y=point2-'a';
        if(mapList[x][y]>tmppower) mapList[x][y]=tmppower;
    }
}
void Dijkstra(int source,int sidecount){
    for(int i=0;i<sidecount;i++)power[i]=mapList[source][i];
    visit[source]=1;
    power[source]=0;
    for(int i=0;i<sidecount;i++){
        int min=Inf,temp;
        for(int j=0;j<sidecount;j++){
            if(visit[j]==0 && power[j]<min){
                min=power[j];
                temp=j;
            }
        }
        visit[temp]=1;
        for(int j=0;j<sidecount;j++)
            power[j]=(mapList[temp][j]+power[temp]<power[j])?(mapList[temp][j]+power[temp]):power[j];
    }
}
int main(){
    int pointcount=0,sidecount=0;
    char source;
    scanf("%d,%d,%c",&pointcount,&sidecount,&source);
    getchar();
    init(sidecount);
    GetMap(sidecount);
    Dijkstra(source-'a',sidecount);
    for(int i=0;i<pointcount;i++)printf("%c:%d\n",i+'a',power[i]);
    return 0;
}