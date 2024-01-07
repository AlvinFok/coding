#include<iostream>
#include<string>
#include<stack>
#include<map>

using namespace std;



bool eval(bool a, bool b, char op){
    switch (op)
    {
    case '*':
        return a & b;
        break;
    
    case '+':
        return a | b;
        break;
    default:
        return !a;
        break;
    }
}

int main(){
    int N;
    cin >> N;
    map<char, bool> m;
    char A = 'A';
    string s;
    getline(cin>>ws, s);
    for(char c:s){
        if(c == 'T'){
            m[A++] = true;
        }
        else if(c == 'F'){
            m[A++] = false;
        }
        
    }

    getline(cin>>ws, s);
    stack<bool> st;
    for(char c:s){
        if(c == '*' || c == '+'){
            bool a = st.top();
            st.pop();
            bool b = st.top();
            st.pop();
            st.push(eval(a, b, c));
        }
        else if(c == '-'){
            bool a = st.top();
            st.pop();
            st.push(eval(a, false, c));
        }
        else if(c != ' '){
            st.push(m[c]);
        }
    }

    if(st.top() == true)
        cout << 'T' << endl;
    else
        cout << 'F' << endl;

}