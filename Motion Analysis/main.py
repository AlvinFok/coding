import cv2
import numpy as np
import imutils

#Capture webcam
video = cv2.VideoCapture(0)

#get video width and higet
width = int(video.get(cv2.CAP_PROP_FRAME_WIDTH))
height = int(video.get(cv2.CAP_PROP_FRAME_HEIGHT))
print('Frame Width:{}'.format(width))
print('Frame Height:{}'.format(height))

#create background subtractor
fgbg_mog2 = cv2.createBackgroundSubtractorMOG2()
fgbg_knn = cv2.createBackgroundSubtractorKNN()

kernel = cv2.getStructuringElement(cv2.MORPH_ELLIPSE, (3, 3))

def preprocess(image):
    image = cv2.cvtColor(image, cv2.COLOR_RGB2GRAY)
    #image = cv2.GaussianBlur(image, (47, 47), 0)
    return image

def posprocess(img):
    (T, img) = cv2.threshold(img, 90, 255, cv2.THRESH_BINARY)
    #img = cv2.adaptiveThreshold(img,255,cv2.ADAPTIVE_THRESH_MEAN_C,\
    #    cv2.THRESH_BINARY,11,2)
    img = cv2.dilate(img, None, iterations=42)
    img = cv2.erode(img, None, iterations=42)
    img = cv2.dilate(img, None, iterations=8)

    return img

def findContours(img):
    cnts, _ = cv2.findContours(img.copy(), cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

    return cnts


# lastFrame = None
while True:
    ret, frame = video.read()
    frame_preprocess = preprocess(frame)
    fgmask_mog2 = fgbg_mog2.apply(frame_preprocess)
    fgmask_knn = fgbg_knn.apply(frame_preprocess)
    
    fgmask_mog2 = cv2.morphologyEx(fgmask_mog2, cv2.MORPH_OPEN, kernel)
    fgmask_knn = cv2.morphologyEx(fgmask_knn, cv2.MORPH_OPEN, kernel)
    
    b = np.zeros(fgmask_mog2.shape[:2], dtype = "uint8")
    r = np.zeros(fgmask_mog2.shape[:2], dtype = "uint8")
    
    fgmask_mog2_rgb = cv2.merge([b, fgmask_mog2, r])
    fgmask_knn_rgb = cv2.merge([b, fgmask_knn, r])
    
    binImg_mog2 = posprocess(fgmask_mog2)
    binImg_knn = posprocess(fgmask_knn)
    #cv2.imshow("fgbg_posprocess", imutils.resize(fgmask, width=displayResize))
    b = np.zeros(binImg_mog2.shape[:2], dtype = "uint8")
    r = np.zeros(binImg_mog2.shape[:2], dtype = "uint8")
    binImg_mog2_rgb = cv2.merge([b, binImg_mog2, r])
    binImg_knn_rgb = cv2.merge([b, binImg_knn, r])
    #cv2.imshow("3 Channels", imutils.resize(merged, width=displayResize))
    cnts_mog2 = findContours(binImg_mog2)
    cnts_knn = findContours(binImg_knn)
    QttyOfContours = 0
    minArea = 6000
    frame1 = frame.copy()
    frame2 = frame.copy()
    for c in cnts_mog2:
        #if a contour has small area, it'll be ignored
        if cv2.contourArea(c) < minArea:
            continue
        QttyOfContours = QttyOfContours+1    
        #draw an rectangle "around" the object
        (x, y, w, h) = cv2.boundingRect(c)
        cv2.rectangle(frame1, (x, y), (x + w, y + h), (0,0,255), 2)
        cv2.rectangle(fgmask_mog2_rgb, (x, y), (x + w, y + h), (0, 0, 255), 2)
        cv2.rectangle(binImg_mog2_rgb, (x, y), (x + w, y + h), (0, 0, 255), 2)
    
    for c in cnts_knn:
        #if a contour has small area, it'll be ignored
        if cv2.contourArea(c) < minArea:
            continue
        QttyOfContours = QttyOfContours+1    
        #draw an rectangle "around" the object
        (x, y, w, h) = cv2.boundingRect(c)
        cv2.rectangle(frame2, (x, y), (x + w, y + h), (0,255,0), 2)
        cv2.rectangle(fgmask_knn_rgb, (x, y), (x + w, y + h), (0, 255, 0), 2)
        cv2.rectangle(binImg_knn_rgb, (x, y), (x + w, y + h), (0, 255, 0), 2)
    
    
    combined1 = np.hstack((frame1, fgmask_mog2_rgb))
    combined2 = np.hstack((frame2, fgmask_knn_rgb))
    combined = np.vstack((combined1, combined2))
    
    cv2.imshow("Combined", imutils.resize(combined, width=1000))
    k = cv2.waitKey(1) & 0xff
    if k == 27:
        break


video.release()
cv2.destroyAllWindows()