#include<iostream>
#include<vector>
#include<map>

using namespace std;



vector<int> arrayRankTransform(vector<int>& arr) {
    int rank = 1;
    map<int, vector<int> >mp;
    for (int i = 0; i < arr.size(); i++)
    {
        mp[arr[i]].push_back(i);
    }

    for (auto it=mp.begin();it!=mp.end();it++)
    {
        for (int j = 0; j < it->second.size(); j++)
        {
            arr[it->second[j]] = rank;
        }
        
        rank++;
    }
    
    return arr;
    
}


int main(int argc, const char** argv) {
    return 0;
}