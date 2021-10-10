/*背景：
我们的教材中已经介绍了表达式求值的算法，现在我们将该算法的功能进行扩展，
要求可以处理的运算符包括：+、-、*、/、%（整数取余）、^（乘方）、（、）。

要求：
采用算符优先算法，计算的中间结果只保留整数。

输入：
第一行为整数N。表示下面有N个表达式
从第二行起的后面N行为N个由整数构成的表达式

输出：
共N行，每行为相应表达式的计算结果。
如果判断出表达式有错误，则输出：error.
如果在计算过程中出现除数为0的情况，则输出：Divide 0.
特殊情况说明：
在表达式中，如果操作数出现负数（例如-8），则要特别注意。例如：
10加-8表示为：10+-8。
10减-8表示为：10--8。*/

#include <bits/stdc++.h>
int ischar(char c){
	if(c=='+'||c=='-'||c=='*'||c=='/'||c=='^'||c=='%')return 1;
	else return 0;
}
char priority(char a,char b){
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
    if((a1==7&&a==b)||(a1==3&&b1==5)||(a1!=7&&b1==7)||(a=='\0'&&ischar(b))||(a=='('&&ischar(b)))
		return '<';    //a 优先级小于 b，先执行b
    else if((a1==5&&b1==3)||(b1!=7&&a1==7)||(a1==3&&b1==3)||(a1==5&&b1==5)) 
		return '>';    //a 优先级大于等于 b，先执行a
}
int calculation(int a,int b,char c){    //根据符号 c 进行运算
	switch(c){
		case '+': return a+b;
		case '-': return a-b;
		case '*': return a*b;
		case '/': if(b)return a/b; else{printf("Divide 0.\n");return 0;}
		case '%': return a%b;
		case '^': if(b>=0)return pow(a,b); else{printf("error.\n");return 0;}
		//default: printf("error.\n");operationflag=1;return 0;
	}
}
int isnum(char c){
	if(c>='0'&&c<='9')return 1;
	else return 0;
}

int main(){
	char op[100],input[1010];
	int num[100];
	int n,flag,opflag,numflag,negativeflag=0;
	scanf("%d",&n);
	while(n--){
		memset(op,0,sizeof(op));
		memset(num,0,sizeof(num));
		memset(input,0,sizeof(input));
		op[0]='\0';
		flag=0;
		opflag=1;
		numflag=0;
		scanf("%s",input);
		for(int i=0;i<strlen(input);i++){
			negativeflag=0;
			if(i==0&&isnum(input[i+1])&&input[0]=='-'){  //负数
				negativeflag=1;
				i++;
				goto A;                       //去A换成负数
			}
			if(i==0&&isnum(input[i+1])&&input[0]=='+'){  //正数
				i++;
				goto A;
			}
			if(input[i]=='('){          //"("
				if(input[i-1]==')') goto error;   // () 的情况
				if(isnum(input[i-1]))goto error;
				if(ischar(input[i+1])&&input[i+1]!='+'&&input[i+1]!='-')goto error;  //符号是 */%^
				op[opflag++]=input[i];  //符号'('入栈 op                
				if((input[i+1]=='+'||input[i+1]=='-')&&isnum(input[i+2]))i++;   //括号后的数字前缀带有正负号，此正负号不是运算符
			}  
			else{         //数字
				if(isnum(input[i])){            
					if(input[i-1]=='-'&&(ischar(input[i-2])||input[i-2]=='('))negativeflag=1;  //判断正负号
					A: while(1){      
						if(isnum(input[i])){
							num[numflag]=num[numflag]*10+input[i]-'0';
							i++;
						}
						else break;
					}
					if(negativeflag)num[numflag]*=(-1); 
					numflag++;
					i--;  
				}
				else{     // 运算符号 AND ")"
					if(ischar(input[i])){     //运算符号
						if(priority(op[opflag-1],input[i])=='<'){  //栈内符号优先级小于栈外，栈外符号入栈 op
							op[opflag++]=input[i];
							if((input[i+1]=='+'||input[i+1]=='-')&&isnum(input[i+2]))i++;   //判断符号后的数字是否带有正负号
						}
						else{  //栈内符号优先级大于栈外，则栈内符号进行运算
							while(1){
								if(priority(op[opflag-1],input[i])=='>'){     
									if(num[numflag-1]==0&&op[opflag-1]=='/')goto divide0;
									if(num[numflag-1]<0&&op[opflag-1]=='^')goto error;
									num[numflag-2]=calculation(num[numflag-2],num[numflag-1],op[opflag-1]);
									num[numflag-1]=0;
									numflag--;
									opflag--;
								}
								else break;    //只要栈内符号优先级大于栈外，就一直运行
							}
							op[opflag++]=input[i];  //栈内符号运算完毕，栈外符号入栈 op
							if((input[i+1]=='+'||input[i+1]=='-')&&isnum(input[i+2]))i++;   //判断符号后的数字是否带有正负号
						}
					}
					else{     //")"
						if(input[i]==')'){      
							if(isnum(input[i+1]))goto error;
							if(input[i+1]=='(')goto error;
							while(1){
								if(op[opflag-1]!='('){      //进行括号里面的表达式
									if(num[numflag-1]==0&&op[opflag-1]=='/')goto divide0;
									if(num[numflag-1]<0&&op[opflag-1]=='^')goto error;
									if(op[opflag-1]=='\0')goto error;
									num[numflag-2]=calculation(num[numflag-2],num[numflag-1],op[opflag-1]);
									num[numflag-1]=0;
									numflag--;
									opflag--;
								}
								else{
									opflag--;     //消去 "("
									break;        //运算完后跳出循环
								}
							}
						}
					}
				}
			}
		}
		while(1){
			if(op[opflag-1]!='\0'&&op[opflag-1]!='('){
				if(num[numflag-1]==0&&op[opflag-1]=='/')goto divide0;
				if(num[numflag-1]<0&&op[opflag-1]=='^')goto error;
				num[numflag-2]=calculation(num[numflag-2],num[numflag-1],op[opflag-1]);
				num[numflag-1]=0;
				numflag--;
				opflag--;
			}
			else{
				if(op[opflag-1]=='(')goto error;
				else break;
			}
		}
		printf("%d\n",num[0]);goto B;
		error:printf("error.\n");goto B;
    	divide0:printf("Divide 0.\n");goto B;
		B:;    //继续 开始新循环
	}
	return 0;
}