/*前缀码：任何一个字符的编码都不是同一字符集中另一个字符的编码的前缀。
请编写一个程序，判断输入的n个由1和0组成的编码是否为前缀码。如果这n个编码是前缀码，则输出"YES”；否则输出第一个与前面编码发生矛盾的编码。

输入：
第1行为n（表示下面有n行编码）
第2～n+1行为n个由0或1组成的编码

输出：判断结果

例如，如果输入：
5,00,01,10,110,111
每一个字符均不是其他字符编码的前缀，所以，输出：YES
再如，如果输入：
5,00,01,10,110,11
编码11与前面的编码110的前缀，所以，输出：11
*/

#include<bits/stdc++.h>
typedef struct binode{
    int data;
    struct binode *lchild,*rchild;
}binode,*bitree;

int main(){
    int n,flag=0,len=0;
    char s[100000];
    scanf("%d",&n);
    bitree tree,temp;
    tree=(bitree)malloc(sizeof(binode));
    tree->data=0;            //初始化树
    tree->lchild=tree->rchild=NULL;
    while(n--){
        temp=tree;              //每次循环都会定义
        memset(s,0,sizeof(s));  //初始化字符串
        scanf("%s",s);
        len=strlen(s);
        for(int i=0;i<len;i++){
            if(s[i]=='0'){
                if(temp->lchild==NULL){
                    temp->lchild=(bitree)malloc(sizeof(binode));
                    temp=temp->lchild;
                    temp->lchild=temp->rchild=NULL;
                    temp->data=(i==len-1)?1:0;
                }
                else{
                    if(i==len-1||temp->lchild->data==1){ //此字符串被以出现的字符包含 || 此字符串含有已出现字符
                        flag=1;
                        goto k;
                    }
                    else temp=temp->lchild;
                }
            } 
            else {
                if(temp->rchild==NULL){
                    temp->rchild=(bitree)malloc(sizeof(binode));
                    temp=temp->rchild;
                    temp->lchild=temp->rchild=NULL;
                    temp->data=(i==len-1)?1:0;
                }
                else{
                    if(i==len-1||temp->rchild->data==1){ //此字符串被以出现的字符包含 || 此字符串含有已出现字符
                        flag=1;
                        goto k;
                    }
                    else temp=temp->rchild;
                }
            }
        }
    }
    k:(flag)?printf("%s\n",s):printf("YES\n");
    return 0;
}