 #include<iostream>
using namespace std;
void digitCount(int digit[],int num){
    int tmp=num , base=1;
    while(tmp > 0){
        if(num>=base)
            digit[0]-=base;
        digit[tmp%10]+=num%base+1;
        for(int i = 0; i < (tmp%10) ;i++)
            digit[i]+=base;
        tmp/=10;
        for(int i = 0; i<10;i++)
            digit[i]+= tmp*base;
         base*=10;
    }

}
int main(){
    int num1,num2;
    while(cin>>num1>>num2 && num1 && num2){
        int digit_1[10]={0} , digit_2[10]={0};
        digitCount(digit_1,num1-1);
        digitCount(digit_2,num2);
        for(int i = 0;i < 10;i++)
            cout<<digit_2[i] - digit_1[i] <<(i==9?"\n":" ");
    }
}
