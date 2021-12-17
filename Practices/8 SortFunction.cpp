/***************************
 * 插入排序：直接插入排序（顺序查找）、折半插入排序（折半查找）、希尔排序（基于逐趟缩小增量）
 * 交换排序：冒泡排序、快速排序
 * 选择排序：简单选择排序、堆排序
 * 归并排序：2-路归并排序
 * 基数排序
 * 
 * 顺序查找：两个基本操作-比较/移动
 * 监视哨兵设置在R[0]; R[0] = R[i]; 从后面开始查找
 * 从R[i-1]起向前顺序查找，直到找到插入位置
 * for (j=i-1; R[0].key < R[j].key; --j)R[j+1] = R[j]; //向后移位
 * 插入位置是：j+1, R[j+1] = R[0]; //插入
 * 
 * 希尔排序：
 * 1. 对数据分组，在各组内进行直接插入排序；
 * 2. 作若干次使待排记录基本有序；
 * 3. 对全部记录进行一次顺序插入排序；
 * 
 * 堆排序：
 * 选择最小关键字：比较n-1次
 * 选择其它当前最小关键字： 𝒍𝒐𝒈𝒏
 * 排序的时间复杂度：O(𝒏𝒍𝒐𝒈𝒏)
 * 空间复杂度 O(n) 
 * 大顶堆：
 * 1. 建立初始堆；
 * 2. 输出堆顶元素(交换堆顶元素和最后一个元素的位置) ；
 * 3. 调整堆
 * 优先队列的定义
 * 优先队列中的每一个元素都有一个优先级值。
 * 通常约定优先级值小的优先级高
 * 优先队列支持的基本运算有：
 * Size( )：返回优先队列中元素个数。
 * Min( )：返回优先队列中最小优先级值元素。
 * Insert(x)：将元素x插入优先队列。
 * DeleteMin(x)：删除优先队列中具有最小优先级值的元素，并保存到x中
 * 
 * 完全二叉树: 
 * r2i 是 ri 的左孩子；
 * r2i+1 是 ri 的右孩子。
 * 含有n 个关键字的完全二叉树的深度h= [log2n] +1。
 * 
 * 冒泡排序
 * 时间复杂度O(n^2)
 * 空间复杂度O(1)
 * 
 * 快速排序
  本质就是把基准数大的都放在基准数的右边,把比基准数小的放在基准数的左边,这样就找到了该数据在数组中的正确位置.
 * 
 * 
 * *****************************/

#define MAXSIZE 1000 // 待排顺序表最大长度
typedef int KeyType; // 关键字类型为整数类型
typedef struct{ // 记录类型
    KeyType key; // 关键字项
    InfoType otherinfo; // 其它数据项
}RcdType; 
typedef struct {// 顺序表类型
    RcdType r[MAXSIZE+1]; // r[0]闲置
    zint length; // 顺序表长度
} SqList; 

//顺序查找 直接插入排序
void InsertionSort ( SqList &L ) {
    // 对顺序表 L 作直接插入排序。
    for ( i=2; i<=L.length; ++i ) {
        L.r[0] = L.r[i];  // 复制为监视哨兵
        for ( j=i-1;L.r[0].key<L.r[j].key;--j)L.r[j+1] = L.r[j]; // 查找并后移
        L.r[j+1] = L.r[0]; // 插入到正确位置
    }
}
void InsertSort(int a[],int left,int right){
    int temp;
    for(int i=left + 1; i<=right; i++){
        temp=a[i];
        for(int j=i-1;j>=0&&num[j]>temp;j--)a[j+1]=a[j];
        if (int j!=i-1)a[j+1]=temp;
    }
}

//折半插入排序
void BinsertSort(SqList &L){
    for(i=2;i<=L.length;i++){
        L.r[0]=L.r[i];
        low=1; high=i-1;
        while(low<high){
            mid=(low+high)/2;
            if(L.r[0].key<L.r[mid].key)) high=mid-1;
            else low=mid+1; 
        } //找high和low的值
        for(j=i-1 ; j >= high +1 ; j--) L.r[j+1]=L.r[j]; //后移
        L.r[high+1]=L.r[0];  //插入
    }
}

//希尔排序
void ShellSort (DataList& L, int delta[], int m) {
//按 delta[m] 中给出的间隔，对表 L 做希尔排序
    int i, start, gap;
    for (i = m-1; i >= 0; i--) {
        gap = delta[i];
        for (start=0; start<gap;start++)
        insertSort_gap (L,start,gap);
    } //直到delta[0] =1停止迭代
}
void insertSort_gap (DataList& L,int start,int gap) {
//对从start开始间隔为gap的子序列做直接插入排序
    DataType temp; int i, j;
    for (i=start+gap; i<=L.n-1;i+=gap){
        if (L.data[i-gap] > L.data[i]) { //发现逆序 （区间内 从后开始算
            temp = L.data[i]; j = i; //在前面有序表
            do { //寻找插入位置
                L.data[j] = L.data[j-gap];
                j = j-gap; 
            } while( j-gap > 0 && L.data[j-gap] > temp );
            L.data[j] = temp;
        }
    }   
}

