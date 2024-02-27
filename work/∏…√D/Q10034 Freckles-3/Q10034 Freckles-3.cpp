#include<cstdio>
#include<algorithm>
#include<cmath>
using namespace std;
struct Point{
    double x ,y;
};
struct Edge{
    int p_1,p_2;
    double weight;
};
int main(){
    int times,n;
    while(times--){
        scanf("%d",&n);
        Point p[n];
        Edge e[n*n];
        for(int i =0;i<n;i++)
            scanf("%lf %lf",&p[i].x,&p[i].y);
    }
    return 0;
}
