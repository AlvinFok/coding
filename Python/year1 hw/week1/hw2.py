
# coding: utf-8

# In[3]:


tmp=set()
ans=int(input("Please enter ans"))
guess=int(input("Please enter guess"))
while(guess!=ans):
    if(guess in tmp):
        print("Aleardy have it")
    elif(guess<ans):
        print("larger")
    elif(guess>ans):
        print("smaller")
    tmp.add(guess)
    guess=int(input("Please enter guess"))
print("Right!")

