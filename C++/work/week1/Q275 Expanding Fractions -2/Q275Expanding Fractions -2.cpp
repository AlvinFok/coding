#include<iostream>
using namespace std;
int main(){
    int n,m;
    int store[100000];
    string output;
    while(cin>>n>>m &&n &&m){
        fill(store,store+2000,-1);
        output=".";
        store[n]=0;
        while(n){
            n*=10;
            output+= (n/m)+'0';
            n%=m;
            if(store[n%m] != -1)break;
            store[n] = output.length()-1;
        }
        for(int i =0;i < output.length();i++){
            if(i&&(i%50==0))cout<<endl;
            cout<<output[i];
        }
        if(n){
            cout<<"\n"<<"The last "<<output.length()-store[n%m]-1<<" digits repeat forever."<<endl;
        }
        else cout<<"\n"<<"This expansion terminates."<<endl;
        cout<<endl;
    }
    return 0;
}
