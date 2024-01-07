#include<iostream>
using namespace std;

int main(){
    long long int startNum,endNum;
    while(cin>>startNum>>endNum && startNum != -1 && endNum != -1){
        long long sum = 0;
        while(startNum<=endNum){
            if(startNum%10 == 0){
                cout<<"10 here"<<endl;
                long long int tmp = startNum;
                while(tmp >= 10){
                    tmp/=10;
                }
                cout<<"tmp = "<< tmp<< endl;
                sum+=tmp;
                cout<< "[10]sum = " << sum<<endl;
            }
            else{
                sum+=startNum%10;
                cout<< "sum = " << sum<<endl;
            }

            startNum++;
        }
        cout<< sum << endl;
    }
    return 0;
}
