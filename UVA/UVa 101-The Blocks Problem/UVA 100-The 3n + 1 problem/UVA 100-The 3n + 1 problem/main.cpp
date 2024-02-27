//
//  main.cpp
//  UVA 100-The 3n + 1 problem
//
//  Created by Alvin on 2019/9/19.
//  Copyright © 2019 Alvin. All rights reserved.
//

#include <iostream>
using namespace std;

int main(int argc, const char * argv[]) {
    // insert code here...
    int num1, num2;
    while(cin>>num1 >>num2){
        int max_length = 0, length = 0;
        cout<<num1 << " " << num2 << " ";
        if(num1 > num2){
            int tmp = num1;
            num1 = num2;
            num2 = tmp;
        }
        for(int i = num1; i <= num2; i++){
            length = 1;
            int n = i;
            while(n != 1){
                if(n%2 == 0){
                    n /= 2;
                }
                else{
                    n = 3*n + 1;
                }
                length++;
                
            }
            if(length > max_length)
                max_length = length;
        }
        cout<<max_length<<endl;
    }
    return 0;
}
