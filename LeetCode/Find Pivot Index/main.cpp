#include<iostream>
#include<vector>

using namespace std;

int pivotIndex(vector<int>& nums) {
    int leftSum = 0, rightSum = 0, sum = 0, ans = -1;
    for(int i = 0;i<nums.size();i++){
        sum += nums[i];
    }
    if(sum - nums[0] == 0)return 0;
    for(int i = 1; i < nums.size(); i++){
        
        leftSum += nums[i-1];
        rightSum = sum - leftSum - nums[i];
        if(leftSum == rightSum){
            ans = i;
            break;
        }
    }
    cout<<ans<<endl;
    return ans;
}

int main(){
    vector<int> num{1,7,3,6,5,6};
    pivotIndex(num);
    vector<int> num1{1,2,3};
    pivotIndex(num1);
    vector<int> num2{2,1,-1};
    pivotIndex(num2);
}