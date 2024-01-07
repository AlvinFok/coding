#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

typedef long long ll;

ll b, n, e;
vector<pair<ll, string> > speeds;


void dec(string s, ll& tb, ll& tn, ll& te){
    for(char c : s){
        if(c == 'b')
            tb--;
        else if(c == 'n')
            tn--;
        else if (c == 'e')
            te--;
    }
}

bool ok(string s ,ll tb, ll tn, ll te){
    dec(s, tb, tn, te);
    return (tb >= 0) && (tn >= 0) && (te >= 0);
}

bool work(vector<ll> kayaks, ll speed){
    ll tb = b, tn = n, te = e;
    bool work = true;
    for(ll i : kayaks){
        bool thisWork = false;
        for(auto j: speeds){
            if(i * j.first >= speed && ok(j.second, tb, tn, te)){
                dec(j.second, tb, tn, te);
                thisWork = true;
                break;
            }
        }
        if(!thisWork){
            work = false;
            break;
        }
            
    }
    return work;
}


int main(){
    
    ll bv, nv, ev;
    cin >> b >> n >>e;
    cin >> bv >> nv >> ev;
    ll m = (b + n + e) / 2;

    vector<ll> kayaks(m);
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

    long long l = 0, r = (ll)100000 * 1000 * 2;
    while( r - l > 1){
        long long mid = (l + r) / 2;
        if(work(kayaks, mid))
            l = mid;
        else
            r = mid;
        
    }

    cout << l << endl;
}
