#include<iostream>
#include<string.h>

using namespace std;

int main(){
    string str;
    int ansInx = 0;
    cin >> str;
    for(int i = 0; i < str.length(); i++){
        cout << str << endl;
        if(str[i] != '<'){
            str[ansInx++] = str[i];
            
        }
        else if(ansInx > 0) ansInx--;
    }

    for(int i = 0; )

    cout << str << endl;
}