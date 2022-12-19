/*
   Code 23 - Edurobot.ch, destiné à l'Arduino
   Objectif : Faire bouger le bras d'un servomoteur dans un sens puis dans l'autre, indéfiniment
*/

//*****EN-TÊTE DECLARATIF*****
#include <Servo.h>  // on inclut la bibliothèque pour piloter un servomoteur

Servo monServo;  // on crée l'objet monServo

void setup()
{
    monServo.attach(9); // on définit le Pin utilisé par le servomoteur
}

void loop()
{
    /*for (int position = 0; position <=180; position ++){ // on crée une variable position qui prend des valeurs entre 0 à 180 degrés
        monServo.write(position);  // le bras du servomoteur prend la position de la variable position
        delay(20);  // on attend 15 millisecondes
    }    }
*/
  int position =0;
  
  monServo.write(position);
  position=90;
  monServo.write(position);
  position =180;
  monServo.write(position);
  position=270;
  monServo.write(position);
}
