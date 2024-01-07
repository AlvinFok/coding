#include<iostream>
#include<stdio.h>
#include<vector>
#include<map>
using namespace std;

vector<int> twoSum(vector<int>& nums, int target) {
    map<int,int> data;
    vector<int> ans;
    for(int i = 0; i < nums.size(); i++){
        if(data.find(target - nums[i]) != data.end()){
            cout << i << " " << data[target - nums[i]]<<endl;
            ans.push_back(i);
            ans.push_back(data[target - nums[i]]);
            break;
        }
        data[nums[i]] = i;
    }
    return ans;
}

int main()
{
    vector<int> vect { 3,2,4 };
    twoSum(vect, 6);
    vector<int> vect1 {3, 3};
    twoSum(vect1,6);
    return 0;
}
