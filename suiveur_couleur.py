import cv2
import numpy as np
import imutils
import RPi.GPIO as GPIO
import time
import serial

#Liste des servos

Flexion_cou_GD = 'A'
Flexion_cou_Av_Ar = 'B'
Rotation_cou = 'C'
Deplacement_yeux_HB = 'E'
Deplacement_yeux_GD = 'D'
Bouche = 'F'

#FLEXION DU COU

limite_gauche = 50
limite_droite = 130

limite_avant = 160
limite_arriere = 50

limite_rotation_gauche = 0
limite_rotation_droite = 180

#DEPLACEMENT DES YEUX

limite_yeux_gauche = 125
limite_yeux_droite = 55
limite_yeux_haut = 100
limite_yeux_bas = 80

#Angles de départ
angle_x_yeux = 90
angle_y_yeux = 90

angle_x_tete = 90
angle_y_tete = 90

min_y_atteint = False
max_y_atteint = False

min_x_atteint = False
max_x_atteint = False

#Capture video
cap= cv2.VideoCapture(0)
cap.set(3,640)
cap.set(4,480)

#Dimensions de la fenetre
largueur = 640
hauteur = 480

#Precision toleree
precision = 60
decalage = 120

with serial.Serial("/dev/ttyACM0", 9600, timeout=1) as arduino:
    while True:
         #Retour video
         _,frame= cap.read()
         #Redimensionnement de l'image
         resized = cv2.resize(frame, (largueur, hauteur))
         #Modification des couleurs de l'image en HSV
         hsv = cv2.cvtColor(resized, cv2.COLOR_BGR2HSV)
        
         #Bornes du rouge d'une boite Raspberry
         lower_red = np.array([0, 200, 125])
         upper_red = np.array([179, 255, 230])
         
         #Application du masque
         mask = cv2.inRange(hsv,lower_red,upper_red)

         #Detection des contours
         cnts = cv2.findContours(mask, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)
         cnts = imutils.grab_contours(cnts)

         for c in cnts:
             area = cv2.contourArea(c) #Aire des contours
             if area > 2000: #Application d'un filtre pour ne garder que les gros contours
                 
                 #Afficahge des contours
                 cv2.drawContours(resized,[c],-1,(0,255,0), 3)
                 
                 #Recuperation du centre du contour
                 M = cv2.moments(c)
                 cx = int(M["m10"]/ M["m00"])
                 cy = int(M["m01"]/ M["m00"])
                 
                 #tracage d'un cercle au centre du contours
                 cv2.circle(resized,(cx,cy),7,(255,255,255),-1)
                 
                 #Determination de la direction dans laquelle faire tourner les servos pour suivre le contours
                 min_x_atteint = False
                 if cx > (largueur+precision)/2:
                    angle_x_tete = angle_x_tete - 1
                    if angle_x_tete < limite_gauche:
                        angle_x_tete = limite_gauche
                        min_x_atteint = True
                    else:
                        angle_x_yeux = 90
                 
                 max_x_atteint = False
                 if cx < (largueur-precision)/2:
                    angle_x_tete = angle_x_tete + 1
                    if angle_x_tete > limite_droite:
                        angle_x_tete = limite_droite
                        max_x_atteint = True
                    else:
                        angle_x_yeux = 90
                 
                 if min_x_atteint == True:
                     angle_x_yeux = angle_x_yeux - 1
                     if angle_x_yeux < limite_yeux_droite:
                        angle_x_yeux = limite_yeux_droite
                        
                 if max_x_atteint == True:
                     angle_x_yeux = angle_x_yeux + 1
                     if angle_x_yeux > limite_yeux_gauche:
                        angle_x_yeux = limite_yeux_gauche
                 
                 commande = Deplacement_yeux_GD + str(angle_x_yeux) + 'Z'
                 print(commande)
                    
                 arduino.write(commande.encode())
                 
                 commande = Rotation_cou + str(angle_x_tete) + 'Z'
                 print(commande)
                    
                 arduino.write(commande.encode())
                
                 min_y_atteint = False
                 if cy > (hauteur+precision)/2:
                    angle_y_tete = angle_y_tete - 1
                    if angle_y_tete < limite_arriere:
                        angle_y_tete = limite_arriere
                        min_y_atteint = True
                    else:
                        angle_y_yeux = 90
                
                 max_y_atteint = False
                 if cy < (hauteur-precision)/2:
                    angle_y_tete = angle_y_tete + 1
                    if angle_y_tete > limite_avant:
                        angle_y_tete = limite_avant
                        max_y_atteint = True
                    else:
                        angle_y_yeux = 90
                
                 if min_y_atteint == True:
                     angle_y_yeux = angle_y_yeux - 1
                     if angle_y_yeux < limite_yeux_bas:
                        angle_y_yeux = limite_yeux_bas
                        
                 if max_y_atteint == True:
                     angle_y_yeux = angle_y_yeux + 1
                     if angle_y_yeux > limite_yeux_haut:
                        angle_y_yeux = limite_yeux_haut
                     
                 
                 commande = Deplacement_yeux_HB + str(angle_y_yeux) + 'Z'
                 print(commande)
                 
                 arduino.write(commande.encode())
                 
                 commande = Flexion_cou_Av_Ar + str(angle_y_tete) + 'Z'
                 print(commande)
                    
                 arduino.write(commande.encode())

         #Affichage de la video
         cv2.imshow('Video', resized)
        
         #Si l'utilisateur appui sur echap le programme se coupe
         k = cv2.waitKey(5)
         if k == 27:
             break
            
    #Destruction des fenetres
    cv2.destroyAllWindows()
