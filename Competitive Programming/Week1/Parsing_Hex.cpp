#include<iostream>
#include<string>

using namespace std;

int main(){

    string s, hex = "01234567890abcdefABCDEF";
    while(getline(cin, s)){
        string ans="";
        bool isHex = false;
        for(int i = 0;i < s.size(); i++){
            if(tolower(s[i]) == 'x' && tolower(s[i-1]) == '0'){
                isHex = true;
            }
            else if(isHex){
                if(hex.find(s[i]) != string::npos)
                    ans += s[i];

                else{
                    isHex = false;
                    if(ans == "") continue;
                    cout << "0x" << ans << " " << stoul(ans, nullptr, 16) << endl;
                    ans = "";
                }
            }
        }
        if(ans != "")
            cout << "0x" << ans << " " << stoul(ans, nullptr, 16) << endl;
    }

}