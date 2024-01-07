#include<iostream>

using namespace std;


int maxNumberOfBalloons(string text) {
    int alphabet[5] = {0};//balon  balloon
    for(auto c : text){
        switch (c)
        {
        case 'b':
            alphabet[0] += 1;
            break;

        case 'a':
            alphabet[1] += 1;
            break;

        case 'l':
            alphabet[2] += 1;
            break;
        
        case 'o':
            alphabet[3] += 1;
            break;

        case 'n':
            alphabet[4] += 1;
            break;
        
        default:
            break;
        }
    }

    alphabet[2] /= 2;//two 'l' needed
    alphabet[3] /= 2;//two 'o' needed
    int min = INT_MAX;
    for (int i = 0; i < 5; i++)
    {
        if(alphabet[i] < min){
            min = alphabet[i];
        }
    }
    
    return min;


}

int main(){
    cout << maxNumberOfBalloons("nlaebolko") << endl;
    cout << maxNumberOfBalloons("loonbalxballpoon") << endl;
    cout << maxNumberOfBalloons("leetcode") << endl;

    return 0;
}