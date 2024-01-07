#include<iostream>
#include<limits.h>
#include<queue>
#include<vector>

using namespace std;

int r, c;
vector< vector<int> > graph;
vector< vector<int> > dis;
struct  Node
{       
    int x, y, cost;
    Node() {}
    Node(int a, int b, int newCost){
        x = a;
        y = b;
        cost = newCost;
    }

    bool operator()(Node &a, Node &b){
        return a.cost > b.cost;
    }
};


void dijkstra(){
    priority_queue<Node, vector<Node>, Node> q;
    for(int i = 0; i < r; i++){
        Node n(i, 0, graph[i][0]);
        q.push(n);
        dis[i][0] = graph[i][0];
    }

    while(!q.empty()){
        Node n = q.top();
        q.pop();
        int x = n.x;
        int y = n.y;
        int cost = n.cost;

        if(cost > dis[x][y])
            continue;
        
        if(x - 1 >=0){
            if(max(graph[x - 1][y], cost) < dis[x - 1][y]){
                dis[x - 1][y] = max(graph[x - 1][y], cost);
                Node current(x - 1, y, dis[x - 1][y]);
                q.push(current);
                
            }
        }
        if(x + 1 < r){
            if(max(graph[x + 1][y], cost) < dis[x + 1][y]){
                dis[x + 1][y] = max(graph[x + 1][y], cost);
                Node current(x + 1, y, dis[x + 1][y]);
                q.push(current);
            }
        }
        if(y - 1 >=0){
            if(max(graph[x][y - 1], cost) < dis[x][y - 1]){
                dis[x][y - 1] = max(graph[x][y - 1], cost);
                Node current(x, y - 1, dis[x][y - 1]);
                q.push(current);
            }
        }
        if(y + 1 < c){
            if(max(graph[x][y + 1], cost) < dis[x][y + 1]){
                dis[x][y + 1] = max(graph[x][y + 1], cost);
                Node current(x, y + 1, dis[x][y + 1]);
                q.push(current);
            }
        }
    }
}

int main(){
    
    cin >> r >> c;
    graph.resize(r, vector<int>(c, 0));
    dis.resize(r, vector<int>(c, INT_MAX));
    for(int i = 0; i < r ;i++)
        for(int j = 0; j < c; j++)
            cin >> graph[i][j];
    
    dijkstra();
        
    int ans = INT_MAX;
    for(int i = 0; i < r; i++){
        ans = min(ans, dis[i][c - 1]);
    }

    cout << ans << endl;
}