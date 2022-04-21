/*Have you ever played quoit in a playground? Quoit is a game in which flat rings are pitched at some toys, with all the toys 
encircled awarded. In the field of Cyberground, the position of each toy is fixed, and the ring is carefully designed so it can 
only encircle one toy at a time. On the other hand, to make the game look more attractive, the ring is designed to have the largest 
radius. Given a configuration of the field, you are supposed to find the radius of such a ring. Assume that all the toys are points 
on a plane. A point is encircled by the ring if the distance between the point and the center of the ring is strictly less than the 
radius of the ring. If two toys are placed at the same point, the radius of the ring is considered to be 0.

Input The input consists of several test cases. For each case, the first line contains an integer N (2 <= N <= 100,000), the total 
number of toys in the field. Then N lines follow, each contains a pair of (x, y) which are the coordinates of a toy. The input is 
terminated by N = 0.

Output For each test case, print in one line the radius of the ring required by the Cyberground manager, accurate up to 2 decimal places.*/

#include <bits/stdc++.h>
using namespace std;
const double INF = 1e20;
struct point{
	double x,y;
}a[100005],b[100005];
bool compareY(point a,point b){
    return a.y<b.y;
}
bool compareXY(point a,point b){			//按照x从小到大，x相等y从小到大排序
	return(a.x==b.x?a.y<b.y:a.x<b.x);
}

double distance(point a,point b){
	return sqrt(pow(a.x-b.x,2)+pow(a.y-b.y,2));
}
double Search (int low,int high){
    int c=0;
    if(low==high)return INF;
    if(high-low==1)return distance(a[low],a[high]);
    int mid=(low+high)/2;   
    double x=min(Search(low,mid),Search(mid+1,high));  //min(左半区间最小值, 右半区间最小值)
    for(int i=low;i<=high;i++){
        if(fabs(a[i].x-a[mid].x)<=x)b[c++]=a[i];
    }
    sort(b,b+c,compareY);
    for(int i=0;i<c;i++){
        for(int j=i+1;j<c;j++){
            if(b[j].y-b[i].y>=x)break;  //乐观剪枝，y的差值已经超过d就没有计算意义
            x=min(x,distance(b[i],b[j]));
        }
    }
    return x;
}
int main(){
	int n;
	while(~scanf("%d",&n) && n){
		for(int i = 0;i < n;i++){
			scanf("%lf%lf",&a[i].x,&a[i].y);
		}
		sort(a,a+n,compareXY);
		double ans = Search(0,n-1)/2;
		printf("%.2f\n",ans);
	}
	return 0;
} 

/*4
0 3
3 2
4 0
7 1
0

1.12*/
