#include<iostream>
using namespace std;
int buffer[10];
int findNext(int n,int k){
    if(k==0)return 0;
    long long int squareK = (long long int)k*k;
    int ans = 0,len=0;
    while(squareK>0){
        buffer[len++]=squareK%10;
        squareK/=10;
    }
    if(n>len)n=len;
    for(int i =0; i < n; i++)
        ans = ans*10+buffer[--len];
    return ans;
}
int main(){
    int times;
    cin>>times;
    while(times--){
        int n ,k;
        cin>>n>>k;
        int ans = k , k1 = k , k2 = k;
        do{
            k1 = findNext(n,k1);
            k2 = findNext(n,k2); ans = max(ans,k2);
            k2 = findNext(n,k2); ans = max(ans,k2);
        }while(k1!=k2);
        cout<<ans<<endl;
    }
}
