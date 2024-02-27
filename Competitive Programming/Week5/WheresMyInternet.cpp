#include<iostream>
#include<vector>
#include<map>

using namespace std;

vector<bool> visited;
map<int, vector<int> > m;

void dfs(int start){
    visited[start] = true;
    for(auto i :m[start]){
        if(!visited[i])
            dfs(i);
    }
}

int main(){
    int N, M, a, b;
    cin >> N >> M;
    
    visited.resize(N+1, false);
    for(int i = 0; i < M; i++){
        cin >> a >> b;
        m[a].push_back(b);
        m[b].push_back(a);
    }
    dfs(1);
    bool connected = true;
    for(int i = 1; i < N+1; i++){
        if(!visited[i]){
            connected = false;
            cout << i << endl;
        }
    }

    if(connected)
        cout << "Connected" << endl;
}