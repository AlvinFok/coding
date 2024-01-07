#include<iostream>
#include<vector>
using namespace std;

vector<int> plusOne(vector<int>& digits) {
    bool addTen = false;
    int n = digits.size() - 1;
    
    digits[n] += 1;
    if(digits[n] >= 10){
        if(n == 0){
            digits[n] -= 10;
            digits.insert(digits.begin(),1);
            return digits;
        }
        digits[n] -= 10;
        addTen = true;

    }
    for(int i = n-1; i >= 0;i--){
        
        if(addTen){
            digits[i] += 1;
            addTen = false;
        }
        if(digits[i] >= 10){
            digits[i] -= 10;
            addTen = true;
        }
    }
    if(addTen){
        digits.insert(digits.begin(),1);
    }
    return digits;
}

void print(std::vector<int> const &input)
{
    for (int i = 0; i < input.size(); i++) {
        cout << input.at(i) << ' ';
    }
    cout<<endl;
}
int main(){
    vector<int> num{1,2,3};
    print(plusOne(num));
    vector<int> num1{4,3,2,1};
    print(plusOne(num1));
    vector<int> num2{0};
    print(plusOne(num2));
    vector<int> num3{9};
    print(plusOne(num3));
    vector<int> num4{9, 9};
    print(plusOne(num4));
    return 0;
}