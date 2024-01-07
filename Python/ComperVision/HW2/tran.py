#%%
import cv2
import numpy as np
from matplotlib import pyplot as plt

# %%
def to_matrix(img):#Tranform img to matrix
    H,W,C = img.shape
    mtr = np.zeros((W,H,C), dtype=np.uint8)
    for i in range(img.shape[0]):
        mtr[:,i] = img[i]
    
    return mtr

def to_image(mtr):#Tranform matrix to image
    W,H,C = mtr.shape
    img = np.zeros((H,W,C), dtype=np.uint8)
    for i in range(mtr.shape[0]):
        img[:,i] = mtr[i]
        
    return img
def get_equation(a, b, n):#n represent which equation
    res = []
    b = [b[0], b[1], 1]
    dim = 3
    for i in range(dim):
        equation = [0] * dim * 4
        equation[i] = a[0]
        equation[dim + i] = a[1]
        equation[2*dim + i] = 1 if i != 2 else 0
        
        equation[3*dim + n - 1] = -b[i]
        res.append(equation)
        
    return res
def getPerspectiveTransform(pts1, pts2):
    A = []
    pointLen = len(pts1)
    for i in range(pointLen):
        A += get_equation(pts1[i], pts2[i], i)
        
    B = [0, 0, -1] * pointLen
    C = np.linalg.solve(A, B)
    res = np.ones(9)
    res[:8] = C.flatten()[:8]#矩陣的右下角是1
    return res.reshape(3,-1).T

def warpPerspective(img, M, size):
    mtr = to_matrix(img)#Tranform img to matrix
    H,W = size
    dst = np.zeros((H,W,mtr.shape[2]))
    for i in range(mtr.shape[0]):
        for j in range(mtr.shape[1]):
            res = np.dot(M, [i,j,1])#點積
            i2,j2,_ = (res / res[2] + 0.5).astype(int)#目標位置
            if i2 >= 0 and i2 < H:#邊界處理
                if j2 >= 0 and j2 < W:
                    dst[i2,j2,:] = mtr[i,j,:]#destination scanning
    
    return to_image(dst)

def onMouse(event, x, y, flags, pointsList):
    if(event == cv2.EVENT_LBUTTONDOWN):
        pointsList.append([x,y])
