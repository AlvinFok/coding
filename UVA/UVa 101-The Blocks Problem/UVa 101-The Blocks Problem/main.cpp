//
//  main.cpp
//  UVa 101-The Blocks Problem
//
//  Created by Alvin on 2019/9/22.
//  Copyright © 2019 Alvin. All rights reserved.
//

#include <iostream>
#include <map>
#include <vector>
using namespace std;

void init_block(int block);

//int main(int argc, const char * argv[]) {
//    // insert code here...
//    string cmd1, cmd2;
//    int a, b, blockSize;
//    map<int, vector<int>>block;
//
//    cin>>blockSize;
//    int pos[blockSize];
//    for(int i = 0; i < blockSize; i++){
//        block[i].push_back(i);
//        pos[i] = i;
//    }
//    while(cin >>cmd1 >>a >>cmd2 >>b){
//        if(a == b)continue;
//        if(pos[a] == pos[b])continue;
//        if(cmd1 == "move")init_block(a);
//        if(cmd2 == "onto")init_block(b);
//
//    }
//    return 0;
//}

int main(){
    string in;
    getline(cin, in);
    cout<<in<<endl;
    return 0;
}

void init_block(int block){
    
}


