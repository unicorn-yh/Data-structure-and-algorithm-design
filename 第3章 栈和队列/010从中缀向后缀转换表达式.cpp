/*问题描述
中缀表达式就是我们通常所书写的数学表达式，后缀表达式也称为逆波兰表达式，在编译程序对我们书写的程序中的表达式进行语法检查时，往往就可以通过逆波兰表达式进行。我们所要设计并实现的程序就是将中缀表示的算术表达式转换成后缀表示，例如，将中缀表达式
(A 一 (B*C 十 D)*E) ／ (F 十 G )
转换为后缀表示为：ABC*D十E*--FG十／

注意：为了简化编程实现，假定变量名均为单个字母，运算符只有＋，－，＊，／ 和＾（指数运算，要注意运算符的结合性），可以处理圆括号 (），并假定输入的算术表达式正确。
要求：使用栈数据结构实现 ，输入的中缀表达式以＃号结束

输入
整数N。表示下面有N个中缀表达式
N个由单个字母和运算符构成的表达式

输出
N个后缀表达式。*/

#include <bits/stdc++.h>
using namespace std;
int compareOp(char a,char b){
    int a1=0,b1=0;
    switch(a){
        case '(':a1=1;break;
        case '+':a1=3;break;
        case '-':a1=3;break;
        case '*':a1=5;break;
        case '/':a1=5;break;
        case '^':a1=7;break;
        case ')':a1=9;break;
    }
    switch(b){
        case '(':b1=1;break;
        case '+':b1=3;break;
        case '-':b1=3;break;
        case '*':b1=5;break;
        case '/':b1=5;break;
        case '^':b1=7;break;
        case ')':b1=9;break;
    }
    if(b1==9||(a1==7&&a==b)||(a1==5&&b1==3)||(a1==7&&b1!=7))return 1;
    else if(a==b||(a1==3&&b1==5)||(b1==7&&a1!=7)||(a1==3&&b1==3)||(a1==5&&b1==5)) return 0;
}
int main(){
    int n=0;
    scanf("%d",&n);
    char op[1010],exp[1010];
    while(n--){
        memset(op,0,sizeof(op));
        memset(exp,0,sizeof(exp));
        op[0]='1';
        int base=1,top=1;
        scanf("%s",exp);
        for(int i=0;i<strlen(exp)-1;i++){
            if(exp[i]=='#')break;
            else if((exp[i]>='a'&&exp[i]<='z')||(exp[i]>='A'&&exp[i]<='Z'))printf("%c",exp[i]);
            else{
                if(exp[i]=='(') op[top++]=exp[i]; //左括号 直接进op
                else if(exp[i]==')'){
                    if(exp[i-1]=='(') top--;           
                    while(op[top-1]!='('){
                        printf("%c",op[top-1]);  //在遇到左括号之前 输出全部op的符号
                        top--;
                    }
                    top--;   //舍弃op的左括号
                }
                else{
                    if(compareOp(exp[i],op[top-1]))op[top++]=exp[i];  //优先级较大则直接存入op
                    else{
                        while(!compareOp(exp[i],op[top-1])){   //优先级较小则
                            printf("%c",op[top-1]);            //直接输出
                            top--;
                        }
                        op[top++]=exp[i];
                    }
                }
            }
        }
        while(top-1>0){   //逆序输出
            printf("%c",op[top-1]);
            top--;
        }   
        printf("\n"); 
    }
    return 0;
}