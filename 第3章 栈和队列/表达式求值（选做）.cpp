/*问题描述
带有变量的中缀表达式是常见的数学表达式。如果规定变量由长度不超过 8 个小写字母组成；
end为保留字，表示程序段结束；用？表示输出指定变量的值，则可以设计出比较复杂的表达式
（即一个可顺序执行语句序列）。例如，如果有如下语句段：
abc=10
def=8
c=abc+def
abc=abc+5-c*2
? c
? abc
end

则输出为：
c=18
abc=-21

注意：为了简化编程实现，运算符只有＋，－，＊，／ ，%和＾（指数运算），可以处理圆括号（），并假定输入的算术表达式正确。
要求：使用栈结构实现。
输入：表达式序列
输出：全部指定变量的值
表达式中的全部计算结果均为整数。如果在计算过程中出现除数为0的情况，则输出：Divide 0.

特殊情况说明：
在表达式中，如果操作数出现负数（例如-8），则要特别注意。例如：
10加-8表示为：10+-8。
10减-8表示为：10--8。*/

#include <bits/stdc++.h>
using namespace std; 
map<string, int>mapping; 
stack<char>op; 
stack<int>opnum; 
string input,s;
 
int PriorityOut(char c){  //栈外优先级
    switch(c){
        case '+':return 3;
        case '-':return 3;
        case '*':return 5;
        case '/':return 5;
        case '%':return 5;
        case '(':return 10;
        case '^':return 8;
    }
}
int PriorityIn(char c){     //栈内优先级
    switch(c){
        case '+':return 4;
        case '-':return 4;
        case '*':return 6;
        case '/':return 6;
        case '%':return 6;
        case '(':return 1;
        case '^':return 7;
    }
}

int calculate(int a,int b,char c) { 
    switch(c){
        case '+':return a+b;
        case '-':return a-b;
        case '*':return a*b;
        case '/':return a/b;
        case '%':return a%b;
        case '^':return (int)pow(double(a),double(b));
  } 
} 
 
int processInput(string s) { 
    int num=0; 
    for (int i=0;s[i];i++){
        if(s[i]>='0'&&s[i]<='9'){   //数字
            num=num*10+s[i]-'0';
        }
        else if(s[i]>='a'&&s[i]<='z'){   //字符串
            int k=i;
            while(s[k]>='a'&&s[k]<='z')k++;    
            string t=s.substr(i,k-i);         
            opnum.push(mapping[t]);      //将字符串以mapping的形式存入栈opnum
            i=k-1;
        }
        else if(!(s[i]>='0'&&s[i]<='9')&&!(s[i]>='a'&&s[i]<='z')){   //符号
            if(s[i]=='=')continue;
            if(s[i-1]>='0'&&s[i-1]<='9'){                            //符号之前是数字 数字进栈opnum
                opnum.push(num);
                num=0;                                              //num回归0 num只是暂时存储数字
            }
            else if(!(s[i-1]>='a'&&s[i-1]<='z')&&!(s[i-1]>='0'&&s[i-1]<='9')&&(s[i]=='+'||s[i]=='-')){   //符号 +-
                i++;
                int k=i;
                while(s[k]&&(s[k]>='0'&&s[k]<='9')){   //将符号之后的数字赋予num
                    num=num*10+s[k]-'0';
                    k++;
                }
                if(s[i-1]=='-')       //+/-之前还有一个负号 证明数字是负数
                    num=-num;
                i=k-1;
                continue;
            }
            if(op.empty()||s[i]=='('){    //"("直接进入空栈
                op.push(s[i]);
                continue;
            }
            else if(s[i]==')'){         //")"的情况 需要计算
                char c;
                while(!op.empty()&&(c=op.top())!='('){          //op栈顶符号为 +-*/%^
                    int b=opnum.top();opnum.pop();
                    int a=opnum.top();opnum.pop();
                    if(b==0&&c=='/')continue;
                    else opnum.push(calculate(a,b,c));   //将计算到的结果入栈 opnum 用于下一轮计算
                    op.pop();
                }
                op.pop();              //去除"("符号 (吧？)
            }
            else{                      //符号 +-*/%^ 
                int elemOut=PriorityOut(s[i]);        //栈外优先级
                int elemIn;      //栈内优先级
                while(!op.empty()&&(elemIn=PriorityIn(op.top()))>elemOut){   //op不为空 栈内大于栈外优先级 所以先执行栈内的
                    char c=op.top();
                    int b=opnum.top();opnum.pop();
                    int a=opnum.top();opnum.pop();
                    if(b==0&&c=='/')continue;
                    else opnum.push(calculate(a,b,c));   
                    op.pop();
                }
                op.push(s[i]);      //栈为空 或 栈外大于栈内优先级 将元素入栈 后续再进行比较
            }
        } 
    } 
    //所有循环结束之后
    if(s[s.length()-1]>='0'&&s[s.length()-1]<='9')  //字符串结尾是数字的话 入栈opnum
        opnum.push(num);                          // num之前在上个循环已经被赋予了 还没进栈
    if(!op.empty()||!opnum.empty()){             //有其中一个栈都不为空的话
        while(!op.empty()){                     //op栈不空的话 一直执行计算
            char c=op.top();
            int b=opnum.top();opnum.pop();
            int a=opnum.top();opnum.pop();
            if(b==0&&c=='/')continue;
            else opnum.push(calculate(a,b,c));
            op.pop();
        }
        return opnum.top();                  //返回opnum栈里的仅剩元素
    }
    else return num; 
} 
int main() { 
    while(getline(cin,input)){
        if(input=="end")break;
        while(!op.empty())op.pop();           //初始化两个栈
        while(!opnum.empty())opnum.pop();
        if(input[0]=='?'){
            s=input.substr(2);               //从下标2开始到结束取子字符串
            int n=mapping.find(s)->second;   //<string,int> second表示返回第二个元素：int, s为string
            cout<<s<<'='<<n<<endl;           //输出结果
        }
        else if(input[0]>='a'&&input[0]<='z'){
            int i=0;
            while(input[i]!='=')i++;
            string str=input.substr(0,i);               //取出变量
            if(mapping.count(str)==0) mapping[str]=0;   //str未出现在mapping的列表里
            string remain=input.substr(i);             //取剩余字符串 下标 i~结尾
            mapping[str]=processInput(remain);         //操作计算剩余字符串 将结果返回mapping列表中
        }
    }
  return 0; 
} 