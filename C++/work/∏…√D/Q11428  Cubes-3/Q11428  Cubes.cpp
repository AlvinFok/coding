#include<iostream>
using namespace std;
int main(){
    int x[10001]={} , y[10001]={} , ans[10001]={};
    for(int i = 2; i <=60 ;i++){
        for(int j = i-1 ; j>0 ;j--){
            int tmp = i*i*i - j*j*j;
            if(tmp <= 10000 && ans[tmp]==0){
                ans[tmp]=1;
                x[tmp] = i;
                y[tmp] = j;
            }
        }
    }

    int n;
    while(cin>>n && n){
        if(ans[n])
            cout<<x[n] <<" " <<y[n]<<endl;
        else
            cout<<"No solution"<<endl;
    }
}
