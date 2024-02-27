#include<iostream>
#include<vector>
#include<map>

using namespace std;



int eval(int a, int b, char op){
    switch (op)         
    {
    case '+':
        return a + b;
        break;
    
    case '-':
        return a - b;
        break;
    case '*':
        return a * b;
        break;
    case '/':
        return a / b;
        break;
    default:
        return -1;
        break;
    }
}

int main(){
    map<int, string> ans;
    map<int, char> operatorMap;
    operatorMap[0] = '*';
    operatorMap[1] = '/';
    operatorMap[2] = '+';
    operatorMap[3] = '-';

    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            for(int k = 0; k < 4; k++){
                vector<int> nums = {4, 4, 4, 4};
                vector<char> ops = {operatorMap[i], operatorMap[j], operatorMap[k]};
                // cout << ops[0]<< ops[1]<< ops[2] << endl;
                for(int l = 0; l < ops.size(); l++){
                    if(ops[l] == '*' || ops[l] == '/'){
                        nums[l] = eval(nums[l], nums[l+1], ops[l]);
                        nums.erase(nums.begin()+l+1);
                        ops.erase(ops.begin()+l);
                        l--;
                    }
                }

                for(int l = 0; l < ops.size(); l++){
                    nums[l] = eval(nums[l], nums[l+1], ops[l]);
                    nums.erase(nums.begin()+l+1);
                    ops.erase(ops.begin()+l);
                    l--;
                    
                }
                
                ans[nums[0]] = "4 " + string(1, operatorMap[i]) + " 4 " + string(1, operatorMap[j]) + " 4 " + string(1, operatorMap[k]) + " 4 = " + to_string(nums[0]);
                // cout << ans[nums[0]] << endl;
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
            cout << "no solution" << endl;
        }
    }
}