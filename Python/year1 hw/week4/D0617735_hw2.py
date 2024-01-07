
# coding: utf-8

# In[2]:


from sklearn import datasets
from sklearn.model_selection import train_test_split
from sklearn.neighbors import KNeighborsClassifier
from sklearn.metrics import classification_report
import matplotlib.pyplot as plt
iris=datasets.load_iris()
X_train,X_test,Y_train,Y_test=train_test_split(iris.data,iris.target,test_size=0.2)
knn=KNeighborsClassifier()
knn.fit(X_train,Y_train)
plt.scatter(X_test[:,0],X_test[:,2],marker='o',c=knn.predict(X_test))
plt.show()

