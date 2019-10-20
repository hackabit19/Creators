# Creators
Idea is to develop an automatic target shooter where, gun points to a specified object and shoots it.

There will be 24 hours surveillance through cameras. Two cameras will be installed for viewing a stereoscopic pair of separate images, depicting left-eye and right-eye views of the same scene, as a single three-dimensional image, using Computer Vision.
When the images of the specified objects will be captured by the cameras, in their field view, the gun will adjust its position, aiming at the target. Automatic trigger mechanism will be used to shoot at the targeted object.
A classifier will be built to classify the specific type of objects such as if the object is a particular person then, whenever that person appears in the field view of the cameras, that person will be shot.
Arduino IDE(Arduino Uno board) and PySerial will be used to drive the motors which will be used for positioning the gun.  

The python file(facedetection.py) is detecting the frontal face of the human using haarcascade classifier. 
By the use of pyserial communication is established between python file(facedetection.py) and file containing arduino code(targetshooter.ino)
The .ino file contains the arduino code for driving the motors which will automatise the movement of the gun.
