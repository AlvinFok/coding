# -*- coding: utf-8 -*-
"""
Spyder Editor

This is a temporary script file.
"""
import numpy as np
#%%
def standardCompute(array):
    return np.std(array)
#%%
array=[int(x) for x in input("enter data:\n").split()]
print(standardCompute(array))