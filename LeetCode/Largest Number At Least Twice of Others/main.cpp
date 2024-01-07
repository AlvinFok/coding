#include<iostream>
#include<vector>

using namespace std;

int dominantIndex(vector<int>& nums) {

    if(nums.size() == 1)return 0;

    int maxIndex = 0, maxIndex2 = 1;
    for(int i = 1; i < nums.size(); i++) {
        if(nums[i] > nums[maxIndex]){
            maxIndex2 = maxIndex;
            maxIndex = i;
            
        }
        else if(nums[i] > nums[maxIndex2]){
            maxIndex2 = i;
        }
    }
    if(nums[maxIndex] >= 2 * nums[maxIndex2] || maxIndex == maxIndex2)
        return maxIndex;
    else
        return -1;
}

int main(){
    vector<int> num{3,6,1,0};
    cout<<dominantIndex(num)<<endl;
    vector<int> num1{1,2,3,4};
    cout<<dominantIndex(num1)<<endl;
    vector<int> num2{1};
    cout<<dominantIndex(num2)<<endl;
    vector<int> num3{1,0};
    cout<<dominantIndex(num3)<<endl;
    vector<int> num4{3,0,0,2};
    cout<<dominantIndex(num4)<<endl;
    return 0;
}