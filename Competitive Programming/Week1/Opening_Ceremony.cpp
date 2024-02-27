#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int main(){
    int n;
    cin >> n;
    vector<int> nums(n);
    for(auto& i:nums){
        cin >> i;
    }

    sort(nums.begin(), nums.end());
    int ans = n;

    for(int i = 0; i < nums.size(); i++){
        ans = std::min(nums[i] + (n - i - 1), ans);
    }

    cout << ans << endl;
}