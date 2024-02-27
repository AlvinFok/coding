
# coding: utf-8

# In[7]:


import numpy as np
import matplotlib.pyplot as plt
data=np.random.normal(0,10,10000)
bin=np.arange(-20,21,1)
plt.hist(data,bins=bin)
plt.show()

