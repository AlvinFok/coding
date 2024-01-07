#include<iostream>
#include<string>
#include<list>

using namespace std;


void solve(){
    string str;
    list<char> out;
    int ansIdx = 0 , rearIdx = 0;
    bool insert = false;
    getline(cin >> ws, str);

    list<char>::iterator iter = out.begin();
    for(char c : str){
        switch (c)  
        {
        case '<':
            if(iter != out.begin()){
                iter = out.erase(--iter);
            }
            break;
        
        case '[':
            iter = out.begin();
            break;
        case ']':
            iter = out.end();
            break;
        
        default:
            iter = out.insert(iter, c);
            iter++;
            break;
        }
    }

    for(char c : out){
        cout << c;
    }
    cout << endl;
}

int main(){
    int n;
    cin >> n;
    while(n--){
        solve();
    }
}