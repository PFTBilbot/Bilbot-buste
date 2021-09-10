#include <Servo.h>
#include <SoftwareSerial.h>

SoftwareSerial hc05(10 ,11);

Servo gauche_droite;
Servo avant_arriere;
Servo rotation_tete;
Servo yeux;
Servo yeux_HB;
Servo bouche;

int position_GD = 90;
int position_AA = 90;
int position_rot = 90;
int position_yeux = 90;
int position_yeux_HB = 90;
int position_bouche = 90;

int limite_gauche = 50;
int limite_droite = 130;

int limite_avant = 140;
int limite_arriere = 50;

int limite_rotation_gauche = 0;
int limite_rotation_droite = 180;

int limite_yeux_gauche = 125;
int limite_yeux_droite = 55;
int limite_yeux_haut = 120;
int limite_yeux_bas = 60;

int limite_ouverture_bouche = 80;
int limite_fermeture_bouche = 100;


char c;

void setup()
{   
    Serial.begin(9600);
    hc05.begin(9600);
    yeux.attach(4);
    yeux_HB.attach(5);
    bouche.attach(3);
    gauche_droite.attach(2);
    avant_arriere.attach(7);
    rotation_tete.attach(6);
    
}

void loop()
{     
  if (hc05.available()>0){
      c = hc05.read();}
      Serial.println(c);

      //flexion GD
      if (c == 'C'){
        Serial.println("gauche");
        position_GD = position_GD - 1;
        if (position_GD < limite_gauche){
          position_GD = limite_gauche;
        }
        gauche_droite.write(position_GD);
      }
  
      if (c == 'D'){
        Serial.println("droite");
        position_GD = position_GD + 1;
        if (position_GD > limite_droite){
          position_GD = limite_droite;
        }
        gauche_droite.write(position_GD);
        delay(15);
      }

      //flexion AV AR
      if (c == 'A'){
        Serial.println("arriere");
        position_AA = position_AA - 1;
        if (position_AA < limite_arriere){
          position_AA = limite_arriere;
        }
        avant_arriere.write(position_AA);
        delay(15);
      }
  
      if (c == 'B'){
        Serial.println("avant");
        position_AA = position_AA + 1;
        if (position_AA > limite_avant){
          position_AA = limite_avant;
        }
        avant_arriere.write(position_AA);
        delay(15);
      }

      //rotation tete
      if (c == 'E'){
        Serial.println("gauche tete");
        position_rot = position_rot - 1;
        if (position_rot < limite_rotation_gauche){
          position_rot = limite_rotation_gauche;
        }
        rotation_tete.write(position_rot);
        delay(15);
      }
  
      if (c == 'F'){
        Serial.println("droite tete");
        position_rot = position_rot + 1;
        if (position_rot > limite_rotation_droite){
          position_rot = limite_rotation_droite;
        }
        rotation_tete.write(position_rot);
        delay(15);
      }

      //yeux GD
      if (c == 'I'){
        Serial.println("droite yeux");
        position_yeux = position_yeux - 1;
        if (position_yeux < limite_yeux_droite){
          position_yeux = limite_yeux_droite;
        }
        yeux.write(position_yeux);
        delay(15);
      }
  
      if (c == 'H'){
        Serial.println("gauche yeux");
        position_yeux = position_yeux + 1;
        if (position_yeux > limite_yeux_gauche){
          position_yeux = limite_yeux_gauche;
        }
        yeux.write(position_yeux);
        delay(15);
      }

      //yeux hb
      if (c == 'G'){
        Serial.println("haut yeux");
        position_yeux_HB = position_yeux_HB - 1;
        if (position_yeux_HB < limite_yeux_bas){
          position_yeux_HB = limite_yeux_bas;
        }
        yeux_HB.write(position_yeux_HB);
        delay(15);
      }
  
      if (c == 'J'){
        Serial.println("bas yeux");
        position_yeux_HB = position_yeux_HB + 1;
        if (position_yeux_HB > limite_yeux_haut){
          position_yeux_HB = limite_yeux_haut;
        }
        yeux_HB.write(position_yeux_HB);
        delay(15);
      }

      //bouche
      if (c == 'K'){
        Serial.println("bouche ouverte");
        position_bouche = position_bouche - 1;
        if (position_bouche < limite_ouverture_bouche){
          position_bouche = limite_ouverture_bouche;
        }
        bouche.write(position_bouche);
        delay(15);
      }
  
      if (c == 'L'){
        Serial.println("bouche fermee");
        position_bouche = position_bouche + 1;
        if (position_bouche > limite_fermeture_bouche){
          position_bouche = limite_fermeture_bouche;
        }
        bouche.write(position_bouche);
        delay(15);
      }
    
}
