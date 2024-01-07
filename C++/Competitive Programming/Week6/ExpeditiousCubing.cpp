#include<iostream>
#include<algorithm>
#include<cstdio>

using namespace std;

int main(){
    int a[4], x, y;
    for(int i = 0; i < 4; i++)
    {
        scanf("%d.%d", &x, &y);
        a[i] = x*100+y;
    }
    int n;
     scanf("%d.%d", &x, &y);

    n = x*100+y;

    sort(a , a+4);

    if( (a[0] + a[1] + a[2]) > n * 3)
        cout << "impossible" << endl;
    else if((a[1]+a[2]+a[3]) <= n*3)
        cout << "infinite" << endl;
    else{
        n = (n * 3 - a[1] - a[2]);
        printf("%d.%02d\n", n/100, n%100);
    }
        
}