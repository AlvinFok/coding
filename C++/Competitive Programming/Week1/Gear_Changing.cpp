#include<iostream>
#include<vector>
#include<set>


using namespace std;

int main(){
    int N, M;
    long double P;
    cin >> N >> M >> P;
    P /= 100;

    vector<long double> v1(N);
    for(auto& i:v1)
        cin >> i;

    vector<long double> v2(M);
    for(auto& i:v2)
        cin >> i;

    set<double> s;
    for(auto i:v1)
        for(auto j:v2)
            s.insert(i/j);

    long double curr = *s.begin();
    s.erase(curr);
    bool good = true;
    for(auto i:s){
        if(curr + curr * P < i){
            good = false;
            break;
        }
        curr = i;
    }

    if(good)
        cout << "Ride on!" << endl;
    else
        cout << "Time to change gears!" << endl;
}