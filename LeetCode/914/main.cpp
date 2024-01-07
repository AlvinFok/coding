#include<iostream>
#include<vector>
#include<map>
#include <algorithm>

using namespace std;


bool hasGroupsSizeX(vector<int>& deck) {
    map<int, int>mp;
    int res = 0;
    for (int i = 0; i < deck.size(); i++)
    {
        mp[deck[i]]++;
    }
    for(auto it:mp){
        res = __gcd(it.second, res);
    }

    return res > 1;
    
}

int main(int argc, char const *argv[])
{
    
    return 0;
}
