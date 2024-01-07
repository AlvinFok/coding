#include<iostream>

using namespace std;


string generateTheString(int n) {
    return "b" + string(n-1, 'a' + n % 2);
}

int main(){
    return 0;
}