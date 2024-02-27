#include<iostream>
#include<map>
#include<vector>
#include<stack>

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
    default://not
        return !a;
        break;
    }
}

int main(){
    int n;
    map<char, bool> m;
    cin >> n;
    cin.ignore();
    char A = 'A';
    for(int i = 0; i < n; i++){
        char c;
        cin >> c;
        if(c == 'T')
            m[A++] = true; 
        else if(c == 'F')
            m[A++] = false; 
    }

    string s;
    getline(cin>>ws, s);
    stack<bool> st;
    for(char c:s){
        if(c >= 'A' && c <= 'Z'){
            st.push(m[c]);
        }
        else if(c == '*' || c == '+'){
            bool a, b;
            a = st.top();
            st.pop();
            b = st.top();
            st.pop();
            st.push(eval(a, b, c));
        }
        else if(c == '-'){
            bool a;
            a = st.top();
            st.pop();
            st.push(eval(a, true, c));
        }
    }

    if(st.top())
        cout << 'T' << endl;
    else
        cout << 'F' << endl;

}