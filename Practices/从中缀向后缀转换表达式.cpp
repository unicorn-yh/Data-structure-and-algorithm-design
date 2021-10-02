// ！！！有些错误 ！！！

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
    return a1<b1?0:1;
}
int main(){
    int n=0;
    scanf("%d",&n);
    stack<char>op;
    stack<char>alnum;
    while(n--){
        while(!op.empty())op.pop();
        while(!alnum.empty())alnum.pop();
        char s[110];
        char c;
        scanf("%s",s);
        for(int i=0;i<strlen(s);i++){
            c=s[i];
            if(c=='#')break;
            else if((c>='a'&&c<='z')||(c>='A'&&c<='Z')||(c>='0'&&c<='9'))alnum.push(c);
            else{
                if(c=='(')op.push(c);
                else if(c==')'){
                    while(op.top()!='('){
                        alnum.push(op.top());
                        op.pop();
                    }
                    op.pop();   //舍弃栈顶的左括号
                }
                else{
                    if(op.empty()||compareOp(c,op.top()))op.push(c);  //优先级较大则直接存入op
                    else{
                        alnum.push(op.top());
                        op.pop();
                        while(!op.empty()){   //优先级较小则出栈
                            if(compareOp(op.top(),c)){
                                alnum.push(op.top());                   //逐个将运算符移入alnum
                                op.pop();
                            }
                            else break;
                        }
                        op.push(c);
                    }
                }
            }
        }
        while(!op.empty()){          //将op剩余的运算符移入alnum
            alnum.push(op.top());
            op.pop();
        }
        int k=1;
        while(!alnum.empty()){
            s[k++]=alnum.top();
            alnum.pop();
        }
        for(int i=k-1;i>0;i--) printf("%c",s[i]);   //逆序输出
        printf("\n"); 
    }
    return 0;
}