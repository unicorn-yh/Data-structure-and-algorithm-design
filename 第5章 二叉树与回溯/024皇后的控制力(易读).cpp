/*题目描述：
我们对八皇后问题进行扩展。
国际象棋中的皇后非常神勇，一个皇后可以控制横、竖、斜线等4个方向（或者说是8个方向），只要有棋子落入她的势力范围，
则必死无疑，所以对方的每个棋子都要小心地躲开皇后的势力范围，选择一个合适的位置放置。如果在棋盘上有两个皇后，
则新皇后控制的势力范围与第一个皇后控制的势力范围可以进行叠加，这样随着皇后数量的增加，皇后们控制的范围越来越大，
直至控制了棋盘中全部的格子。
现在我们关心的是，如果在 N×N 的棋盘上放入 M 个皇后（M个皇后相互之间不能冲突）控制棋盘中的格子，
则共有多少种不同的放置方法？

输入: N (N <= 10)  M (M < N)

输出： 如果将 M 个皇后放入 N×N 的棋盘中可以控制全部棋盘中的格子，则不同的放置方法的数量*/

#include <bits/stdc++.h>
int n,m,arr[101]={0},sum=0;
int visit[11][11]={0};     //记录格子是否被皇后控制，大于0就是被皇后控制了
#define max(x,y) (x<y?y:x)
#define min(x,y) (x<y?x:y)
bool ComparePlace(int row,int col){   //比较函数
    if(abs(row-col)==abs(arr[row]-arr[col])||arr[row]==arr[col])return false; 
    return true;
}
int isControlled(){    //检查所有格子是否被皇后控制了
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            if(visit[i][j]==0)return 0; 
    return 1;    
}
void BottomRightPower(int a,int i,bool add){
    int rowstart=max(a-i+1,1);       //向右下的对角线
    int columnstart=max(1,i-a+1);
    for(int j=rowstart,k=columnstart;j<=n&&k<=n;j++,k++){
        if(add==true)visit[j][k]++;          //更新皇后遍布的势力
        else visit[j][k]--;
    }
}
void BottomLeftPower(int a,int i,bool add){
    int rowstart=min(n,a+i-1);     //向左下的对角线
    int columnstart=max(1,i-(n-a));
    for(int j=rowstart,k=columnstart;j>=1&&k<=n;j--,k++)
        if(add==true)visit[j][k]++;        //更新皇后遍布的势力
        else visit[j][k]--;
}
void RowColumnPower(int row,int column,bool add){
    for(int temp=1;temp<=n;temp++){     //计算皇后行和列的势力
        if(add==true){
            visit[row][temp]++;       //已定行，遍历列，更新皇后的势力
            visit[temp][column]++;    //已定列，遍历行，更新皇后势力
        }
        else{
            visit[row][temp]--;       //已定行，遍历列，更新皇后的势力
            visit[temp][column]--;    //已定列，遍历行，更新皇后势力
        }
    }
}
void backtrack(int t,int s){
    if(m-s+1>n-t+1) return;  //剩余皇后大于剩余行数，返回
    if(s==m+1){                    //求出一种解
        if(isControlled())sum++;  //如果整个棋盘都被皇后的势力控制了，更新解的数量
        return;
    }
    for(int i=1;i<=n;i++){      //已定行t，遍历i列  
        int flag=1;
        arr[t]=i;      //皇后 t 的位置处于 i列    
        for(int j=1;j<t;j++){
            if(arr[j]!=0)  
                if(!ComparePlace(t,j)){  //皇后冲突的话
                    flag=0;
                    break;
            }
        }
        if(flag){   //这个位置没问题才放下一行
            RowColumnPower(t,i,true);   //增加皇后势力的遍布
            BottomRightPower(t,i,true);   
            BottomLeftPower(t,i,true);
            visit[t][i]-=3;
            backtrack(t+1,s+1);

            RowColumnPower(t,i,false);   //回溯完后，还原初始状态
            BottomRightPower(t,i,false);   //减少皇后势力的遍布
            BottomLeftPower(t,i,false);
            visit[t][i]+=3;
        }
    }
    arr[t]=0;    //这行可以不放
    backtrack(t+1,s);
}
int main(){
    scanf("%d %d",&n,&m);
    backtrack(1,1);
    printf("%d\n",sum);
    return 0;
}