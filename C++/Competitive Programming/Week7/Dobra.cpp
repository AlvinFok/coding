#include<iostream>
#include<vector>

using namespace std;
typedef long long ll;

vector<int> option;
ll ans = 0;

bool isValid(string str){
    bool hasL = false;
    int vowels = 0, consonants = 0;
    for(char c : str){
        if(c == 'L')
            hasL = true;

        if(c == 'A' || c == 'E' || c == 'I' || c == 'O' || c== 'U'){
            vowels++;
            consonants = 0;
        }
        else{
            consonants++;
            vowels = 0;
        }

        if(vowels >=3 || consonants >= 3)
            return false;
        
    }
    return hasL;
}

void solve(string s, int i){
    if(i == s.size()){
        if(isValid(s)){
            ll count = 1;
            for(int i : option)
                count *= i;
            ans += count;
            
        }
        return;
    }

    if(s[i] != '_')
        solve(s, i + 1);
    else{
        s[i] = 'L';
        option[i] = 1;
        solve(s, i+1);

        s[i] = 'B';
        option[i] = 20;
        solve(s, i+1);

        s[i] = 'A';
        option[i] = 5;
        solve(s, i+1);

        s[i] = '_';
        option[i] = 1;
    }

}


int main(){
    string str;
    cin >> str;
    option.resize(str.size(), 1);
    solve(str, 0);
    cout << ans << endl;
}