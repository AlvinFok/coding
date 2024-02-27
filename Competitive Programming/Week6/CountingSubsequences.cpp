#include<iostream>
#include<map>

using namespace std;

typedef long long ll;


void solve(int x){
    int nums[x+1];
    for(int i = 1; i <= x;i++)
        cin >> nums[i];

    nums[0] = 0;
    for(int i = 1; i <= x;i++){
        nums[i] += nums[i-1];
    }

    map<ll, int>m;
    m[0] = 1;
    int ans = 0;
    for(int i = 1; i <= x; i++){
        ans += m[nums[i]-47];
        m[nums[i]]++;
    }
    cout << ans << endl;
    
}


int main(){
    ll n;
    cin >> n;
    while(n--){
        int x;
        cin >> x;
        solve(x);
        
    }
}