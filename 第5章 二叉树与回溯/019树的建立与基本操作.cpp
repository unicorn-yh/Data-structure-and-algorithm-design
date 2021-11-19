/*程序的输入是一个表示树结构的广义表。假设树的根为 root ，其子树森林 F ＝ （ T1 ， T2 ， … ， Tn ），
设与该树对应的广义表为 L ，则 L ＝（原子，子表 1 ，子表 2 ， … ，子表 n ），其中原子对应 root ，
子表 i （ 1<i<=n ）对应 Ti 。例如：广义表 (a,(b,(c),(d)),(f,(g),(h ),(i))) 表示的树如图所示：
程序的输出为树的层次结构、树的度以及各种度的结点个数。
*/

#include<bits/stdc++.h>
void outputFormat(char c[],int level[],int n){
    for(int i=0;i<n;i++){
        for(int j=0;j<level[i];j++)printf("    ");
        printf("%c\n",c[i]);
    }    
}

int main(){
    int n=0,maxdegree=0,depth=-1;
    char c[100],ch;
    int degree[100]={0};  //记录每个节点的度
    int level[100]={0};   //记录每个节点的层次（depth）
    int count[100]={0};   //记录每个度的个数
    ch=getchar();
    while(ch!='\n'){
        switch(ch){
            case '(': depth++;break;
            case ')': depth--;break;
            case ' ': break;
            case ',': break;
            default : c[n]=ch;level[n++]=depth;break;
        }
        ch=getchar();
    }
    outputFormat(c,level,n);   //按照凹入表示法输出树
    for(int i=0;i<n-1;i++){    //找每个节点的度 & 树的度
        for(int j=i+1;j<n;j++){
            if(level[i]==level[j])break;         //遇到同层级的节点，该i节点无子节点，接下去的子节点都属于j
            if(level[i]+1==level[j])degree[i]++;  //找到该节点的子节点，该点的度+1，degree数组域：[0,maxdegree]
        }
        maxdegree=(degree[i]>maxdegree)?degree[i]:maxdegree;   //每次循环都更新树的度
    }
    printf("Degree of tree: %d\n",maxdegree);    //输出树的度
    for(int i=0;i<n;i++) count[degree[i]]++;      
    for(int i=0;i<=maxdegree;i++) printf("Number of nodes of degree %d: %d\n",i,count[i]);
    return 0;
}