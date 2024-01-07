#include<iostream>
#include<list>
#include<string>

using namespace std;


void solve(){
    string s;
    getline(cin>>ws, s);
    list<char> out;
    list<char>::iterator iter = out.begin();
    for(char c:s){
        switch (c)
        {
        case '<':
            if(iter != out.begin())
                iter = out.erase(--iter);
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

    for(char c:out)
        cout << c;
    cout<<endl;
}


int main(){

    int n ;
    cin >> n;
    while(n--){
        solve();
    }
}