#include<iostream>
#include<vector>

using namespace std;


int n, m, ans=0;
int dx[] = {0, 1, 1, 1, 0, -1, -1, -1}, dy[] = {-1, -1, 0, 1, 1, 1, 0, -1};
char mat[120][120];

void dfs(int r, int c){
    mat[r][c] = '.';
    for(int i = 0; i < 8; i++){
        int tx = r + dx[i];
        int ty = c + dy[i];
        bool valid = tx >= 0 && tx < n && ty >= 0 && ty < m;
        if(!valid || mat[tx][ty] == '.')
            continue;

        // cout << tx << " " << ty <<endl;

        dfs(tx, ty);
        
    }

}


int main(){
    cin >> n >> m;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            char c;
            cin >> c;
            mat[i][j] = c;
        }
    }

    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            if(mat[i][j] == '#'){
                ans++;
                dfs(i, j);
            }
        }
    }

    cout << ans << endl;
}