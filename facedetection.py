# -*- coding: utf-8 -*-
"""
Created on Wed Jul 31 19:30:47 2019

@author: ISM
"""

import cv2
import numpy as np

face_cascade = cv2.CascadeClassifier("D:\Aface\haarcascade_frontalface_default.xml")

eye_cascade = cv2.CascadeClassifier("D:\Aface\haarcascade_eye.xml")


cap = cv2.VideoCapture(0)
#cv2.namedWindow('img')
#cv2.resizeWindow('img',600,600)

while True:
    ret, img = cap.read()
    gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
    faces = face_cascade.detectMultiScale(gray, 1.3, 5)
    for (x,y,w,h) in faces:
        cv2.rectangle(img,(x,y),(x+w,y+h),(255,0,0),2)
        roi_gray = gray[y:y+h, x:x+w]
        roi_color = img[y:y+h, x:x+w]
        eyes = eye_cascade.detectMultiScale(roi_gray)
        for (ex,ey,ew,eh) in eyes:
            cv2.rectangle(roi_color, (ex, ey), (ex+ew,ey+eh), (0,255,0), 2)
    cv2.imshow('img' , img)
    if cv2.waitKey(30) & 0xFF == ord('q'):
        break
    
cap.release()
cv2.destroyAllWindows()