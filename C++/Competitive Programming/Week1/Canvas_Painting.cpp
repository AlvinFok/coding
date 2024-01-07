#include<iostream>
#include<queue>
#include<vector>


using namespace std;

int main(){
    int T;
    cin >> T;
    while(T--){
        int N;
        cin >> N;
        priority_queue<long, vector<long>, greater<long> > canvas;
        long tmp;
        for(int i = 0;i < N;i++){
            cin >> tmp;
            canvas.push(tmp);
        }

        long counter = 0;
        while(canvas.size() != 1){
            long a = canvas.top();canvas.pop();
            long b = canvas.top();canvas.pop();
            counter += (a + b);
            canvas.push(a + b);
        }
        cout << counter << endl;
        canvas.pop();
    }

}