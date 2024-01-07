#%%
import cv2
import numpy as np
import matplotlib.pyplot as plt
#Count Gray histogram
imageGray = cv2.imread('3.jpeg', cv2.IMREAD_GRAYSCALE)
_, grayHist = np.unique(imageGray, return_counts=True)  #Counting

plt.figure()
plt.plot(grayHist)
plt.title('Count by myself(GrayScale)')
plt.show()
# %%
RGBHist = cv2.calcHist([imageGray], [0], None, [256], [0, 256])
plt.figure()
plt.plot(RGBHist)
plt.title('Count by opencv(GrayScale)')
plt.show()
# %%
#Count RGB histogram
imageRGB = cv2.imread('3.jpeg')
_, red = np.unique(imageRGB[:, :, 2], return_counts=True)
_, green = np.unique(imageRGB[:, :, 1], return_counts=True)
_, blue = np.unique(imageRGB[:, :, 0], return_counts=True)


plt.figure()
plt.plot(red, 'r-')
plt.plot(green, 'g-')
plt.plot(blue, 'b-')
plt.title('Count by myself(RGB)')
plt.show()
# %%
channels = cv2.split(imageRGB)
colors = ('b', 'g', 'r')
plt.figure()
for (chan, color) in zip(channels, colors):
    hist = cv2.calcHist([chan], [0], None, [256], [0, 256])
    plt.plot(hist, '{}-'.format(color))
plt.title('Count by opencv(RGB)')
plt.show()

#%%
#graysacle histogram equalizaton
cumsum_gray = np.cumsum(grayHist)#Accumulate the pixels
cumsum_gray_masked = np.ma.masked_equal(cumsum_gray, 0)#delete vlaue = 0 's pixel
cumsum_gray_masked = (cumsum_gray_masked - cumsum_gray_masked.min()) * 255 / (cumsum_gray_masked.max() - cumsum_gray_masked.min())#equation for histogram equalizaton
cumsum_gray_final = np.ma.filled(cumsum_gray_masked, 0).astype(np.uint8)
print(type(cumsum_gray_final))
imageGray2 = cumsum_gray_final[imageGray]

imageShowGray = np.hstack((imageGray, imageGray2))
plt.imshow(imageShowGray, cmap=plt.cm.gray)
plt.axis('off')
plt.show()
# %%
#RGB histogram equalizaton
r, g, b = cv2.split(imageRGB)

_, red = np.unique(r, return_counts=True)
_, green = np.unique(g, return_counts=True)
_, blue = np.unique(b, return_counts=True)

cumsum_b = np.cumsum(blue)
cumsum_g = np.cumsum(green)
cumsum_r = np.cumsum(red)

cumsum_blue_masked = np.ma.masked_equal(cumsum_b, 0)
cumsum_green_masked = np.ma.masked_equal(cumsum_g, 0)
cumsum_red_masked = np.ma.masked_equal(cumsum_r, 0)

cumsum_blue_masked = (cumsum_blue_masked - cumsum_blue_masked.min()) * 255 / (cumsum_blue_masked.max() - cumsum_blue_masked.min())
cumsum_green_masked = (cumsum_green_masked - cumsum_green_masked.min()) * 255 / (cumsum_green_masked.max() - cumsum_green_masked.min())
cumsum_red_masked = (cumsum_red_masked - cumsum_red_masked.min()) * 255 / (cumsum_red_masked.max() - cumsum_red_masked.min())

cumsum_blue_final = np.ma.filled(cumsum_blue_masked, 0).astype(np.uint8)
cumsum_green_final = np.ma.filled(cumsum_green_masked, 0).astype(np.uint8)
cumsum_red_final = np.ma.filled(cumsum_red_masked, 0).astype(np.uint8)

image_blue = cumsum_blue_final[b]
image_green = cumsum_green_final[g]
image_red = cumsum_red_final[r]

imageShowRGB = cv2.merge((image_blue, image_green, image_red))
imageShowRGB = np.hstack((imageRGB, imageShowRGB))
plt.imshow(imageShowRGB)
plt.axis('off')
plt.show()
#%%
gray = cv2.imread('gray.png')
print(gray.shape)
rgb = cv2.imread('Rgb.png')
print(rgb.shape)
image = np.vstack((gray[:1560], rgb[:,:2084]))
cv2.imwrite('merge.jpg',image)
# %%


