#include<iostream>
#include<vector>
#include<algorithm>
#include<unordered_set>

using namespace std;



vector<vector < int > > fourSum(vector<int>& nums, int target) {
    sort(nums.begin(), nums.end());
    return kSum(nums, target, 0, 4);
}


vector<vector < int > > kSum(vector<int>& nums, int target, int start, int k){
    vector<vector<int> > res;
    if(start == nums.size()){
        return res;
    }

    long long avg = target / k;

    if(nums[start] > avg || avg > nums.back()){
        return res;
    }

    if(k == 2){
        twoSum(nums, target, start);
    }

    for(int i = start; i < nums.size(); i++){
        if( i == start || nums[i-1] != nums[i]){
            for(vector<int> subset : kSum(nums, target - nums[i], i + 1, k - 1)){
                res.push_back({nums[i]});
                res.back().insert(end(res.back()), begin(subset), end(subset));
            }
        }
        
    }

    return res;

}

vector<vector<int > > twoSum(vector<int>& nums, int target, int start){
    vector<vector<int> > res;
    unordered_set<int> s;

    for(int i = start; i < nums.size(); i++){
        if(res.empty() || res.back()[1] != nums[i]){
            if(s.count(target - nums[i])){
                res.push_back({(int)target - nums[i], nums[i]});
            }
        }
        s.insert(nums[i]);
    }
    return res;
}




int main(int argc, char const *argv[])
{
    /* code */
    return 0;
}
