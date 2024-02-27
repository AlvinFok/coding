#include<iostream>
#include<map>
#include<vector>
#include<cstdio>
#include<fstream>
using namespace std;
int main(){
    map<int , vector<int> >numMap;
    int arraySize,times,num;
    ofstream file;
    while(scanf("%d %d",&arraySize,&times) != EOF){

        file.open("output.txt");
        numMap.clear();
        for(int i =0;i <arraySize;i++){
            cin>>num;
            numMap[num].push_back(i+1);
        }

        while(times--){
            int k,v;
            cin>>k>>v;
            if(numMap[v].size()<k)file<<"0"<<endl;
            else file<<numMap[v][k-1]<<endl;

        }
        file<<"\n";
    }
    file.close();
}
