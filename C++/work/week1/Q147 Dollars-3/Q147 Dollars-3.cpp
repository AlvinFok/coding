#include<stdio.h>
#include<stdlib.h>
long long int dollars[30001]={0};
main()
{
 int money[11]={10000,5000,2000,1000,500,200,100,50,20,10,5};
 dollars[0]=1;
 for(int i =0;i<11;i++)
    for(int j =money[i];j<=30000;j++)
       dollars[j]+=dollars[j-money[i]];
 int n,m;
 while(scanf("%d.%d",&n,&m)==2)
   {
     if(n==0&&m==0) break;
   printf("%3d.%02d%17lld\n",n,m,dollars[n*100+m]);
   }
 return 0;
}
