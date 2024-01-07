#include<iostream>
#include<map>

using namespace std;


bool canInput(int n){
    map<string, string> key;
    key["1"] = "1234567890";
    key["2"] = "2356890";
    key["3"] = "369";
    key["4"] = "4567890";
    key["5"] = "56890";
    key["6"] = "69";
    key["7"] = "7890";
    key["8"] = "890";
    key["9"] = "9";
    key["0"] = "0";

    string num = to_string(n);
    bool good = true;
    for(int i = 0; i < num.size() - 1; i++){
        good = good & key[string(1, num[i])].find(num[i + 1]) != string::npos;
    }
    return good;
}

int main(){
    int t;
    cin >> t;
    while(t--){

        int n;
        cin >> n;
        int error = 0;
        while(!canInput(n+error) && !canInput(n-error))
            error++;
        
        if(canInput(n+error))
            cout << n+error << endl;
        else
            cout << n-error << endl;

    }
}