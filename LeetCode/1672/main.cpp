#include<iostream>
#include<vector>

using namespace std;


int maximumWealth(vector<vector< int > >& accounts) {

    int num_col = accounts[0].size();
    int num_row = accounts.size();
    int ans = 0;
    for (int i = 0; i < num_row; i++)
    {
        int tmp = 0;

        for (int j = 0; j < num_col; j++)
        {
            tmp += accounts[i][j];
        }
        
        ans = max(ans, tmp);
    }
    
    return ans;
}

int main(int argc, char const *argv[])
{
    /* code */
    return 0;
}
