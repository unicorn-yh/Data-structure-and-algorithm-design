#include <bits/stdc++.h>
char input[100];
int a=0,b=0,temp,flag;
 
void PrintGList(){
    for(int i=a;i<=b;i++)printf("%c",input[i]);
    printf("\n");
}
void getHead(){
    printf("destroy tail\nfree list node\ngeneric list: ");
    flag=-1;
    for(int i=a;input[i]!='\0';i++){
        switch(input[i]){
            case '(': flag++;if(!flag)a=i+1;break;        //第一个原子开始
            case ')': flag--;if(!flag){b=i;goto j;}break; //第一个原子结束
            case ',': if(!flag){b=i-1;goto j;}break;
            default : break;
        }
    }
    j:PrintGList();
}
void getTail(){
    printf("free head node\nfree list node\ngeneric list: ");
    flag=-1;
    int t=0;
    for(int i=a;input[i]!='\0';i++){
        if(i==b){
            t=1;
            break;
        }
        switch(input[i]){
            case '(': flag++;break;
            case ')': flag--;break;
            case ',': if(!flag){input[i]='(';a=i;goto k;}
            default : break;
        }
    }
    k:if(t){
        printf("()\n");
        return;
    }
    PrintGList();
}
int main(){
    scanf("%s",input);
    printf("generic list: %s\n",input);
    b=strlen(input)-1;
    while(~scanf("%d",&temp)){
        switch(temp){
            case 1: getHead();break;
            case 2: getTail();break;
        }
    }
    return 0;
}