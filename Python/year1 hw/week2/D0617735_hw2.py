
# coding: utf-8

# In[53]:


import pandas
data=pandas.read_csv("marry_broken.csv",encoding="big5")
data=data.drop_duplicates()
data=data.T.fillna(data.mean(axis=1)).T
print(data)