//选择排序
void SelectSort (Elem R[], int n ) {
    for (i=1; i<n; ++i) {// 对记录序列R[1..n]作简单选择排序。
        j = SelectMinKey(R, i, n);// 选择第 i 小的记录，并交换到位，在 R[i..n] 中选择关键字最小的记录
        if (i!=j) R[i]←→R[j]; // 与第 i 个记录交换
    }
}

//堆排序
typedef SqList HeapType;
typedef struct {
    ElemType *elem; // 存储空间基址
    int length;     // 当前长度
    int listsize; // 当前分配的存储容量
              // (以sizeof(ElemType)为单位)
}SqList;
void HeapAdjust (HeapType &H, int s, int m){   //筛选过程=建大根堆
    // 已知 H.R[s..m]中记录的关键字除 R[s] 之外均
    // 满足堆的特征，本函数自上而下调整 R[s] 的
    // 关键字，使 H.R[s..m] 也成为一个大顶堆
    rc=H.R[s]; //暂存R[s]
    for(j=2*s;j<=m;j*=2){ //j初值指向左孩子（r2i）右孩子（r2i+1）
        /*...筛选过程...*/
        if (j<m && H.R[j].key<H.R[j+1].key) ++j; //令 j 指示关键字较大记录的位置（左/右“子树根”之间先进行相互比较
        if (rc.key>=H.R[j].key) break; // 根比大子树根大，不需要继续往下调整（“根”和“大子树根”之间的比较
        H.R[s]=H.R[j];s=j;   //根比大子树根小，往下调整，s指向较大子树根节点
    }
    H.R[s]=rc;    //将调整前的堆顶记录插入到s位置
}
void HeapSort(HeapType &H){ // 对顺序表 H 进行堆排序
    for (i=H.length/2;i>0;--i) // 建大顶堆
        HeapAdjust (H.R,i,H.length);
    for (i=H.length;i>1;--i) { // 将堆顶记录和当前未经排序子序列  
        swap(H.R[1],H.R[i]);   // 第一个和最后一个记录相互交换
        HeapAdjust(H.R,1,i-1); // 对 H.R[1] 进行筛选
    }
} 
void swap(int *a,int *b){
    int tmp=*a;
    *a=*b;
    *b=tmp;
}
void max_heapify(int arr[], int start, int end) {
    //建立父节点指标和子节点指标
    int dad = start;
    int son = dad * 2 + 1;
    while (son <= end)  //若子节点指标在范围内才做比较
        {
            if (son + 1 <= end && arr[son] < arr[son + 1]) 
            //先比较两个子节点大小，选择最大的
            son++;
        if (arr[dad] > arr[son]) //如果父节点大於子节点代表调整完毕，直接跳出函数
            return;
        else  //否则交换父子内容再继续子节点和孙节点比较
        {
            swap(&arr[dad], &arr[son]);
            dad = son;
            son = dad * 2 + 1;
        }
    }
}
void heap_sort(int arr[], int len) {
    int i;
    //初始化，i从最後一个父节点开始调整
    for (i = len / 2 - 1; i >= 0; i--)
        max_heapify(arr, i, len - 1);
    //先将第一个元素和已排好元素前一位做交换，再重新调整，直到排序完毕
    for (i = len - 1; i > 0; i--) 
    {
        swap(&arr[0], &arr[i]);
        max_heapify(arr, 0, i - 1);
    }
}
 int main() {
    int arr[] = { 3, 5, 3, 0, 8, 6, 1, 5, 8, 6, 2, 4, 9, 4, 7, 0, 1, 8, 9, 7, 3, 1, 2, 5, 9, 7, 4, 0, 2, 6 };
    int len = (int) sizeof(arr) / sizeof(*arr);
    heap_sort(arr, len);
    int i;
    for (i = 0; i < len; i++)
        printf("%d ", arr[i]);
    printf("\n");
    return 0;
}

//冒泡排序
Void bubble-sort (int a[]，int n){ //起泡排序，从小到大排列
    for(i=n-1,change=TRUE; i>1 && change;--i){
        change=false;
        for(j=0;j<i;++j)
            if (a[j]>a[j+1]){
                swap(a[j],a[j+1]);
                change=TRUE;
            }
    }
}

