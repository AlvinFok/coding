#include<iostream>
#include<vector>

using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;

ll sum(vll& fenwick, int index){
    int total = 0;
    for(int i = index; i > 0; i -= i & -i){
        total += fenwick[i];
    }
    return total;
}

void update(vll& fenwick, int index, int value){
    for(int i = index; i < fenwick.size(); i += i & -i){
        fenwick[i] += value;
    }
}


int main(){
    int N, Q;
    cin >> N >> Q;
    vector<vll> fenwick;
    int gems[N+1];
    int value[6+1];
    for(int i = 1; i <= 6; i++)
        cin >> value[i];
    for(int i = 1; i <= N; i++){
        char c;
        cin >> c;
        gems[i] = c - '0';
    }
        

    fenwick.push_back(vll (0));
    for(int i = 1; i <= 6; i++){
        vll tmp(N+1, 0);
        tmp[0] = 0;
        for(int j = 1; j <= N; j++){
            if(gems[j] == i)
                update(tmp, j, 1);
            else
                update(tmp, j, 0);
        }
        fenwick.push_back(tmp);
    }
    

    while(Q--){
        int op, arg1, arg2;
        cin >> op >> arg1 >> arg2;
        if(op == 1){
            update(fenwick[gems[arg1]], arg1, -1);
            gems[arg1] = arg2;
            update(fenwick[gems[arg1]], arg1, 1);
        }
        else if(op == 2){
            value[arg1] = arg2;
        }
        else{
            ll ans = 0;
            for(int i = 1; i <= 6; i ++){
                ans += (sum(fenwick[i], arg2) - sum(fenwick[i], arg1-1)) * value[i];
            }
            cout << ans << endl;
        }
    }


}