/*题目
在本实验中，需要同学们利用队列实现一个飞机场调度模拟，根据不同的输入参数得到不同的模拟结果。
程序运行开始，首先需要输入以下参数：
机场跑道数，飞机降落占用跑道时间（整数）， 飞机起飞占用跑道时间（整数）
整个模拟的时间以分钟为单位，从 0 开始，每分钟的开始需要输入：
该分钟要求降落飞机数， 该分钟要求起飞飞机数
机场调度原则是降落优先起飞，在此原则下按来的顺序排队；每驾飞机都有一个编号，要起飞飞机从 1 开始，
要降落飞机从 5001 开始；每驾飞机需要等待的时间是从其提要求开始到分配跑道为止；每个跑道都有一个编号（从 1 开始），
都可以用来降落和起飞，但同一时间只能被一架飞机占用，占用时间为该飞机降落（起飞）占用跑道时间。
当输入的要求降落飞机数和要求起飞飞机数都小于 0 时，表示机场关闭，不再接受新的请求，
但余下没有降落（起飞）的飞机需照常进行。

模拟过程中需要随时输出以下数据：
1. 当前时间 (%4d)
2. 所有从占用变为空闲的跑道编号 （在输入降落、起飞飞机数前输出）
3. 可以降落（起飞）飞机编号（％ 04d ）、跑道编号（％ 02d ） （在输入降落、起飞飞机数后输出）

模拟结束后，程序需输出以下统计结果：
1. 模拟时间（％ 4d ）
2. 降落平均等待时间（％ 4.1f ）
3. 起飞平均等待时间（％ 4.1f ）
4. 每条跑道被占用时间（％ 4d ）
5. 跑道平均被占用的百分比（％ 4.1f ， 平均占用时间× 100/ 模拟时间）
*/

#include <bits/stdc++.h>
int main(){
    int runway,timelanding,timetakeoff;
    scanf("%d %d %d",&runway,&timelanding,&timetakeoff);
    int currentlanding,currenttakeoff,countlanding=0,counttakeoff=0;
    int templanding=0,temptakeoff=0,time=0,flag=1,stopflag=0;
    int airport[runway],busy[runway];
    memset(airport,0,sizeof(airport));
    memset(busy,0,sizeof(busy));
    float totalbusy=0,averagebusy=0,waitlanding=0,waittakeoff=0;
    printf("Current Time: %4d\n",time++);
    scanf("%d %d",&currentlanding,&currenttakeoff);
    templanding+=currentlanding;
    temptakeoff+=currenttakeoff;
    while(templanding>=0 && temptakeoff>=0){   //有输入的循环
        for(int i=0;i<runway;i++){
            if(airport[i]==0){
                if(templanding>0){
                    airport[i]=timelanding;
                    countlanding++;
                    templanding--;
                    printf("airplane %d is ready to land on runway %02d\n",5000+countlanding,i+1); 
                }
                else if(templanding==0 && temptakeoff>0){
                    airport[i]=timetakeoff;
                    counttakeoff++;
                    temptakeoff--;
                    printf("airplane %04d is ready to takeoff on runway %02d\n",counttakeoff,i+1);
                }
            }
            if(airport[i]!=0) busy[i]++;
        }
        printf("Current Time: %4d\n",time++);
        if(templanding>0)waitlanding+=templanding;
        if(temptakeoff>0)waittakeoff+=temptakeoff;
        for(int i=0;i<runway;i++){
            if(airport[i]>1)airport[i]--;
            else if(airport[i]==1){
                airport[i]=0;
                printf("runway %02d is free\n",i+1);
            }
        }
        scanf("%d %d",&currentlanding,&currenttakeoff);
        if(currentlanding>=0 && currenttakeoff>=0){
            templanding+=currentlanding;
            temptakeoff+=currenttakeoff;
        }
        else break;                             //输入小于0时结束循环
    }

    while(templanding>=0 && temptakeoff>=0){     //没有输入的循环
        flag=0;                                 //判断跑道是否为空的条件
        for(int i=0;i<runway;i++){
            if(airport[i]==0){
                if(templanding>0){
                    airport[i]=timelanding;
                    countlanding++;
                    templanding--;
                    printf("airplane %d is ready to land on runway %02d\n",5000+countlanding,i+1); 
                }
                else if(templanding==0 && temptakeoff>0){
                    airport[i]=timetakeoff;
                    counttakeoff++;
                    temptakeoff--;
                    printf("airplane %04d is ready to takeoff on runway %02d\n",counttakeoff,i+1);
                }
            }
            if(airport[i]!=0) busy[i]++;
        }
        printf("Current Time: %4d\n",time++);
        if(templanding>0)waitlanding+=templanding;
        if(temptakeoff>0)waittakeoff+=temptakeoff;
        for(int i=0;i<runway;i++){
            if(airport[i]>1)airport[i]--;
            else if(airport[i]==1){
                airport[i]=0;
                printf("runway %02d is free\n",i+1);
            }
        }
        if(templanding==0 && temptakeoff==0){  //当所有飞机已经成功起飞和降落
            for(int i=0;i<runway;i++){
                if(airport[i]!=0)flag=1;      //判断所有跑道是否为空
            }
            if(flag==0)break;              //所有跑道为空，退出
        }

    }
    printf("simulation finished\n");
    printf("simulation time: %4d\n",--time);
    printf("average waiting time of landing: %4.1f\n",waitlanding/countlanding);
    printf("average waiting time of takeoff: %4.1f\n",waittakeoff/counttakeoff);
    for(int i=0;i<runway;i++){
        printf("runway %02d busy time: %4d\n",i+1,busy[i]);
        totalbusy+=busy[i];
    }
    printf("runway average busy time percentage: %4.1f%%\n",(totalbusy*100)/(time*runway));
    return 0;
}