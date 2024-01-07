#include <iostream>
#include <vector>

using namespace std;


int countGoodRectangles(vector<vector<int> >& rectangles) {
    int mn = 0, mx = 0, count = 0;
    for (auto rectangle : rectangles)
    {
        mn = min(rectangle[0], rectangle[1]);
        if(mn > mx){
            mx = mn;
            count = 1;
        }

        else if(mn == mx){
            count++;
        }
    }
    return count;
    
}

int main(){
    vector<vector<int> > a {{5,8},{3,9},{5,12},{16,5}};
    vector<vector<int> > b {{2,3},{3,7},{4,3},{3,7}};

    countGoodRectangles(a);
    countGoodRectangles(b);
    return 0;
}