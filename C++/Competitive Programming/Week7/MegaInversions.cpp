#include<iostream>

using namespace std;

typedef long long ll;

int n;

void update(ll a[], int index, int val){
    for(int i = index; i < n; i += i & (-i)){
        a[i] += val;
    }
}

ll sum(ll a[], int index){
    ll total = 0;
    for(int i = index; i > 0; i -= i & (-i)){
        total += a[i];
    }
    return total;
}



int main(){

    cin >> n;
    ll a[n];
    ll a1[n], a2[n];
    for(int i = 0; i < n; i++){
        cin >> a[i];
        a1[i] = a2[i] = 0;
    }
    
    ll ans = 0;
    for(int i = n - 1; i >= 0; i--){
        ans += sum(a2, a[i]-1);
        ll uno = sum(a1, a[i]-1);
        update(a1, a[i], 1);
        update(a2, a[i], uno);
    }

    cout << ans << endl;
}