#include<iostream>
#include<cmath>>
using namespace std;
typedef long long int64;
int main(){
    long long int catHeight,catWork,catDontWork,n;
    double error = 1e-9;
    while(cin>>catHeight>>catWork && catHeight && catWork){

        for(n=0;
        fabs(log(catHeight)*log(n)-log(catWork)*log(n+1))>error;
        n++);
        if(n==1){
            catDontWork=int64(log2(catHeight)+0.5);
        }
        else
            catDontWork=(1-catWork)/(1-n);
        cout<<catDontWork<<" "<< (catHeight - catWork)*n +catHeight<<endl;
    }
}
