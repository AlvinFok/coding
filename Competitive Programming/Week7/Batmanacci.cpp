#include<iostream>

using namespace std;
typedef long long ll;

int main(){
    ll n, k;
    cin >> n >> k;
    unsigned long long fib[100100];
    fib[1] = 1;
    fib[2] = 1;
    for(int i = 3; i <= n; i++){
        fib[i] = fib[i-1] + fib[i-2];
        if(fib[i] > 100000000000000000)
            fib[i] = 100000000000000001;
    }

    while(n > 2){
        if(k > fib[n-2]){
            k -= fib[n-2];
            n -=1;
        }
        else
            n-=2;
    }

    if(n == 1)
        cout << "N" << endl;
    if(n == 2)
        cout << "A" << endl;

}