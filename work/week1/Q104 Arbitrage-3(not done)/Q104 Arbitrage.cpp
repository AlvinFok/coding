#include<iostream>
int main(){
    int type;
    while(cin>>type){
        int rate[type][type-1];
        for(int i = 0;i < type;i++){
            for(int j = 0;j < type-1;j++){
                cin>>rate[i][j];
                cout<< rate[i][j];
            }
            cout<<endl;
        }

    }
}
