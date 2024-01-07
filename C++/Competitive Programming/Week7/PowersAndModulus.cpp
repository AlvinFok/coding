#include<iostream>

using namespace std;

int main(){
    long long int a, b, m;
    cin >> a >> b;

    m = a;
    a = a * (a+1) / 2;
    a %= m;
    long long int res = 1;
    while(b > 0){
        res = res * a % m;
        a = a * a % m;
        b >>= 1;
    }
    cout << res << endl;
}