
# coding: utf-8

# In[27]:


from keras.layers import Flatten,Dense,LSTM,Conv2D,MaxPooling2D
from keras.datasets import fashion_mnist
from keras.utils import to_categorical
from keras.models import Sequential
import numpy as np
from keras.utils import to_categorical
import pandas as pd
from sklearn.preprocessing import StandardScaler


# In[ ]:


(x_train,y_train),(x_test,y_test)=fashion_mnist.load_data()
print(y_test.shape)
x_test=np.reshape(x_test,(10000,28,28,1))
x_train=np.reshape(x_train,(60000,28,28,1))
y_train=to_categorical(y_train)


# In[ ]:


model=Sequential()
model.add(Conv2D(32,kernel_size=(2,2),activation='relu',input_shape=(28,28,1)))
model.add(Conv2D(64,(2,2),activation='relu'))
model.add(MaxPooling2D(pool_size=(2,2)))
model.add(Flatten())
model.add(Dense(32,activation='relu'))
model.add(Dense(10,activation='softmax'))
model.compile(loss='categorical_crossentropy',optimizer='adam',metrics=['accuracy'])
model.fit(x_train,y_train,batch_size=256,epochs=8,validation_split=0.2)


# # HW2
# 

# In[32]:


data=pd.read_csv('PRSA_data_2010.1.1-2014.12.31.csv')
x_train=[]
y_train=[]
data=data.replace('cv',0)
data=data.replace('NW',1)
data=data.replace('SE',2)
data=data.replace('NE',3)
data=data.fillna(0)
for i in range(5000):
    tmp=[]
    for j in range(25):
        if(j<24):
            tmp.append(data.iloc[i+j][5:12])
        else:
            y_train.append(data.iloc[i+j][5:12])
    x_train.append(tmp)
x_train=np.reshape(x_train,(5000,24*7))
y_train=np.reshape(y_train,(5000,7))


# In[33]:


scaler=StandardScaler()
scaler.fit(x_train)
x_train=scaler.transform(x_train)
x_train=np.reshape(x_train,(5000,24,7))
model=Sequential()
model.add(LSTM(128,input_shape=(24,7)))
model.add(Dense(64,activation='relu'))
model.add(Dense(32,activation='relu'))
model.add(Dense(16,activation='relu'))
model.add(Dense(8,activation='relu'))
model.add(Dense(4,activation='relu'))
model.add(Dense(2,activation='relu'))
model.add(Dense(7,activation='relu'))
model.compile(loss='mse',optimizer='adam',metrics=['mse'])
model.fit(x_train,y_train,batch_size=5,epochs=5,validation_split=0.2)

