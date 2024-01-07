
# coding: utf-8

# In[2]:


while(True):
    numStore=list()
    numInput=input()
    if(numInput=='0'):break
    isFind=False
    print("Original number was " + str(numInput))
    storeTimes = 0
    while(not isFind):
        numInput = ''.join(sorted(numInput))
        lowerNum = int(numInput)
        upperNum = int(''.join(sorted(numInput,reverse=True)))
        numStore.append(str(upperNum - lowerNum))
        for i in range(storeTimes):
            for j in range(storeTimes):
                if(i==j):continue
                if(numStore[i]==numStore[j]):isFind = True
        if(isFind):break
        print(str(upperNum)+ " - " + str(lowerNum) + " = " + numStore[storeTimes])
        numInput = numStore[storeTimes]
        storeTimes+=1
    print("Chain length " + str(storeTimes)+'\n')

