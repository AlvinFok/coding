#include<iostream>
#include<vector>

using namespace std;

int main(){
    int N;
    cin >> N;
    vector<int> m;
    m.resize(N, 0);
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            int a;
            cin >> a;
            m[i] ^= a;
        }
    }

    for(int i = 0; i < N; i++)
        cout << m[i] << " ";
    cout << endl;
}