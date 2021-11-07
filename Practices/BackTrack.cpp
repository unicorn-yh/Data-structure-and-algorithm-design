#include <bits/stdc++.h>
//回溯法 递归 深度优先搜索 DFS 
void backtrack(int t){
    if(t>n)printf(x);
    else{
        for(int i=f(n,t);i<g(n,t);i++){
            x[t]=h(i);
            if(constraint(t)&&bound(t))backtrack(t+1);
        }
    }
}

//树 非递归遍历 深度优先搜索 DFS
void iterativeBacktrack(){
    int t=1;                      //根结点 t
    while(t>0){                   
        if(f(n,t)<=g(n,t)){      //f为下确界，g为上确界
            for(int i=f(n,t);i<=g(n,t);i++){
                x[t]=h(i);                     //把所遍历的结点存储进数组 x
                if(constraint(t)&&bound(t)){   //约束函数 constraint, 上界函数 bound
                    if(solution(t))printf(x);  //t为解
                    else t++;
                }
            }
        }
        else t--;
    }
}

//遍历子集树  计算时间 O(2^n)
void backtrack(int t){    //根结点 t
    if(t>n)printf(x);     //结点数 n
    else{
        for(int i=0;i<=1;i++){
            x[t]=i;
            if(legal(t))backtrack(t+1);  //结点 t有可能是解，继续搜索其子节点
        }
    }
}

//遍历排列树  计算时间 O(n!)
void backtrack(int t){
    if(t>n)print(x);
    else{
        for(int i=t;i<=n;i++){  //以结点t为起点，搜索其下子节点
            swap(x[t],x[i]);    
            if(legal(t))backtrack(t+1);
            swap(x[t],x[i]);
        }
    }
}

//装载问题（子集树）
//可行性约束函数：(i=1->n) Σ(WiXi)<=C1
//上界函数：不选择当前元素，当前载重量 cw+剩余集装箱的重量 r<=当前最优载重量 bestw
void backtrack(int i){
    if(i>n){     //达到叶节点 更新最优解 bestw
        if(cw>bestw){
            bestw=cw;
            for(int i=1;i<=numbox;i++)isLoaded[i]=x[i];
        }
        return; 
    }
    if(cw+w[i]<=c){ //搜索子左数
        x[i]=1;
        cw+=w[i];
        backtrack(i+1);
        x[i]=0;
        cw-=w[i];
    }
    backtrack(i+1);
}
void backtrack(int i){  //搜索第i层结点
    if(i>n) return;  //达到叶节点 更新最优解 bestw,bestx
    r-=w[i];
    if(cw+w[i]<=c){ //搜索左子树
        x[i]=1;
        cw+=w[i];
        backtrack(i+1);
        cw-=w[i];
    }
    if(cw+r>bestw){
        x[i]=0;   //搜索右子树
        backtrack(i+1);
    }
    r+=w[i];
}

//批处理作业调度  排列树
//n个作业的集合{J1,J2,...,Jn}，每个作业必需先由机器 1处理，再由机器 2处理，作业 Ji 所需处理时间 tji
//Fji：作业 i在机器 j上完成处理的时间；作业调度的完成时间和：所有作业在机器 2上完成处理的时间和
class Flowshop{
    friend Flow(int**,int,int[]);
    void Backtrack(int i);
    int* *M,     //作业所需处理时间
    int* *x;     //当前作业调度
    int* *bestx; //当前最优作业调度
    int* *f2;    //机器2完成处理的时间
    int* f1;     //机器1完成处理的时间
    int* f;      //完成时间和
    int* bestf;  //当前最优值
    int* n;      //作业数
}
void Flowshop::backtrack(int i){
    if(i>n){
        for(int j=1;j<=n;j++)bestx[j]=x[j];
        bestf=f;
    }
    else{
        for(int j=i;j<=n;j++){
            f1+=M[x[j]][1];
            f2[i]=((f2[i-1]>f1)?f2[i-1]:f1)+M[x[j]][2];
            f+=f2[i];
            if(f<bestf){
                swap(x[i],x[j]);
                backtrack(i+1);
                swap(x[i],x[j]);
            }
            f1-=M[x[j]][1];
            f-=f2[i];
        }
    }
}

