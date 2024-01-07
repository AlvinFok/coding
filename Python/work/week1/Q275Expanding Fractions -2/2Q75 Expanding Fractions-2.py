
# coding: utf-8

# In[10]:


while(True):
    n,m=map(int,input().split())
    if(n==0 and m==0):break
    store=[-1]*2000
    output="."
    store[n]=0
    while(n):
        n*=10;
        output+=str(int(n/m))
        n%=m
        if(store[n%m] != -1):break
        store[n] = len(output)-1
        
    for i in range(len(output)):
        if(i!=0 and (i%50==0)):print()
        print(output[i],end="")
            
    if(n):
        print('\n'+"The last " + str(len(output)-store[n%m]-1) + " digits repeat forever.")
    else:
        print('\nThis expansion terminates.')
    print()

