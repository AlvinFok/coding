#include<iostream>
#include<vector>

using namespace std;

vector<int> findDiagonalOrder(vector<vector<int> >& mat) {
    if(mat.empty() || mat.size() == 0 )return vector<int> {};
    int M=mat.size(), N=mat[0].size();
    int i = 0, j = 0, count = 1;
    vector<int> ans;
    ans.push_back(mat[0][0]);
    while(ans.size() < M*N){
        while(i>0 && j<N-1){//move up
            i--;
            j++;
            ans.push_back(mat[i][j]);
        }
        if(j < N-1){
            j++;
            ans.push_back(mat[i][j]);
        }
        else if(i < M - 1){
            i++;
            ans.push_back(mat[i][j]);
        }

        while(i < M - 1 && j > 0){//move down
            i++;
            j--;
            ans.push_back(mat[i][j]);
        }
        if(i< M - 1){
            i++;
            ans.push_back(mat[i][j]);
        }
        else if(j < N-1){
            j++;
            ans.push_back(mat[i][j]);
        }


    }
    return ans;

}

void print(vector<int> num){
    for(int i =0;i<num.size();i++){
        cout<<num[i]<< " ";
    }
    cout<<endl;
}


int main(){
    vector<vector<int> > num {{1,2,3,4,5}, {6,7,8,9,10}, {11,12,13,14,15}, {16,17,18,19,20}};
    print(findDiagonalOrder(num));
    vector<vector<int> > num1 {{1,2,3},{4,5,6},{7,8,9}};
    print(findDiagonalOrder(num1));
    vector<vector<int> > num2 {{1,2},{3,4}};
    print(findDiagonalOrder(num2));
    return 0;
}