/* 现有学校宿舍区之间要铺设光纤建设网络，在施工预算的统计数据表中，列出了有可能建设光缆的若干条管线的成本，
求使每栋楼都能够接入校园网且使管网建设费用成本最低。

输入：
第一行数据包括楼宇的数目正整数N（≤1000）和候选管网数目M（≤3N）；
随后的M行对应M条线路，每行给出3个正整数，分别是该条线路直接连通的两个楼宇的编号以及预算成本（为简单起见，城镇从1到N编号）。

输出：
输出建设楼楼通需要的最低成本。如果输入数据不足以保证畅通，则输出−1，表示需要建设更多的通路。
*/

#include<bits/stdc++.h>
using namespace std;
int tree[1001];
struct node{
    int point1,point2,cost;
}CableList[5005]; 
struct Rule{
    bool operator()(const node &A, const node &B)const{
        return A.cost<B.cost;
    }
};
void init(int cable){      //定义开头节点 每个人的开头节点都是自己
    for(int i=0;i<=cable;i++)tree[i]=i;
}
int find(int a){         //查找节点的开头节点
    if(tree[a]==a)return a;  //自己就是开头节点说明该节点没被使用过
    return tree[a]=find(tree[a]);   //如果被使用过，就不断递归去找开头节点
}
int judge(int a,int b){   //判断两个相连的节点是否成环
    if(find(a)!=find(b)){ //如果 a，b节点的开头节点不一样
        tree[find(a)]=find(b);        //则将a节点的开头设置为 b
        return 1;
    }
    return 0;
}
void kruskal(int building,int cable){   //kruskal 克鲁斯卡尔算法，计算最小生成树
    int sideselected=0,totalcost=0;
    init(cable);
    sort(CableList,CableList+cable,Rule());    //依成本顺序排列
    for(int i=0;i<cable;i++){
        if(judge(CableList[i].point1,CableList[i].point2)){   //如果两个相连节点的开头节点不一样
            sideselected++;                                   //选择该边
            totalc6ost+=CableList[i].cost;                     //更新成本
        }
        if(sideselected==building-1)break;
    }
    printf("%d\n",sideselected==building-1?totalcost:-1);
}
int main(){
    int building,cable;
    scanf("%d %d",&building,&cable);
    for(int i=0;i<cable;i++) scanf("%d %d %d",&CableList[i].point1,&CableList[i].point2,&CableList[i].cost);
    kruskal(building,cable);
    return 0;
}