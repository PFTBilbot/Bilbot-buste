#include <Servo.h>

Servo gauche_droite;
Servo avant_arriere;
Servo rotation_tete;
Servo yeux_GD;
Servo yeux_HB;
Servo bouche;

//POSITIONS DE BASE

int position_DG = 90;
int position_AvAr = 90;
int position_rot = 90;
int position_yeux_GD = 90;
int position_yeux_HB = 90;
int position_bouche = 90;

//FLEXION DU COU

int limite_gauche = 50;
int limite_droite = 130;

int limite_avant = 160;
int limite_arriere = 50;

int limite_rotation_gauche = 0;
int limite_rotation_droite = 180;

//DEPLACEMENT DES YEUX

int limite_yeux_gauche = 125;
int limite_yeux_droite = 55;
int limite_yeux_haut = 120;
int limite_yeux_bas = 60;

//DEPLACEMENT DE LA BOUCHE

int limite_ouverture_bouche = 80;
int limite_fermeture_bouche = 100;

//VARIABLES DE DONNEES

char c;
String trame;
String ordre;
String angle;
char commandeServo;
int angleInt;

//Exemple de trame : A102Z
// A : Commande du Servo A
// 102 : Angle voulu
// Z : Fin de la trame

//CORRESPONDANCES DE LA TRAME :
// A = Flexion cou gauche droite
// B = Flexion cou avant arriere
// C = Rotation du cou
// D = Deplacement yeux haut bas
// E = Deplacement yeux gauche droite
// F = Ouverture fermeture bouche

void setup() {
    
    //Communication avec la Raspberry Pi
    Serial.begin(9600);

    //Creation des instances des servos
    yeux_GD.attach(4);
    yeux_HB.attach(5);
    bouche.attach(3);
    gauche_droite.attach(2);
    avant_arriere.attach(7);
    rotation_tete.attach(6);
    
}

void loop() {

  //RECUPERATION DE LA TRAME
  if (Serial.available()>0){
      c = Serial.read();
      if (c != 'Z'){
      trame = trame + c;
      }
      //CONVERSION EN DONNEES UTILES
      else {
        commandeServo = trame[0];
        angle = "";
        angle += trame[1];
        angle += trame[2];
        angle += trame[3];
        angleInt = angle.toInt();
        trame = "";
      }
  }

  //DEBUT
  if (commandeServo == 'A'){
    if (angleInt < limite_gauche){
      gauche_droite.write(limite_gauche);
    }
    if (angleInt > limite_droite){
      gauche_droite.write(limite_droite);
    }
    else{
    gauche_droite.write(angleInt);
    }
  }
  //FIN

  //DEBUT
  if (commandeServo == 'B'){
    if (angleInt < limite_arriere){
      avant_arriere.write(limite_arriere);
    }
    if (angleInt > limite_avant){
      avant_arriere.write(limite_avant);
    }
    else{
    avant_arriere.write(angleInt);
    }
  }
  //FIN

  //DEBUT
  if (commandeServo == 'C'){
    if (angleInt < limite_rotation_gauche){
      rotation_tete.write(limite_rotation_gauche);
    }
    if (angleInt > limite_rotation_droite){
      rotation_tete.write(limite_rotation_droite);
    }
    else{
    rotation_tete.write(angleInt);
    }
  }
  //FIN

  //DEBUT
  if (commandeServo == 'D'){
    if (angleInt < limite_yeux_droite){
      yeux_GD.write(limite_yeux_droite);
    }
    if (angleInt > limite_yeux_gauche){
      yeux_GD.write(limite_yeux_gauche);
    }
    else{
    yeux_GD.write(angleInt);
    }
  }
  //FIN

  //DEBUT
  if (commandeServo == 'E'){
    if (angleInt < limite_yeux_bas){
      yeux_HB.write(limite_yeux_bas);
    }
    if (angleInt > limite_yeux_haut){
      yeux_HB.write(limite_yeux_haut);
    }
    else{
    yeux_HB.write(angleInt);
    }
  }
  //FIN

  //DEBUT
  if (commandeServo == 'F'){
    if (angleInt < limite_ouverture_bouche){
      bouche.write(limite_ouverture_bouche);
    }
    if (angleInt > limite_fermeture_bouche){
      bouche.write(limite_fermeture_bouche);
    }
    else{
    bouche.write(angleInt);
    }
  }
  //FIN
}
