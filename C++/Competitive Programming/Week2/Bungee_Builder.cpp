#include<iostream>
#include<vector>

using namespace std;

int main(){
    int N;
    cin >> N;
    vector<int> num(N);
    for(auto &i:num)
        cin >> i;

    int maxHeight, minHeight, maxJump=0;
    maxHeight = minHeight = num[0];
    for(auto i:num){
        minHeight = min(i, minHeight);
        if(i >= maxHeight){
            maxJump = max(maxJump, maxHeight - minHeight);
            maxHeight = minHeight = i;
        }
        else{
            maxJump = max(maxJump, i - minHeight);
        }
    }
    cout << maxJump << endl;
}