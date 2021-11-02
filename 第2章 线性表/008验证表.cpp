#include <bits/stdc++.h>
struct list{
    int id;
    char name[10];
};
int main(){
    int m,n,i,j;
    int repeat=0,listCount=0;
    scanf("%d",&m);
    struct list list1[m];
    for(i=0;i<m;i++)memset(list1[i].name,0,sizeof(list1[i].name));
    for(i=0;i<m;i++)scanf("%d %s",&list1[i].id,&list1[i].name);
    scanf("%d",&n);
    if(!n){ 
        printf("the LIST2 is NULL.\n");
        return 0;
    }
    struct list list2[n+1];
    for(i=0;i<n+1;i++)memset(list2[i].name,0,sizeof(list2[i].name));
    for(i=0;i<n;i++)scanf("%d %s",&list2[i].id,&list2[i].name);
    for(i=0;i<n;i++){
        repeat=0;
        for(j=0;j<m;j++){
            if(list2[i].id==list1[j].id){
                if(strcmp(list2[i].name,list1[j].name)==0){
                    repeat++;
                    break;
                }
            }
        }
        if(!repeat){
            printf("%d %s is not in LIST1.\n",list2[i].id,list2[i].name);
            listCount++;
        }
    }
    if(!listCount && n) printf("the records of LIST2 are all in the LIST1.\n");
    return 0;
}
