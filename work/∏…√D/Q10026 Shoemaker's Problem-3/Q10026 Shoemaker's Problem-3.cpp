#include<iostream>
#include<algorithm>
using namespace std;
typedef struct{
    int day,money,id;
    float weight;
}Node;
bool cmp(Node a , Node b){
    if (a.weight == b.weight)return a.id < b.id;
    else return a.weight > b.weight;
}
int main(){
    int times;
    cin>>times;
    while(times--){
        int Case;
        cin>>Case;
        Node work[Case+1];
        for(int i =1 ; i<=Case;i++){
            cin>>work[i].day>>work[i].money;
            work[i].weight = (float)work[i].money/work[i].day;
            work[i].id = i;
        }
        sort(work+1 ,work + Case +1 ,cmp);
        for(int i =1;i<Case;i++)
            cout<<work[i].id <<" ";
        cout<<work[Case].id <<endl;
        if(times)cout<<endl;
    }
}
