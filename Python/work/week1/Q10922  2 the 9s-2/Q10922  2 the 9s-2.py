
# coding: utf-8

# In[4]:


while(True):
    num=input()
    if num[0] == '0':break
    countNum=0
    sum=[0]*10
    tmp=num
    isFind=False
    while(True):
        for i in tmp:
            sum[countNum] += int(i)
        if sum[countNum]==9:
            isFind=True
        tmp=str(sum[countNum])
        if(isFind or sum[countNum]<=9):break
        countNum+=1
    if(isFind):
        print(num+" is a multiple of 9 and has 9-degree "+str(countNum+1)+".")
    else:
        print(num+" is not a multiple of 9.")


# In[ ]:


printf(sum)

