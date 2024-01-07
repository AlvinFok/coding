
# coding: utf-8

# In[ ]:


dollars=[0]*30001
money = [10000,5000,2000,1000,500,200,100,50,20,10,5]
dollars[0]=1
for i in range(11):
    j=money[i]
    while(j<=30000):
        dollars[j]+=dollars[j-money[i]]
        j+=1
while(True):
    n=float(input())
    if(n==0.0):break
    print("%6.2f%17d"%(n,dollars[int(n*100+0.5)])) 

