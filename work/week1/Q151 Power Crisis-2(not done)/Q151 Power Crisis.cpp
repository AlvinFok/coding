#include<iostream>
#include<stdlib.h>
#include<stdio.h>>
using namespace std;
int main(){
    int num;
    while(cin>> num && num != 0){
        int k = 2;
        bool player[num]={true};
        while(true){
            fill(player,player+num,true);
            int n = k;
            while(player[12] != false){
                cout<< "??" <<endl;
                if(player[12] == false)break;
                n+=k;
                if(player[n%num] == false)
                    n++;
                else
                    player[n%num] = false;

            }
            if(player[12]==true)break;
            k++;
        }

    }
}
