#include<iostream>
#include<limits.h>

using namespace std;

int main(){
    int n ;
    cin >> n;
    int graph[n][n];
    for(int i = 0 ; i < n; i++)
        for(int j = 0; j < n; j++)
            cin >> graph[i][j];

    int mst[n], key[n];
    bool mstSet[n];
    
    for (int i = 0; i < n; i++) {
        key[i] = INT_MAX;
        mstSet[i] = false;
    }

    mst[0] = -1;
    key[0] = 0;
    for(int i = 0 ; i < n - 1; i++){
        int min = INT_MAX;
        int min_i;
        for(int j = 0 ; j < n; j++){
            if(!mstSet[j] && key[j] < min){
                min = key[j];
                min_i = j;
            }
        }

        mstSet[min_i] = true;
        for(int j = 0; j < n; j++){
            if(graph[min_i][j] != 0 && !mstSet[j] && graph[min_i][j] < key[j]){
                key[j] = graph[min_i][j];
                mst[j] = min_i;
            }
        }
    }

    for(int i = 1; i < n; i++)
        cout << mst[i] + 1 << " " << i+1 << endl;

}