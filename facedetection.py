# -*- coding: utf-8 -*-
"""
Created on Wed Jul 31 19:30:47 2019

@author: ISM
"""

import cv2
import numpy as np
import serial

face_cascade = cv2.CascadeClassifier("F://haarcascade_frontalface_default.xml")

ser = serial.Serial('COM5',9600)
focalLength = 3.85
baseline = 60

#capturing the video images
cap = cv2.VideoCapture(1)
cap2 = cv2.VideoCapture(2)

while True:
    ret, img = cap.read()
    gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)                #converting the image to gray_image
    gray2 = cv2.cvtColor(img2,cv2.COLOR_BGR2GRAY)
    faces = face_cascade.detectMultiScale(gray, 1.3, 5)         #using haarcascade classifier to detect the frontal face  
    for (x,y,w,h) in faces:                                     #making a rectangle around the frontal face
        cv2.rectangle(img,(x,y),(x+w,y+h),(255,0,0),2)          
        roi_gray = gray[y:y+h, x:x+w]
        roi_color = img[y:y+h, x:x+w]
        
        #finding the centroid of the detected face
        cX = x + int(w/2)
        cY = y + int(h/2)
            
        cv2.circle(img, (cX, cY), 5, (255, 255, 255), -1)
        cv2.putText(img, "centroid", (cX - 25, cY - 25),cv2.FONT_HERSHEY_SIMPLEX, 0.5, (255, 255, 255), 2)
            
        #calculating the disparity map
        stereo = cv2.StereoBM_create(numDisparities=128, blockSize=15)
        disparity = stereo.compute(gray,gray2)
        
        #Calculating the depth map using disparity
        #converting disparity into mm 
        
        depth = (focalLength * baseline) / (disparity*0.264)
        print(cX)
        print(cY)
        print(-disparity)
        cX=(int)(cX/480)                #Scaling the centroid co-ordinates
        cY=(int)(cY/480)
        print(-depth[cX,cY])
        ser.write(cX)
        ser.write(cY)
        ser.write(depth)
    cv2.imshow('img' , img)
    if cv2.waitKey(30) & 0xFF == ord('q'):
        break
    
cap.release()
cv2.destroyAllWindows()
