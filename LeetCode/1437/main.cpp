
#include<iostream>
#include<vector>

using namespace std;



bool kLengthApart(vector<int>& nums, int k) {
    int prevOne = -k-1;
    for (int i = 0; i < nums.size(); i++)
    {
        if(nums[i]){
            if(i - prevOne <= k ) return false;
            prevOne = i;
        }
    }
    return true;
}


int main(int argc, char const *argv[])
{
    /* code */
    return 0;
}
