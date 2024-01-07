#include<iostream>
#include<cstdio>
using namespace std;

int c[27][6];
string str;
void init(){
    for(int i =0;i<27;i++){
        c[i][0] = 1;
        for(int j =1 ; j<6; j++){
            cout<<c[i-1][j-1] << " " << c[i-1][j]<<endl;
            c[i][j] = c[i-1][j-1] + c[i-1][j];
            //cout<<c[i][j]<<" ";
        }
        cout<<endl;
    }
}
void cal(){
     int len = str.length() , ans = 1;
        for(int i = 1 ; i < len ; i++){
            if(str[i-1] >= str[i]){
                cout<<"0"<<endl;
                return;
            }
            ans += c[26][i];
            cout<<"ans = " << ans <<endl;
        }

        char ch= 'a';
        for(int i=0;i<len;i++){
            for(;ch<str[i];ch++){
                ans += c['z'-ch][len-i-1];
            }
            ch++;
        }

        cout<<ans<<endl;
}
int main(){
    init();
    while((cin>>str) && str!=""){
       cal();
    }
}
