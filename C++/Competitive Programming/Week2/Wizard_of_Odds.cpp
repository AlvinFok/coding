#include<iostream>
#include<cmath>

using namespace std;

int main(){
    unsigned long long int N, K;
    cin >> N >> K;
    if(pow(2, K) >= N)
        cout << "Your wish is granted!" << endl;
    else
        cout << "You will become a flying monkey!" << endl;
}