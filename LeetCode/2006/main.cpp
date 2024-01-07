#include<iostream>
#include<vector>
using namespace std;

int countKDifference(vector<int>& nums, int k) {
    int count = 0;

    for (int i = 0; i < nums.size(); i++)
    {
        for (int j = 0; j < i; j++)
        {
            count += abs(nums[i] - nums[j]) == k;
        }
        
    }
    return count;
}


int main(int argc, char const *argv[])
{
    
    return 0;
}
