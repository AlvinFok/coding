#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int b, n, e;
vector<pair<int, string> > speeds;


void dec(string s, int& tb, int& tn, int& te){
    for(char c : s){
        if(c == 'b')
            tb--;
        else if(c == 'n')
            tn--;
        else
            te--;
    }
}

bool ok(string s ,int tb, int tn, int te){
    dec(s, tb, tn, te);
    return (tb >= 0) && (tn >= 0) && (te >= 0);
}

bool work(vector<int> kayaks, long long int speed){
    int tb = b, tn = n, te = e;
    bool work = true;
    for(long long int i : kayaks){
        bool thisWork = false;
        for(auto j: speeds){
            if(i * j.first >= speed && ok(j.second, tb, tn, te)){
                dec(j.second, tb, tn, te);
                thisWork = true;
                break;
            }
        }
        if(!thisWork)
            work = false;
    }
    return work;
}


int main(){
    
    int bv, nv, ev;
    cin >> b >> n >>e;
    cin >> bv >> nv >> ev;
    int m = (b + n + e) / 2;

    vector<int> kayaks(m);
    for(auto& i:kayaks)
        cin >> i;
    sort(kayaks.begin(), kayaks.end());
    reverse(kayaks.begin(), kayaks.end());

    speeds.push_back({bv+bv, "bb"});
    speeds.push_back({bv+nv, "bn"});
    speeds.push_back({bv+ev, "be"});
    speeds.push_back({nv+nv, "nn"});
    speeds.push_back({nv+ev, "ne"});
    speeds.push_back({ev+ev, "ee"});

    sort(speeds.begin(), speeds.end());

    long long ans = 0, step = 100000 * 1000 * 2;
    while( step > 0){
        cout << ans << " " << step << endl;
        if(work(kayaks, ans + step))
            ans += step;
        step = step >> 1;
    }

    cout << ans << endl;
}
