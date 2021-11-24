/* 假设要用很多个教室对一组活动进行调度。我们希望使用尽可能少的教室来调度所有的活动。
输入要求：
第一行为活动的个数 N(1<=N<=1 000 000) 。
接下来 N 行为 Si 和 Fi(0<=Si<Fi<=2 000 000 000) ，分别代表第 i 个活动的开始时间和结束时间。活动 i 的区间段为 [Si,Fi)

输出要求：
输出有一行 M ，为所需教室的最小数量。
*/

#include<bits/stdc++.h>
using namespace std;
int starttime[1000000],finishtime[1000000];
int main(){
    int classroomcount=0,n=0,tmpcount=0,i=0,j=0;
    scanf("%d",&n);   //输入活动数量
    for(int i=0;i<n;i++)scanf("%d %d",&starttime[i],&finishtime[i]);
    sort(starttime,starttime+n);     //从小到大排列活动开始时间
    sort(finishtime,finishtime+n);   //从小到大排列活动结束时间
    while(i<n && j<n){
        if(starttime[i]<finishtime[j]){    //活动开始时间在结束时间之前
            tmpcount++;                    //课室数量暂时+1
            i++;                           //下次循环从下一个开始时间开始
            classroomcount=max(classroomcount,tmpcount);  //更新课室数量
        }
        else if(starttime[i]>finishtime[j]){   //活动开始时间在结束时间之后
            tmpcount--;                        //课室数量暂时-1
            j++;                               //下次循环从下一个结束时间开始
        }
        else{                                //活动开始时间 = 结束时间
            j++;
            i++;
            classroomcount=max(classroomcount,tmpcount);
        }
    }
    printf("%d\n",classroomcount);
    return 0;
}