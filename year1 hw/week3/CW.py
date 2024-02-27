
# coding: utf-8

# In[22]:

import numpy as np
array=np.random.randint(20,80,30)
print(array[array>60]*5)


# In[26]:

array=np.array([[34,651,76],[78,-53,34],[-32,565,34],[34,23,54]])
array=np.clip(array,0,255)
array=np.array_split(array,3,axis=0)
b=np.sum(array[0])+np.sum(array[1])
print(b)



# In[75]:

import matplotlib.pyplot as plt
x1=[2,6,3.75,2]
y1=[12,12,17,12]
x2=[3,2,6,5]
y2=[12,6,6,12]
x3=[3.5,4,4.5]
y3=[6,6,6]
x4=[3,4,5,2.5,3.5,4.5,5.5]
y4=[11,12,10.5,7.5,8,9.5,7]
plt.plot(x1,y1,color="yellow")
plt.plot(x2,y2,color="red")
plt.bar(x3,y3,color="black")
plt.scatter(x4,y4,s=50,c="green",alpha=0.4)
plt.show()


# In[76]:

data=np.random.normal(0,10,10000)
bin=np.arange(-20,21,1)
plt.hist(data,bins=bin)
plt.show()


# In[98]:

import seaborn as sns
data=sns.load_dataset("iris")
plt.subplot(2,2,1)
plt.scatter(data["sepal_length"],data["sepal_length"],s=30,alpha=1)
plt.subplot(2,2,2)
plt.scatter(data["sepal_length"],data["sepal_width"],s=30,alpha=1)
plt.subplot(2,2,3)
plt.scatter(data["sepal_length"],data["petal_length"],s=30,alpha=1)
plt.subplot(2,2,4)
plt.scatter(data["sepal_length"],data["petal_width"],s=30,alpha=1)
plt.show()

