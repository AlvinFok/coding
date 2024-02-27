#include<iostream>
#include<map>
#include<vector>

using namespace std;


vector< vector<int> > node;
vector<bool> visited;
vector<bool> endNode;
bool black = true;

void dfs(int start){
    bool canMove = false;
    for(int i : node[start]){
        if(i < 0){//red
            i = -i;
            canMove = true;
            if(visited[i])
                continue;
            
            visited[i] = true;
            dfs(i);
            visited[i] = false;
        }
        else if(black){
            if(visited[i])
                continue;
            visited[i] = true;
            black = false;
            dfs(i);
            visited[i] = false;
            black = true;
        }
    }
    if(!canMove)
        endNode[start] = true;
}

int main(){
    int n, m;
    cin >> n >> m;

    node.resize(n + 1, vector<int>(0));
    visited.resize(n + 1, false);
    endNode.resize(n + 1, false);
    for(int i = 0; i < m; i++){
        int a, b;
        cin >> a >> b;
        if(a < 0)
            node[-a].push_back(-b);
        else
            node[a].push_back(b);
    }
    visited[1] = true;
    dfs(1);
    int ans = 0;
    for(bool i : endNode){
        if(i)
            ans++;
    }
    cout << ans << endl;
}