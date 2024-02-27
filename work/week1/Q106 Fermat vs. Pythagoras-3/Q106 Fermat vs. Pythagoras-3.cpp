#include<iostream>
using namespace std;
int gcd(int m ,int n){
    int k;
    while(k=m%n){
        m=n;
        n=k;
    }
    return n;
}
short store[100000]={0};
int main(){
    int input;
    while(cin>>input && input){
        int numTuple=0;
        for(int x=1;x < 1000;x++){
            for(int y=x+1;;y+=2){
                if(gcd(x,y)!=1)continue;
                int a,b,c;
                a=y*y-x*x;
                b=2*x*y;
                c=x*x+y*y;
                if(c>input)break;
                numTuple++;

                int aTmp=a,bTmp=b,cTmp=c;
                while(cTmp<=input){
                    store[aTmp] = store[bTmp] = store[cTmp] = 1;
                    aTmp += a;
                    bTmp += b;
                    cTmp += c;
                }
            }
        }
        int nonNumTuple = input;
        for(int i=0;i<=input;i++){
            nonNumTuple-=store[i];
        }
        cout<<numTuple <<" "<< nonNumTuple <<endl;
    }
}
