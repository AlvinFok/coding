#include<iostream>
#include<string>
using namespace std;
int main(){
    string num;
    while(cin>>num && num[0]!='0'){
        int sum[10]={00},countNum=0;
        string tmp=num;
        bool isFind=false;
        do{
            for(int i =0;i<tmp.length();i++){
                sum[countNum] += tmp[i] - '0';
            }
            if(sum[countNum] == 9){
                isFind=true;
            }
            tmp=to_string(sum[countNum]);
        }while(sum[countNum++] > 9);
        if(isFind)cout<<num << " is a multiple of 9 and has 9-degree " << countNum <<"."<<endl;
        else cout<< num << " is not a multiple of 9." <<endl;
    }
}
