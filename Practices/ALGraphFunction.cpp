//图的操作
#include<stdio.h>
#include<stdlib.h>
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define OVERFLOW -2
#define MAX_NUM 20

typedef int Status;
typedef int QElemType;
typedef char VexType;

typedef  struct EdgeNode{
	int adjvex;            //定点的位置 
	struct EdgeNode *next;//下一个定点的位置 
}EdgeNode,*EdgeLink;//建立邻接表 

typedef struct Vex{
	VexType data;      //顶点的数据 
	EdgeNode *firstEdge;//指向第一条邻节点的指针 
}VexNode,AdjList[MAX_NUM];//建立顶点数组； //结构数组 

typedef struct{
	AdjList adjlist;
	int vexNum,edgeNum;//定点数和边的数目 
}ALGraph; //图的邻接表存储结构

//队列的存储结构 图的广度搜索

typedef struct Node{
	QElemType data;
	struct Node *next;
	
}QNode,*QueuePtr; 

typedef struct{
	QueuePtr front;
	QueuePtr rear; 
}LinkQueue;

//初始化队列
Status InitQueue(LinkQueue *Q)
{
	Q->front = Q->rear = (QNode*)malloc(sizeof(QNode));
	if(Q->front)
	{
		Q->front->next = NULL;
		return OK;
	 } 
 } 
 
//判断是否为空
Status IsEmpty(LinkQueue Q)
{
	if(Q.front->next == NULL) return TRUE;
	else return FALSE;
 } 

//入队
Status EnQueue(LinkQueue *Q, QElemType e)
{
	QueuePtr p = (QueuePtr)malloc(sizeof(QNode));
	if(p){
		p->data = e;
		p->next= NULL;
		Q->rear->next = p;
		Q->rear = p;
		return OK;
	}
	else return ERROR;

} 

//出队(带有头结点)
Status DeQueue(LinkQueue *Q, QElemType *e)
{
	QueuePtr q;
	if(Q->front==Q->rear)return ERROR;
	q = Q->front->next;
	*e = q->data;
	Q->front->next = q->next;
	if(Q->rear = q)
	{
		Q->rear = Q->front;
	}
	free(q);
	return OK; 
	
} 

//创建图（邻接表表示）(无向图)
Status CreateGraph(ALGraph *G)
{
	
	int i,j,k;
	EdgeLink e;
	printf("请输入顶点数和变数\n"); 
	scanf("%d %d",&G->vexNum,&G->edgeNum);
//	scanf("%d",&G->edgeNum);
	getchar();//吃掉回车
	//请输入个顶点的数据 
	printf("请输入各顶点的数据:\n");
	for(i=0;i<G->vexNum;i++)//初始化顶点数组 
	{
		scanf("%c",&G->adjlist[i].data);
		if(G->adjlist[i].data=='\n')
		{
			i--;
			continue;	
		}
		G->adjlist[i].firstEdge=NULL; 
	 } 
	//
	printf("请输入顶点（vi,vj)边定点的序号\n");
	
	for(k=0;k<G->edgeNum;k++)
	{
		scanf("%d %d",&i,&j);
	//	scanf("%d",&j);
		e = (EdgeLink)malloc(sizeof(EdgeNode));
		e->adjvex = j;
		e->next = G->adjlist[i].firstEdge ;
		G->adjlist[i].firstEdge = e;
		e = (EdgeLink)malloc(sizeof(EdgeNode));
		e->adjvex=i;
		e->next = G->adjlist[j].firstEdge;
		G->adjlist[j].firstEdge = e;
		
	}
	return OK;	
 } 
 
 int visited[MAX_NUM]; //用于记录遍历状态
  
 //递归从第i个结点深度优先遍历图
void DFS(ALGraph G, int i)
{
	EdgeLink e;
	visited[i] = TRUE;
	printf("%c",G.adjlist[i].data);
	e = G.adjlist[i].firstEdge;
	while(e)
	{
		if(!visited[e->adjvex])
		{
			DFS(G,e->adjvex);	
		}
		e =e->next;
	}
}

//广度优先遍历图
Status BFSTraverse(ALGraph G)
{
	int i;
	EdgeLink p;
	LinkQueue Q;
	InitQueue(&Q);
	for(i=0;i<MAX_NUM;i++) visited[i]=FALSE;
	for(i=0;i<G.vexNum;i++){  //vexNum 为节点数量
		if(!visited[i]){     //没被访问过
			visited[i]=TRUE; //访问该节点
			printf("%c",G.adjlist[i].data);   //输出该顶点的数据
			EnQueue(&Q,i);        //该顶点入队Q
			while(!IsEmpty(Q)){   //Q队列不空，还有未遍历到的节点
				DeQueue(&Q,&i);   //该顶点出队Q
				p = G.adjlist[i].firstEdge;  //让p=顶点的第一个相邻顶点
				while(p){                    //p存在
					if(!visited[p->adjvex]){   //相邻顶点未被访问
						visited[p->adjvex]=TRUE;   //访问该相邻顶点
						printf("%c",G.adjlist[p->adjvex].data); //输出该相邻顶点的数据
						EnQueue(&Q,p->adjvex);                 //该相邻顶点入队
					}
					p=p->next;         //p指向该顶点的下一个相邻顶点
				}	
			}
		}
	}
	return OK;	
}

//无权图单源最短路径问题
void BFS_Distance(Graph G，int v)
{
	for(int i=0;i<G.vexnum;++i)
		d[i] = MAX;
	visited[v] = true;
	d[v] = 0;
	EnQueue(Q,v);
	while(!isEmpty(Q)){		//不空还有未遍历到的节点 
		DeQueue(Q,v);		//出队v 
		for(w = FirstNeighbor(G,v);w>=0;w=NextNeighbor(G,v,w))		//找到所有符合条件的邻接节点 
			if(!visited[w]){		//w是否被访问  
				visited[w] = true;	//修改该顶点对应数组的值为true
				d[w] = d[v] + 1;
				EnQueue(Q,w);		//入队 
			}
	}
}

int main(){
    ALGraph G;
    CreateGraph(&G);
    printf("深度优先遍历:");
    DFS(G,0);
    printf("\n广度优先遍历:");
    BFSTraverse(G);
    printf("\n");
}
