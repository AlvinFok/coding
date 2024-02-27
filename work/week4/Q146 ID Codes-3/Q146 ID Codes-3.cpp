#include<iostream>
#include<algorithm>
using namespace std;
int main(){
    string input;
    while(cin>>input && input!="#"){
        if(next_permutation(input.begin() , input.end())==0)
            cout<<"No Successor"<<endl;
        else
            cout<<input<<endl;
    }
}