//符号三角形问题
//解向量：n元数组 x[1:n], 表示符号三角形的第一行
//可行性约束函数：当前符号三角形所包含的 “+” & “-” 个数不超过 n*(n+1)/4
//无解的判断：n*(n+1)/2 为奇数
void Triangle::backtrack(int t){
    if((count>half)||(t*(t-1)/2-count>half))return;
    if(t>n)sum++;
    else{
        for(int i=0;i<2;i++){
            p[1][t]=i;
            count+=i;
            for(int j=2;j<=t;j++){
                p[j][t-j+1]=p[j-1][t-j+1]^p[j-1][t-j+2];
                count+=p[j][t-j+1];
            }
            backtrack(t+1);
            for(int j=2;j<=t;j++)count-=p[j][t-j+1];
            count-=i;
        }
    }
}

//n后问题：皇后可攻击同行/列/斜线的棋子（n×n棋盘，n个皇后，任意2个皇后不放在同行/列/斜线）
//解向量：（X1,X2,...,Xn）
//显约束：Xi=1,2,...,n
//隐约数：1.不同列：Xi≠Xj；2.不处于同一正、反对角线：|i-j|≠|Xi-Xj|
void Queen::backtrack(int t){
    if(t>n)sum++;
    else{
        for(int i=1;i<=n;i++){
            x[t]=i;
            if(Place(t))backtrack(t+1);
        }
    }
}
bool Queen::Place(int k){
    for(int j=0;j<k;j++)
        if((abs(k-j)==abs(x[j]-x[k]))||(x[j]==x[k])) return false;
    return true;
}
bool Queen::ComparePlace(int row,int col){   //比较函数
    for(int i=0;i<row;i++)
        if(abs(row-i)!=abs(col-arr[i])||col==arr[i])return false;
    return true;
}
void Queen::backtrack1(int t){
    if(t==n){   //求出一种解
        sum++;  //更新解的数量
        return;
    }
    for(int i=0;i<n;i++){      //已定行t，遍历列
        if(ComparePlace(t,i)){ //若所放置的皇后不同行、列、斜线
            arr[t]=i;          //皇后 t 的位置处于 i列
            backtrack1(t+1);   //回溯搜索：行 t+1 的皇后摆放位置
        }
    }
}



//背包问题：不需把背包的载重量划分为等分、物体的重量是背包载重量等分的整数倍的限制
//可行性约束函数：(i=1->n) Σ(WiXi)<=C1
void backtrack(int i){  //搜索第i层结点
    if(i>n) return;  //达到叶节点 更新最优解 bestp,bestx
    r-=w[i];
    if(cw+w[i]<=c){ //搜索左子树
        x[i]=1;
        cw+=w[i];
        cp+=p[i];
        backtrack(i+1);
        cw-=w[i];
        cp-=p[i];
    }
    if(bound(i+1)>bestp){
        x[i]=0;   //搜索右子树
        backtrack(i+1);
    }
}
template<class Typew,class Typep>
Typep Knap<Typew,Typep>::bound(int i){   //计算上界
    Typew cleft=c-cw;          //剩余容量
    Typep b=cp;                
    while(i<=n&&w[i]<=cleft){  //以物品单位重量价值递减序装入物品
        cleft-=w[i];
        b+=p[i];
        i++;
    }
    if(i<=n)b+=p[i]/w[i]*cleft; //装满背包
    return b;
}

//最大团问题（子集树，计算时间 O(n2^n)）
//U是G的最大团，当且仅当U是G的最大独立集（U是独立集，当且仅当 U不包含在G更大的空子图中）
//可行性约束函数：顶点 i到以选入的顶点集中，每一个顶点都有边相连
//上界函数：有足够多的可选择顶点使得算法有可能在右子树中找到更大的团
void Clique::backtrack(int i){ //计算最大团
    if(i>n){
        for(int j=1;j<i;j++)bestx[j]=x[j];
        bestn=cn;
        return;
    }
    int OK=1;
    for(int j=1;j<i;j++)
        if(x[j]&&a[i][j]==0){   //i与j不相连
            OK=0;
            break;
        }
    if(OK){   //进入左子树
        x[i]=1;
        cn++;
        backtrack(i+1);
        x[i]=0;
        cn--;   
    }
    if(cn+n-i>bestn){   //进入右子树
        x[i]=0;
        backtrack(i+1);
    }

}

