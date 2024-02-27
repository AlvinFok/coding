
# coding: utf-8

# In[9]:


from keras.models import Sequential
from keras.layers import Dense
from keras.utils import to_categorical
from keras.datasets import cifar10
from keras.datasets import mnist
import numpy as np
from PIL import Image
from sklearn.model_selection import train_test_split
import matplotlib.pyplot as plt
(x_train,y_train),(x_test,y_test)=mnist.load_data()
test=[]
train=[]
y_train=to_categorical(y_train)
y_test=to_categorical(y_test)
for i in range(60000):
    img=Image.fromarray(x_train[i],"L")
    img=np.array(img.resize((14,14),Image.BILINEAR))
    train.append(img)
for i in range(10000):
    img=Image.fromarray(x_test[i],"L")
    img=np.array(img.resize((14,14),Image.BILINEAR))
    test.append(img)
train=np.array(train).reshape(60000,196)
test=np.array(test).reshape(10000,196)
model=Sequential()
model.add(Dense(64,input_shape=(196,),activation='relu'))
model.add(Dense(32,activation='relu'))
model.add(Dense(16,activation='relu'))
model.add(Dense(8,activation='relu'))
model.add(Dense(10,activation='softmax'))
model.compile(loss='categorical_crossentropy',optimizer='adam',metrics=['accuracy'])
model.fit(train,y_train,batch_size=8,epochs=5,validation_split=0.2)
loss,accuracy=model.evaluate(test,y_test)
print(accuracy)


# ## HW-2

# In[13]:


(x_train,y_train),(x_test,y_test)=cifar10.load_data()
test=[]
train=[]
y_train=to_categorical(y_train)
y_test=to_categorical(y_test)
for i in range(50000):
    img=Image.fromarray(x_train[i],"RGB")
    img=np.array(img.convert('L'))
    train.append(img)
for i in range(10000):
    img=Image.fromarray(x_test[i],"RGB")
    img=np.array(img.convert('L'))
    test.append(img)
train=np.array(train).reshape(50000,1024)
test=np.array(test).reshape(10000,1024)
model=Sequential()
model.add(Dense(64,input_shape=(1024,),activation='relu'))
model.add(Dense(32,activation='relu'))
model.add(Dense(16,activation='relu'))
model.add(Dense(8,activation='relu'))
model.add(Dense(10,activation='softmax'))
model.compile(loss='categorical_crossentropy',optimizer='adam',metrics=['accuracy'])
model.fit(train,y_train,batch_size=8,epochs=5,validation_split=0.2)
loss,accuracy=model.evaluate(test,y_test)
print(accuracy)

