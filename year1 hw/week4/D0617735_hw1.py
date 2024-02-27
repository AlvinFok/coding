
# coding: utf-8

# In[4]:


class Vehicle:
    def __init__(self,a=0,p=0):
        self.age=a
        self.price=p
class Car(Vehicle):
    def __init__(self,a=0,p=0):
        super().__init__(a,p)
    def count(self):
        return self.price/self.age*100
class Bicycle(Vehicle):
    def __init__(self,a=0,p=0):
        super().__init__(a,p)
    def count(self):
        return self.price/self.age*10
onecar=Car(10,1000)
print(onecar.count())

