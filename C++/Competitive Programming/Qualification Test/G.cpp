#include<iostream>
#include<stack>

using namespace std;

int main(){
    int n;
    string s;
    cin>>n;
    getline(cin>>ws, s);
    stack<char> st;
    int i;
    bool fine = true;
    for(i = 0; i < s.size(); i++){
        char c = s[i];
        if(c == '(')
            st.push('(');
        else if(c == '[')
            st.push('[');
        else if(c == '{')
            st.push('{');

        else if(c == ')'){
            if(st.size() == 0 || st.top() != '('){
                fine = false;
                break;
            }
            st.pop();
        }
            
        else if(c == ']'){
            if(st.size() == 0 || st.top() != '['){
                fine = false;
                break;
            }
            st.pop();

        }
        else if(c == '}'){
            if(st.size() == 0 || st.top() != '{'){
                fine = false;
                break;
            }
            st.pop();

        }
        

    }

    if(fine)
        cout << "ok so far" << endl;
    else
        cout << s[i] << " " << i << endl;

}