#include<iostream>
#include<string.h>
using namespace std;
int main(){
    int endNum,tmp,num[10],times;
    cin>>times;
    while(times--){
        cin>>endNum;
        memset(num,0,sizeof(num));
        for(int i = 1;i <= endNum; i++){
            tmp=i;
            while(tmp>0){

                num[tmp%10]++;
                tmp/=10;
            }

        }
        for(int i =0;i<10;i++)
            cout<<num[i]<<(i==9?"\n":" ");

    }

}

