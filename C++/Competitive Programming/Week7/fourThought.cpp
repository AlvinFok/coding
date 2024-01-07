#include<iostream>
#include<map>
#include<vector>

using namespace std;

int eval(int a, int b, char op){
    switch (op)
    {
    case '+':
        return a + b;
        
    case '-':
        return a - b;
    case '*':
        return a * b;
    case '/':
        return a / b;
    default:
        break;
    }
}

int main(){
    char ops[4] = {'*', '/', '+', '-'};
    map<int, string> ans;

    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            for(int k = 0; k < 4; k++){
                vector<int> nums = {4, 4, 4, 4};
                vector<char> op = {ops[i], ops[j], ops[k]};


                for(int l = 0; l < op.size(); l++){
                    if(op[l] == '*' || op[l] == '/'){
                        nums[l] = eval(nums[l], nums[l+1], op[l]);
                        nums.erase(nums.begin()+l+1);
                        op.erase(op.begin()+l);
                        l--;
                    }
                }
                for(int l = 0; l < op.size(); l++){
                    nums[l] = eval(nums[l], nums[l+1], op[l]);
                    nums.erase(nums.begin()+l+1);
                    op.erase(op.begin()+l);
                    l--;
                }
                ans[nums[0]] = "4 " + string(1, ops[i]) + " 4 " + string(1, ops[j]) + " 4 " + string(1, ops[k]) + " 4 = " + to_string(nums[0]);
            }
        }
    }


    int m;
    cin >> m;
    while(m--){
        int n;
        cin >> n;
        if(ans.find(n) != ans.end()){
            cout << ans[n] << endl;
        }
        else{
            cout << "No Solution" << endl;
        }
    }
}