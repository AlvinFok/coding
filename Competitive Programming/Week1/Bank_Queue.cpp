#include<iostream>
#include<vector>
#include<algorithm>
#include <cstring>

using namespace std;

int main(){
    int N, T;
    cin >> N >> T;
    pair<int, int> p[10000];
    int q[10000];
    int c, t;
    for(int i = 0; i < N; i++){
        cin >> c >> t;
        p[i] = pair<int,int> (-c, t);
    }

    sort(p, p + N);

    memset(q, -1, sizeof(q));
    int ans = 0;
    for(int i = 0; i < N;i++){
        int money = -p[i].first;
        int time = p[i].second;
        for(int j = time; j >= 0; j--){
            if(q[j] == -1){
                q[j] = 0;
                ans += money;
                break;
            }
        }
    }
    
    cout << ans << endl;
}