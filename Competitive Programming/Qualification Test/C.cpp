#include<iostream>
#include<string>
#include<stdio.h>

using namespace std;

int main(){
    string line;
    string hexChar = "0123456789abcdefABCDEF";
    while(getline(cin, line)){
        string hex = "";
        bool isHex = false;
        for(int i = 0 ; i < line.size(); i++){
            if(tolower(line[i]) == 'x' && tolower(line[i - 1] == '0')){
                isHex = true;
            }
            else if(isHex){
                if(hexChar.find(line[i]) != string::npos){//contain hex char
                    hex += line[i];
                }
                else{
                    isHex = false;
                    if(hex == "") continue;
                    cout << "0x" + hex << " " << stoul(hex, nullptr, 16) << endl;
                    hex = "";
                }
            }
                
        }
        if(hex != ""){
            cout << "0x" + hex << " " << stoul(hex, nullptr, 16) << endl;
        }
    }
}