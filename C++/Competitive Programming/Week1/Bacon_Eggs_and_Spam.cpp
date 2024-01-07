#include<iostream>
#include<string>
#include<vector>
#include<map>
#include<sstream>
#include<set>

using namespace std;
    

vector<string> token(string s){
    stringstream ss(s);
    string str;
    vector<string> out;
    while(getline(ss, str, ' ')){
        out.push_back(str);
    }
    return out;
}

int main(){
    int n = 1;
    while(n){
        cin >> n;
        map<string, set<string> >m;
        for(int i = 0; i < n; i++){
            string s;
            vector<string> tmp;
            
            getline(cin>>ws, s);
            tmp = token(s);
            for(int i = 1; i < tmp.size(); i++){
                m[tmp[i]].insert(tmp[0]);
            }
            
        }
        for(auto i:m){
            cout << i.first;
            for(auto j:i.second)
                cout << " " << j;
            cout << endl;
        }
        cout << endl;
    }
}