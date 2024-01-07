#include<iostream>
#include<cstring>

using namespace std;
typedef long long ll;

int fenwick[5000010];
int N, Q;
int sum(int index){
    int total = 0;
    while(index > 0) total+=fenwick[index], index -= index & -index;
    // for(; index > 0; index -= index & -index){
    //     total += fenwick[index];
    // }
    return total;
}

void update(int index, int value){
    // for(; index <= N; index += index & -index){
    //     fenwick[index] += value;
    // }
    while(index <= N) fenwick[index]+= value, index += index & -index;
}


int main(){
    
    cin >> N >> Q;
    // fenwick.resize(N+1, 0);
    memset(fenwick,0,sizeof(fenwick));
    while(Q--){
        char op;
        cin >> op;
        if(op == '+'){
            int arg1, arg2;
            cin >> arg1 >> arg2;
            update(arg1 + 1, arg2);
        }
        else{
            int arg1;
            cin >> arg1;
            
            cout << sum(arg1) << endl;
        }
    }
    
}