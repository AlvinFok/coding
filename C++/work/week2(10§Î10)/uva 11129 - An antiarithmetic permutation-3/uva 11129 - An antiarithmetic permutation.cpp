#include<iostream>
#include<cstring>
using namespace std;
int ans[10005],tmp[10005];
void slove(int left,int right){
    int i,j;
    if(left==right)return;
    memcpy(tmp,ans,sizeof(ans));
    for(i=left,j=left; i<=right; i+=2,j++){
        ans[j]=tmp[i];
    }
    for(i=left+1; i<=right; i+=2,j++){
        ans[j]=tmp[i];
    }
    slove(left,(left+right)/2);
    slove((left+right)/2+1,right);
}
int main(){
    int input;
    while(cin>>input && input){
        for(int i=0; i<input; i++)
            ans[i]=i;

        slove(0,input-1);
        cout<< input << ":";
        for(int i =0; i<input; i++){
            cout<< " " << ans[i];
        }
        cout<<endl;
    }
}