//图的 m着色问题（总耗时 O(nm^n)）
//一个图最少需要m种颜色才能使图中每个相邻顶点颜色不同，色数=m
//解向量：（X1,X2,...,Xn）表示顶点i所着颜色 x[i]
//可行性约束函数：顶点 i与已着色的相邻顶点颜色不重复
//约束方程：若顶点i与顶点j相邻，x[i]≠x[j]
void Color::backtrack(int t){   //解空间树（用时 O(m^n-1)）
    if(t>n){
        sum++;
        for(int i=1;i<=n;i++) cout<<x[i]<<' ';
        cout<<endl;
    }
    else{
        for(int i=1;i<=m;i++){
            x[t]=i;
            if(Ok(t))backtrack(t+1);
        }
    }
}
bool Color::Ok(int t){  //检查当前扩展结点的每个儿子的颜色可用性（用时 O(mn)）
    for(int j=1;j<=n;j++)
        if((a[k][j]==1)&&(x[j]==x[k])) return false;
        return true;
}

//旅行售货员问题 (排列树 O(n!))
void backtrack(int t){
    if(t>n)printf(x);
    else{
        for(int i=t;i<=n;i++){
            swap(x[t],x[i]);
            if(legal(t))backtrack(t+1);
            swap(x[t],x[i]);
        }
    }
}
template<class Type>
void Traveling<Type>::backtrack(int i){
    if(i==n){
        if(a[x[n-1]][x[n]]!=NoEdge && a[x[n]][1]!=NoEdge && (cc+a[x[n-1]][x[n]]+a[x[n]][1]<bestc || bestc==NoEdge)){
            for(int j=1;j<=n;j++) bestx[j]=x[j];
            bestc=cc+a[x[n-1]][x[n]]+a[x[n]][1];
        }
    }
    else{
        for(int j=i;j<=n;j++)
            if(a[x[i-1]][x[j]]!=NoEdge && (cc+a[x[i-1]][x[i]]<bestc || bestc==NoEdge)){   //搜索子树
                swap(x[i],x[j]);
                cc+=a[x[i-1]][x[i]];
                backtrack(i+1);
                cc-=a[x[i-1]][x[i]];
                swap(x[i],x[j]);
            }
    }
}

//圆排列问题：要求从n个圆的所有排列中找出有最小长度的圆排列
void Circle::Compute(void){  //计算当前圆排列的长度
    float low=0;high=0;
    for(int i=1;i<=n;i++){
        if(x[i]-r[i]<low)low=x[i]-r[i];
        if(x[i]+r[i]>high)high=x[i]+r[i];
    }
    if(high-low<min)min=high-low;
}
float Circle::Center(int t){  //计算当前所选择圆的圆心横坐标
    float temp=0;
    for(int j=1;j<t;j++){
        float valuex=x[j]+2.0*sqrt(r[t]*r[j]);
        if(valuex>temp)temp=valuex;
    }
    return temp;
}
void Circle::backtrack(int t){
    if(t>n)Compute();
    else{
        for(int j=t;j<=n;j++){
            swap(r[t],r[j]);
            float centerX=Center(t);
            if(centerX+r[t]+r[1]<min){  //下界约束
                x[t]=centerX;
                backtrack(t+1);
            }
            swap(r[t],r[j]);
        }
    }
}

//连续邮资问题
for(int j=0;j<=x[i-2]*(m-1);j++)
    if(y[j]<m)
        for(int k=1;k<=m-y[j];k++)
            if(y[j]+k<y[j+x[i-1]*k])
                y[j+x[i-1]*k]=y[j]+k;
while(y[r]<maxint)r++;
