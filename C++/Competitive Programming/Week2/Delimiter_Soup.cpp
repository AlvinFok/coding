#include<iostream>
#include<string>
#include<stack>

using namespace std;

int main(){
    int N;
    cin >> N;
    string s;
    getline(cin>>ws, s);
    stack<char> st;
    for(int i = 0; i < s.size(); i++){
        if(s[i] == '(' || s[i] == '[' || s[i] == '{')
            st.push(s[i]);
        else if(s[i] == ')'){
            if(st.empty() || st.top() != '('){
                cout << ") " << i <<endl;
                return 0;
            }
            st.pop();
        }
        else if(s[i] == ']'){
            if(st.empty() || st.top() != '['){
                cout << "] " << i <<endl;
                return 0;
            }
            st.pop();
        }
        else if(s[i] == '}'){
            if(st.empty() || st.top() != '{'){
                cout << "} " << i <<endl;
                return 0;
            }
            st.pop();
        }
    }
    cout << "ok so far" << endl;
}