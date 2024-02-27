#include<iostream>
#include<queue>
#include<vector>

using namespace std;



int main(){
    int x, y, ans = 0;
    cin >> y >> x;
    int land[x][y];
    vector< vector<bool> > visited(x, vector<bool>(y, false));
    int dx[] = {-1, 1, 0, 0}, dy[] = {0, 0, 1, -1};

    for(int i = 0; i < x; i++){
        for(int j = 0; j < y; j++){
            int num;
            cin >> num;
            land[i][j] = num;
        }
    }


    queue<pair<int, int> > q;
    for(int i = 0; i < x; i++){
        for(int j = 0; j < y; j++){
            if(visited[i][j])
                continue;
            visited[i][j] = true;
            pair<int, int> point(i, j);
            q.push(point);

            int count = 0;
            int isPool = true;
            while(!q.empty()){
                point = q.front();
                q.pop();
                count++;
                int r = point.first;
                int c = point.second;

                for(int k = 0; k < 4; k++){
                    int tx = r + dx[k];
                    int ty = c + dy[k];
                    bool isInBound = tx >= 0 && tx < x && ty >= 0 && ty < y;
                    if(isInBound){
                        if(!visited[tx][ty] && land[r][c] == land[tx][ty]){
                            pair<int, int> p(tx, ty);
                            q.push(p);
                            visited[tx][ty] = true;
                        }
                        if(land[tx][ty] < land[r][c]){
                            isPool = false;
                        }
                    }
                    
                    
                }
            }
            if(isPool)
                ans += count;
        }
    }

    cout << ans << endl; 

}