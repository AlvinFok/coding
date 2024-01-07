
# coding: utf-8

# In[2]:


import seaborn as sns
import matplotlib.pyplot as plt
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

