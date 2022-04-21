/*阿邱最近开了家餐厅。阿邱想了解某一时段至少有多少不同人出入餐厅。阿邱就雇佣了一个人，呆在餐厅门口，有人进入餐厅，他就在纸上记下+，有人出餐厅，他就在纸上记下-。
假设同一时间没有两个人同时进入或出餐厅；也假设最初的时候餐厅中有足够多的人。问，这段时间里，至少有多少人出入餐厅。（不同人出入的顺序是随意的，一个人可以反复出入。）

Input
第一行是一个正整数m，表示有m组测试数据。（m<=100）
每组测试数据是一个由字符'+'和'-'组成的字符串。字符一个接一个，之间没有其他的分隔符，字符串的长度<=200。

Output
对于每一组测试数据输出一行，最少数量的人。*/

#include<bits/stdc++.h>
int main(){
    int add,subtract,number,n;
    char c;
    scanf("%d",&n);
    getchar();
    for(int i=0;i<n;i++){
        add=subtract=number=0;
        while((c=getchar())!='\n'){
            if(c=='+'){
                ++number;
                if(number>add)add=number;
            }
            else{
                --number;
                if(number<subtract)subtract=number;
            }
        }
        printf("%d\n",add-subtract);
    }
}

/*
2
+-+-+
---

1
3
*/