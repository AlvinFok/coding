#include<iostream>
#include<vector>

using namespace std;

vector<long long int> nums;

bool binarySearch(int low, int high, long long int x){
    if(high >= low){
        int mid = (low + high) / 2;
        if(nums[mid] == x)
            return true;
        else if(nums[mid] > x)
            return binarySearch(low, mid-1, x);
        else
            return binarySearch(mid+1, high, x);
    }
    
    return false;
}

int main(){
    int n, m ,x, a, c;
    cin >> n >> m >> a >> c >> x;
    nums.resize(n);
    long long xi = x;
    for(int i = 0; i < n; i++){
        xi = ( a*xi + c ) % m;
        nums[i] = xi;
    }

    int count = 0;
    for(int i:nums){
        if(binarySearch(0, n-1, i)){
            count++;
        }
    }

    cout << count << endl;

}