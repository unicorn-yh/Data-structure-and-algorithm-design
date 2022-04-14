/*说明： AOE 网络是有向无环加权图，其中顶点表示事件，弧表示活动，权表示活动持续的时间，通常可以用来估算工程完成的时间，
即图中从开始点到结束点之间最长的路径对应的时间。请完成一个程序，完成下列任务：
1 、计算 AOE 网络对应的拓扑排序。如果排序结果不唯一，请输出按照从小到大的顺序排列的结果。
从小到大的顺序就是输入的节点序列顺序（参见下面关于输入格式的说明）。如图1中满足要求的拓扑排序是： 
a-b-c-d-e-f-g-h-k ,图2中满足要求的拓扑排序是：v1-v3-v5-v2-v6-v4-v7-v8-v9
2 、计算 AOE 网络的关键路径。注意关键路径可能不唯一，要求输出所有的关键路径。同样，按照是按照从小到大的顺序输出。
例，如果得到两条关键路径，分别是0-1-3-6-8-9和0-1-3-4-5-8-9，那么先输出后一条路径，因为两条路径中前三个节点相同，
而后一条路径第四个节点的编号小。

测试用例的输入输出格式说明：
输入：
节点的个数，边的条数；
各个节点的名称序列
边： < 起点 , 终点 , 权值 > 。说明起点和终点是在各个点在输入序列中的位置，如图1中边 <a,b> 表示为 <0,1,6> 。

输出：
拓扑排序；
关键路径*/

#include <bits/stdc++.h>
int nodeNum, edgeNum;
int topo[55], path[100];
struct link{
    int dir;//目标位置
    int val;//权值
};
struct{
    char name[5];
    int inNum = 0; //入度
    int outNum = 0; //出度
    int Etv, Ltv;//存储事件的最早和最晚发生时间 
    link linkTo[300];
    int linkNum = 0;
}node[50];

int cmp1(const void *p1, const void *p2){
    struct link *c = (link *)p1;
    struct link *d = (link *)p2;
    return (c->dir) > (d->dir);
}
int cmp2(const void *p1, const void *p2){
    struct link *c = (link *)p1;
    struct link *d = (link *)p2;
    return (c->dir) < (d->dir);
}

/*把顶点和边信息读入到表示图的邻接表中*/
void CreateGraph(){
    /*input for name str of nodes*/
    char str[500]={'\0'};
    scanf("%s",str);
    int len = strlen(str),q=0,k=0;
    for(int i = 0; i < len; i++){
        if (str[i]!=',') node[k].name[q++] = str[i];
        else{
            node[k].name[q] = '\0';
            k++;
            q = 0;
        }
    }

    int p = 0, k_flag = 0;
    int ch_data[5], cd_p = 0;
    char chs[10] = { '\0' }, ch;
    getchar();
    while ((ch = getchar())){
        if (ch == '\n' || ch == -1)
            break;
        if (ch == '<'){
            k_flag = 1;
            continue;
        }
        if (ch == ','&&k_flag == 1){
            ch_data[cd_p] = atoi(chs);
            memset(chs, '\0', sizeof(chs));
            p = 0;
            cd_p++;
            continue;
        }
        if (ch != '<'&&ch != ','&&k_flag == 1 && ch != '>'){
            chs[p++] = ch;
            continue;
        }
        if (ch == '>'&&k_flag == 1){
            ch_data[cd_p] = atoi(chs);
            int u = ch_data[0];
            node[u].linkTo[node[u].linkNum].dir = ch_data[1];
            node[u].linkTo[node[u].linkNum].val = ch_data[2];
            node[u].outNum++;
            node[ch_data[1]].inNum++;
            node[u].linkNum++;
            k_flag = 0;
            p = 0;
            cd_p = 0;
            memset(chs, '\0', sizeof(chs));
            continue;
        }
    }
    for (int i = 0; i < nodeNum; i++) //先对邻节点排序，输出即是按顺序的
        qsort(node[i].linkTo, node[i].linkNum + 1, sizeof(node[i].linkTo[0]), cmp1);
}

/*广度优先搜索获取拓扑序列 */
int TopoLogicalSort_DFS(){
    int *Stack, u, v, top = 0, count = 0;
    Stack = (int*)malloc(sizeof(int) * nodeNum); //分配栈空间
    for (int i = 0; i < nodeNum; i++){    //将入度为0的顶点入栈 
        node[i].Etv = 0; //初始化各事件最早发生事件为0 
        if (node[i].inNum == 0)
            Stack[top++] = i;
    }
    while (top > 0){   //采用广度优先搜索获取拓扑序列 
        u = Stack[--top];
        topo[count++] = u;
        for (int i = 0; i <= node[u].linkNum; i++){ //将u的邻接点入度减1，并将入度为0的顶点入栈 
            int v = node[u].linkTo[i].dir;
            if (node[v].Etv < node[u].Etv + node[u].linkTo[i].val)//更新各顶点事件的最早发生时间 
                node[v].Etv = node[u].Etv + node[u].linkTo[i].val;
            if (--node[v].inNum == 0)
                Stack[top++] = v;
        }
        qsort(Stack,top,sizeof(Stack[0]),cmp2);//使得输出的拓扑序列中无拓扑关系的节点要从小到大输出，但入栈是从大到小
    }
    free(Stack);
    return (count == nodeNum);//如果count小于顶点数，说明存在环 
}

/*路径输出*/
void PrintPath(int top, int end){
    int u = path[top - 1];
    if (u == end){
        printf("%s", node[path[0]].name); //输出关键路径 
        for (int i = 1; i < top; i++)
            printf("-%s", node[path[i]].name);
        printf("\n");
        return;
    }
    for (int i = 0; i <= node[u].linkNum; i++){
        int v = node[u].linkTo[i].dir;
        if (node[u].Etv + node[u].linkTo[i].val < node[v].Etv)
            continue;
        if (node[v].Etv == node[v].Ltv){  //关键事件
            path[top++] = node[u].linkTo[i].dir;//入栈
            PrintPath(top, end);
            top--;//退栈
        }
    }
}

/*求关键路径*/
void CriticalPath(){
    if (!TopoLogicalSort_DFS()){
        printf("NO OPOLOGICAL PATH\n");
        return;
    }
    for (int i = 0; i < nodeNum; i++){
        node[i].Ltv = node[nodeNum - 1].Etv; //初始化各事件最晚发生事件为最后一个事件发生的时间 
        if (i)
            printf("-");
        printf("%s", node[topo[i]].name); //这里方便题目要求的打印拓扑序列
    }
    printf("\n");
    for (int i = nodeNum - 2; i >= 0; i--){
        int u = topo[i];
        for (int j = 0; j <= node[u].linkNum; j++){
            int v = node[u].linkTo[j].dir;
            if (node[u].Ltv > node[v].Ltv - node[u].linkTo[j].val)//更新各顶点事件的最晚发生时间 
                node[u].Ltv = node[v].Ltv - node[u].linkTo[j].val;
        }
    }
    path[0] = topo[0];
    PrintPath(1, topo[nodeNum - 1]);
}

int main(){
    scanf("%d,%d", &nodeNum, &edgeNum);
    CreateGraph();//把顶点和边信息读入到表示图的邻接表中 
    CriticalPath();//求关键路径
    return 0;
}
