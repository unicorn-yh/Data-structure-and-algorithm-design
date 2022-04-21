/*用堆排序算法按关键字递减的顺序排序。
输入：待排序记录数（整数）和待排序记录（整数序列）；
输出：建堆结果和建堆后第一、第二次筛选结果。（注：待排序记录数大于等于3）*/

#include <bits/stdc++.h>
using namespace std;
void max_heapify(int arr[], int start, int end) {  //建立大根堆
    //建立父节点指标和子节点指标
    int dad = start;
    int son = dad*2+1;
    while (son<=end){  //若子节点指标在范围内才做比较
        if (son + 1 <= end && arr[son] < arr[son + 1])son++; //先比较两个子节点大小，选择最大的
        if (arr[dad] > arr[son])return; //如果父节点大於子节点代表调整完毕，直接跳出函数
        else{//否则交换父子内容再继续子节点和孙节点比较
            swap(arr[dad],arr[son]);
            dad = son;
            son = dad*2+1;
        }
    }
}
void heap_sort(int arr[], int len) {   //排序堆
    int k=1; //初始化，i从最後一个父节点开始调整
    for (int i=len/2-1; i>=0; i--)max_heapify(arr,i,len-1);
    for(int i=0;i<len;i++)printf("%d ",arr[i]);
    printf("\n");
    //先将第一个元素和已排好元素前一位做交换，再重新调整，直到排序完毕
    for (int i=len-1;i>0;i--){     //锁定最后一个结点之后继续建立剩余未锁定结点的大根堆
        swap(arr[0],arr[i]);
        max_heapify(arr,0,i-1);
        if(k<=2){
            for(int i=0;i<len-k;i++)printf("%d ",arr[i]);
            printf("\n");
        }
        k++;
        
    }
}
int main(){
    int n;
    scanf("%d",&n);
    int a[n];
    for(int i=0;i<n;i++)cin>>a[i];
    heap_sort(a,n);
    return 0;
}

/*6
输入：
11
12
16
14
15
10

输出：
16 15 11 14 12 10 
15 14 11 10 12 
14 12 11 10

输入：
9
9
8
7
6
5
4
3
2
1

输出：
9 8 7 6 5 4 3 2 1 
8 6 7 2 5 4 3 1 
7 6 4 2 5 1 3*/

