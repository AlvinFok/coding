
# coding: utf-8

# In[63]:


import pandas
data=pandas.read_csv("boyGirlMarryNumber.csv",encoding="big5")
data["SUM"]=data.sum(axis=1)
data=data[data["SUM"]>5000]
data["IQR"]=data.quantile(0.75,axis=1)-data.quantile(0.25,axis=1)
print(data)

