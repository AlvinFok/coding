import cv2
import numpy as np
image = cv2.imread('Doraemon.png')

cv2.imshow('b', image[:, :, 0])
cv2.imshow('g', image[:, :, 1])
cv2.imshow('r', image[:, :, 2])
color = np.zeros((268, 220, 3), dtype=np.uint8)
color[:, :, 0] = image[:, :, 0]
cv2.imshow('blue', color)
cv2.waitKey()
cv2.destroyAllWindows()