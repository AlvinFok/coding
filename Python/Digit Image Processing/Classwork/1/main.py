#矩陣乘法
#%%
a = [[1, 2], [3, 4]]
b = [[0, 4], [1, 1]]
c = [[0,0], [0,0]]
for i in range(len(a)):
    for j in range(len(b)):
        for k in range(len(a)):
            c[i][j] += a[i][k] * b[k][j]

#EX2
#%%
import numpy as np
print(np.floor(4.5) + np.floor(-4.5))
print(np.ceil(4.5) + np.ceil(-4.5))
print(20 * np.arctan(1 / 7) + 8 * np.arctan(3 / 79))

#EX5
# %%
import numpy as np
import cv2
img1 = np.zeros([512, 512], dtype=np.uint8)
img2 = np.ones([512, 512], dtype=np.float32)

cv2.imshow('img1', img1)
cv2.imshow('img2', img2)
cv2.waitKey()

#parctice
# %%
import numpy as np
import cv2
white = np.ones([100, 100], dtype=np.float32)
black = np.zeros([100, 100], dtype=np.uint8)
whiteBlackStack = np.hstack([white, black, white, black, white])
blackWhiteStack = np.hstack([black, white, black, white, black])
image = np.vstack([blackWhiteStack, whiteBlackStack, blackWhiteStack, whiteBlackStack, blackWhiteStack])
cv2.imshow('test', image)
cv2.waitKey()
# %%
import numpy as np
import cv2
image = np.zeros([500, 500], dtype=np.uint8)
for i in range(500):
    y = int(i**(2/3))
    image[y][i] = 255
cv2.imshow('test', image)
cv2.waitKey()

#EX2:5
# %%
import numpy as np
a = np.array([[0, 1, 2, 3, 4], [5, 6, 7, 8, 9], [10, 11, 12, 13, 14]])
print(a[1])
print(a[1:])
print(a[1, 2:])
print(a[:2, 2:])
print(a[:, 2:4])

# %%
import numpy as np
import cv2
image = np.zeros([500,500],dtype=np.uint8)
for i in range(5):
    for j in range(5):
        if ((i + j) % 2 == 0):
            cv2.rectangle(image,(i*100,j*100), (i*100 + 100,j*100 +100),255,-1)

cv2.imshow('test', image)
cv2.waitKey()
cv2.destroyAllWindows()
# %%
