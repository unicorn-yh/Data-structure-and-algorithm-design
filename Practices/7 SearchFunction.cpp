/**********
 * NOTES
 * 顺序表：顺序查找
 * 有序表：折半查找
 * 索引顺序表：分块查找
 * 平均查找长度(Average Search Length)：ΣPiCi=Σ(n-i+1)/n=(n+1)/2
 * Ci=n-i+1, Pi=1/n, 算法的ASL= 成功时ASL + 不成功时的ASL
 * Ci：查找第 i 个记录所需的比较次数
 * Pi：查找第 i 个记录的概率
 * 查找不成功的比较次数均为n+1, 假设查找成功和不成功的可能性相同，对每个元素的查找概率也相同则
 * ASL=Σ(n-i+1)/2n+(n+1)/2=3(n+1)/4
 * 
 * 折半：排序->low mid high确定区间->找到/找不到值
 * 具有n个节点的判定树/满二叉树的深度为 logn+1
 * ASL=log2(n+1)-1, n>50, 存储结构：顺序, 按关键字有序
 * 
 * 索引顺序表 分块
 * 要额外建立一个索引表，在数据块内顺序查找
 * 
 *          顺序        折半        分块
 * ASL      最大        最小        之间
 * 表     有序或无序     有序      分块有序
 * 存储  顺序线性链表    顺序     顺序线性链表
 * 
 * 插入
 * 
 * 删除
 * 分3种情况：
 * 1. p为叶子结点，只需修改 p 双亲 f 的指针：f->lchild=NULL/f->rchild=NULL
 * 2. p只有左子树或右子树
 * 3. p左、右子树均非空
 * 
 * 


*/

#include <bits/stdc++.h>
typedef float KeyType;
typedef int KeyType;
typedef char* KeyType; //字符串

//int
#define EQ(a,b) (a==b)  //equal 
#define LT(a,b) (a<b)   //lower than
#define LQ(a,b) (a<=b)  //lower and equal than
//string
#define EQ(a,b) (!strcmp(a,b)) 
#define LT(a,b) (strcmpa(a,b)<0)   
#define LQ(a,b) (strcmp(a,b)<=0)

typedef struct{
    KeyType key;   //关键字域
}ElemType;

//顺序表
typedef struct{   
    ElemType *elem;   //0号单元留空
    int length;
}SSTable; SSTable ST; ST.elem;
int Search_Seq ( SSTable ST, KeyType key ){ 
    //在顺序表ST中顺序查找其关键字等于key的数据元素。若找到，则函数值为该元素在表中的位置，否则为0。
    int i=0;
    ST.elem[0].key=key;   // “哨兵”
    for ( i=ST.length; !EQ(key,ST.elem[i].Key); --i)；
    return i;       // 若表中不存在待查元素,  i=0
}

//有序表 折半
int Search_Bin ( SSTable ST, KeyType key ){   //0号单元留空
    //在有序表ST中折半查找法查找其关键字等于key的数据元素。若找到，则返回该元素在表中的位置，否则为0。
    low=1; high=ST.length;
    while ( low <= high ) {  
        mid = (low+high)/2;
        if EQ ( key, ST.elem[mid].key )  return mid;      
        else
            if  LT ( key, ST.elem[mid].key ) high=mid-1; 
            else  low = mid+1;     
    }
    return 0;    //表中不存在待查元素 low>high 查找不成功
}

//二叉排序树的存储
typedef struct BiTNode {
    TElemType data;
    struct BiTNode *lchild, *rchild;
} BiTNode,*BTree; 
typedef struct  {
   KeyType key;
   …
} TElemType;
//二叉排序树的查找——非递归算法
BiTree SearchBST ( BiTree T, KeyType key ){ //根指针T
    //二叉排序树用二叉链表存储。在根指针T所指二叉排序树中查找关键字等于key的记录，若查找成功，则返回指向该记录结点的指针，否则 返回空指针
    BiTree p=T; 
    while (p&&!EQ(key,p->data.key))  //指针!=null && 指针!=key
    {  if(LT(key,T->data.key)) p=p->lchild;  //小于去左孩子
       else p=p->rchild;   //大于右孩子
    }
    return(p);
}
//二叉排序树的查找（算法9.5a）——递归算法
BiTree  SearchBST( BiTree T, KeyType key ){ 
    //将二叉链表作为二叉排序树的存储结构
    if (!T||EQ(key,T->data.key)) return(T);
    else
        if(LT(key,T->data.key)) return (SearchBST(T->lchild,key));
        else return (SearchBST(T->rchild,key)); 
}
//插入
Status InsertBST ( BiTree  &T, TElemType e ){
    BiTree p;
    if (!SearchBST(T,e.key,NULL,p)){  
        //查找不成功。p指向访问路径上最后一个结点
        s = (BiTree) malloc( sizeof(BiTNode) );
        s->data=e; s->lchild=s->rchild=NULL;
        if (!p) T=s;        // T为空，被插结点为根结点
        else if ( LT(e.key, p->data.key) )  p->lchild = s;
	    else   p->rchild = s;
        return TRUE;       // 插入成功
    } 
    else return FALSE; // 树中已有e，不需要再插入
}
Status SearchBST ( BiTree T, KeyType key, BiTree f, BiTree &p){ 
    // 在T中查找关键字key，若成功，则p指向该结点，返回TRUE；否则p指向查找路径的最末结点，返回FALSE。f 指向 T 的双亲，初始调用为NULL
    if ( !T )  { p=f; return FALSE; }	// 查找失败
    else if(EQ(key,T->data.key)){ 
        p=T; return TRUE;		// 查找成功
    }
    else if(LT(key,T->data.key)) return SearchBST(T->lchild,key,T,p); // 继续查找
    else return SearchBST(T->rchild,key,T,p); 
} 

//删除
int DeleteBST(BiTreep &rt,int key) //寻找删除节点
{    //若二叉排序树T中存在关键字等于key的数据元素时，则删除该数据元素节点，并返回TRUE，否则返回FALSE
    if(!rt) return FALSE;     //不存在关键字等于key的数据元素
    else {
         if(EQ(key,rt->data)) return Delete(rt); //删除关键字等于key的数据元素
         else if( LT(key,rt->data) )  return DeleteBST(rt->left,key);
         else return DeleteBST(rt->right,key);
    }
}
void  Delete ( BiTree &p ){  //删除p节点的元素
    BiTree p,s;
    if (!p->rchild )    // 右子树为空，则只需重接左子树，1，2.3，2.4
        { q = p; p = p->lchild; free(q);}
    else if ( !p->lchild )  // 左子为空，则只重接右子，2.1，2.2
        { q = p; p = p->rchild;   free(q); }
    else {    // 左右子树均不空
        q = p; s = p->lchild;  //q=根，s=左子树  定位左子树                 
        while ( s->rchild )   // 找p左子树的最右结点（大于左子树p，小于q的右子树）
            { q = s; s =s->rchild; }
        p->data = s->data;  // s覆盖原有的p
        if ( q!=p ) q->rchild = s->lchild;    //重接整个右子树
        else q->lchild = s->lchild;    //重接整个左子树
        free(s);
    }
} //Delete  算法9.8

