
# coding: utf-8

# In[2]:


import cv2
import time
import numpy as np


# In[36]:


cap =cv2.VideoCapture("test_video.mp4")
video_width =int(cap.get(cv2.CAP_PROP_FRAME_WIDTH))
video_higedt =int(cap.get(cv2.CAP_PROP_FRAME_HEIGHT))
fps = cap.get(cv2.CAP_PROP_FPS)
fourcc = cv2.VideoWriter_fourcc(*'DIVX')
out = cv2.VideoWriter("output.mp4", -1, fps, (video_width,video_higedt))
kernel_3 = np.ones((3,3))
kernel_5 = np.ones((5,5))
while(cap.isOpened()):
    ret,frame = cap.read()
    if(ret == False):
        print("video end")
        break
    else:
        gray = cv2.cvtColor(frame,cv2.COLOR_BGR2GRAY)
        a,Bin = cv2.threshold(gray,210,255, cv2.THRESH_BINARY)
        dilation = cv2.dilate(Bin, kernel_3)
        out.write(dilation)
        cv2.imshow('frame',dilation)
        if(cv2.waitKey(1) & 0xFF == ord('q')):
            break

cap.release()
out.release()
cv2.destroyAllWindows()

