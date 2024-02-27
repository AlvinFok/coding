#include<iostream>
#include<string>

using namespace std;

int main(){

    string s;
    getline(cin>>ws, s);
    int idx = 0;
    for(int i = 0; i < s.size(); i++){
        if(s[i] == '<')
            idx--;
        else
            s[idx++] = s[i];
    }

    for(int i = 0; i < idx; i++)
        cout << s[i];
    
    cout << endl;
}