/**/

/*思路：优先删除全部孤立点，随后考虑度为1的结点（即树中的叶子结点），因为叶子结点必须要被覆盖，
将其与父亲结点比较可知，将士兵放置在父亲结点可得到更优解。
删除父亲结点和叶结点，继续寻找新的叶子结点，直到所有结点都被覆盖。*/

#include<bits/stdc++.h>
using namespace std;
int soilder[1505][2],father[1505],visit[1505],num;
void DFS(int root){
    visit[root]=1;
    for(int i=0;i<num;i++){
        if(visit[i]==0 && father[i]==root){  //若当前节点未被访问 && 父节点=当前根结点
            DFS(i);
            soilder[root][1]+=soilder[i][0];
            soilder[root][0]+=min(soilder[i][0],soilder[i][1]);
        }
    }
    soilder[root][0]++;
}
int main(){
    int tree,roadcount,temp,root=0;
    while(~scanf("%d",&num)){
        memset(soilder,0,sizeof(soilder));
        memset(visit,0,sizeof(visit));
        memset(father,0,sizeof(father));
        for(int i=0;i<num;i++){
            scanf("%d:(%d)",&tree,&roadcount);
            if(i==0)root=tree;        //设置根结点
            for(int j=0;j<roadcount;j++){
                scanf("%d",&temp);
                father[temp]=tree;    //设置每个结点的父节点
            }
        }
        DFS(root);
        printf("%d\n",min(soilder[root][0],soilder[root][1]));
    }    
    return 0;
}