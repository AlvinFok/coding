#include<iostream>
#include<cstring>
#include<cstdio>
using namespace std;
int gcd(int a , int b){
    int r;
    while(b>0){
        r=a%b;
        a=b;
        b=r;
    }
    return a;
}
int main(){
    string input;
    while(cin>>input && input!="#"){
        int letter[26] ={} , len = input.length();
        for(int i =0 ; i < len ;i++)
            letter[input[i] - 'a']++;

        long long int ans =0;
        for(int i =0 ;i < len ;i++){

            for(int j =0 ;j < input[i] - 'a';j++){

                if(letter[j]==0)continue;
                int letterAfterThis = len - i -1;

                letter[j]--;
                int num[31] ={};

                for(int k =2;k <= letterAfterThis;k++)
                    num[k]=k;

                for(int k =0;k<26;k++){

                    for(int s =2 ;s<=letter[k];s++){

                        int tmp = s;
                        for(int y =2;y<=letterAfterThis && tmp>1;y++){

                            int gcd_num = gcd(tmp,num[y]);
                            tmp/=gcd_num;
                            num[y]/=gcd_num;
                        }
                    }
                }
                letter[j]++;
                long long result = 1;
                for(int k =2 ;k<=letterAfterThis;k++)
                    result*=num[k];

                ans+=result;

            }
            letter[input[i] - 'a']--;
        }
        printf("%10lld\n",ans+1);
    }

}
