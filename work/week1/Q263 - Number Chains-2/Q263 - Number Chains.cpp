#include<iostream>
#include<algorithm>
using namespace std;
int main(){
    string input;
    while(cin>>input &&(atoi(input.c_str())!=0)){
        string numberStore[100]={"\0"};
        int storeTimes=0,upperNum,lowerNum;
        bool isFind=false;
        cout<<"Original number was "<<input<<endl;
        while(isFind == false){
            sort(input.begin(), input.end());
            lowerNum=atoi(input.c_str());
            reverse(input.begin(),input.end());
            upperNum = atoi(input.c_str());
            numberStore[storeTimes] = to_string(upperNum-lowerNum);
            input = numberStore[storeTimes];
            cout<< upperNum << " - " << lowerNum << " = " << numberStore[storeTimes++] <<endl;
            for(int i = 0;i < storeTimes;i++){
                for(int j = 0;j < storeTimes,j != i;j++){
                    if(numberStore[i].compare(numberStore[j]) == 0)
                        isFind=true;
                }
            }
        }
        cout<< "Chain length " << storeTimes << "\n" <<endl;
    }
}
