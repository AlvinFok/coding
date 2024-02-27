#include<iostream>
#include<vector>
using namespace std;
int main(){
    int times,line;
    cin>>times;
    for(int t = 0 ; t <times ;t++){
        cin>>line;
        vector<int>store(line , -1);
        for(int i =0 ; i< line ; i++){
            int u ,v;
            cin>>u>>v;
            store[u-1] = v-1;
        }
        vector<bool>best_paths(line , false);
        int Max=0 , Max_paths=0;
        for(int i =0 ; i< line ;i++){
            if(best_paths[i])continue;
            vector<bool>visited(line , false);
            vector<int>dataStack;
            dataStack.push_back(i);
            visited[i] = best_paths[i] = true;
            int numCount =0 ;
            while(!dataStack.empty()){
                int tmp = dataStack.back();
                dataStack.pop_back();
                if(!visited[store[tmp]]){
                    numCount++;
                    visited[store[tmp]] = best_paths[store[tmp]] = true;
                    dataStack.push_back(store[tmp]);
                }
            }
            if(numCount > Max){
                Max = numCount;
                Max_paths = i;
            }
        }
        cout<<"Case " << t+1 <<": " << Max_paths+1 <<endl;
    }
}