//快速排序
int Partition(SqList &L, int low, int high) { 
    /*对顺序表L中子表r[low..high]的记录作一趟快速排序，并返回pivot记录所在位置。*/
    L.r[0]=L.r[low]; //用第一个记录作pivot记录
    pivotkey=L.r[low].key; // pivotkey是pivot关键字
    while(low<high){ //从表的两端交替地向中间扫描
        while(low<high && L.r[high]. Key>=pivotkey)--high;
        L.r[low]=L.r[high]; 
        while (low<high && L.r[low]. Key<=pivotkey)++low;
        L.r[high]=L.r[low]; 
    } // 交替扫描结束
    L.r[low]=L.r[0]; //pivot位置
    return low; //返回pivot位置
}
void Qsort(SqList &L, int low, int high) {//对顺序表L中的子序列L.r[low.. high]作快速排序
    if(low<high){ 
        pivotloc=Partition(L,low,high); 
        QSort(L, low, pivotloc-1); 
        Qsort(L, pivotloc+1, high);
    }
}
void QuickSort(SqList &L ) {//对顺序表L快速排序
    QSort(L, 1, L.length); 
}
//改进的快速排序
void Quicksort(ElementType A[], int N) { 
    Qsort(A,0,N-1); 
}
void Qsort( ElementType A[], int Left, int Right ) { 
    int i, j; 
    ElementType Pivot; 
    if ( Left + Cutoff >= Right ) InsertionSort( A + Left, Right - Left + 1 );
    else {
        /*改进的快速排序*/
        Pivot = Median3( A,Left,Right); /* 选择枢轴*/
        i=Left+1; j=Right-2; 
        while(1){ 
            while (A[i++]<Pivot);/* 从左扫描 */
            while (A[j--]>Pivot); /* 从右扫描 */
            if(i<j) Swap(&A[i],&A[j]); /* 部分调整 */
            else break; /* 调整完成 */
        } 
        Swap(&A[i],&A[Right-1]); /* 存储pivot*/
        Qsort(A,Left,i-1); /* 递归的对左边进行快速排序 */
        Qsort(A,i+1,Right); /*递归对右边进行快速排序 */
    }
}
ElementType Median3( ElementType A[ ], int Left, int Right ){ /* 选择pivot*/
    int Center = ( Left + Right ) / 2;
    if ( A[ Left ] > A[ Center ] ) Swap( &A[ Left ], &A[ Center ] ); 
    if ( A[ Left ] > A[ Right ] ) Swap( &A[ Left ], &A[ Right ] ); 
    if ( A[ Center ] > A[ Right ] ) Swap( &A[ Center ], &A[ Right ] ); 
    /* Invariant: A[ Left ] <= A[ Center ] <= A[ Right ] */ 
    Swap( &A[ Center ], &A[ Right - 1 ] ); /* Hide pivot */
    /* only need to sort A[ Left + 1 ] … A[ Right – 2 ] */
    return A[ Right - 1 ]; /* Return pivot */
}
void Qsort(int arr[], int low, int high){
    if (high<=low)return;
    int i=low,j=high+1,key=arr[low];
    while (true){  
        while (arr[++i]<key){ /*从左向右找比key大的值*/
            if (i==high)break;
        }
        while (arr[--j]>key){ /*从右向左找比key小的值*/
            if (j==low)break;
        }
        if (i>=j) break;
        int temp = arr[i];  /*交换i,j对应的值*/
        arr[i] = arr[j];
        arr[j] = temp;
    }
    arr[low] = arr[j];  /*中枢值与j对应值交换*/
    arr[j] = key;
    Qsort(arr,low,j-1);
    Qsort(arr,j+1,high);
}
int main(){
    int a[] = {57, 68, 59, 52, 72, 28, 96, 33, 24};
    Qsort(a, 0, sizeof(a) / sizeof(a[0]) - 1);/*这里原文第三个参数要减1否则内存越界*/
    for(int i = 0; i < sizeof(a) / sizeof(a[0]); i++)
        cout << a[i] << " ";
    return 0;
}/*参考数据结构p274(清华大学出版社，严蔚敏)*/

//基数排序
# define MAX_NUM_KEY 3 //关键字个数
# define RADIX 10 //关键字的基数
# define MAXSIZE 10000
typedef struct { //静态链表的节点类型
    KeyType key[ MAX_NUM_KEY ];//关键字
    int next;
} SLCell; //静态链表的节点类型
typedef struct {  //静态链表类型
    SLCell r[ MAXSIZE ] // 静态链表空间
    int bitnum; //关键字位数
    int rednum; //记录个数
} SLList;
typedef int ArrType[ RADIX ]; // 指针数组类型



