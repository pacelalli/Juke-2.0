
// -- MOTEUR 1 -- 
int EN1=9; //Connecté à Arduino pin 9 (sortie PWM) 
int IN1=4; //Connecté à Arduino pin 4 
int IN2=5; //Connecté à Arduino pin 5 

// -- MOTEUR 2 -- 
int EN2=10; //Connecté à Arduino pin 10 (Sortie PWM) 
int IN3=3; //Connecté à Arduino pin 3
int IN4=2; //Connecté à Arduino pin 2 

// -- MOTEUR 3 --
int EN3=11; //Connecté à Arduino pin 11 (Sortie PWM)
int IN5=6; //Connecté à Arduino pin 6
int IN6=7; //Connecté à Arduino pin 7

// -- SERVOMOTEUR 1 --

// -- SERVOMOTEUR 2 -- 








//STOP
void stope(){

  //Moteur 1 arrêt
  analogWrite(EN1,0);
  //Moteur 2 arrêt
  analogWrite(EN2,0);
  //Moteur 3 arrêt
  analogWrite(EN3,0);}

//ROTATION VERS LA DROITE 
void rotationDroite(int vitesse){
  
  // Direction du Moteur 1 normale
  digitalWrite(IN1,LOW); 
  digitalWrite(IN2,HIGH); 
  // Direction du Moteur 2 normale
  digitalWrite(IN3,LOW); 
  digitalWrite(IN4,HIGH); 
  // Direction du Moteur 3 normale
  digitalWrite(IN5,LOW); 
  digitalWrite(IN6,HIGH); 
  
  
  //Moteur 1 - vitesse de rotation choisie (le robot tourne sur lui-même)
  analogWrite(EN1,vitesse);
  //Moteur 2 - vitesse de rotation choisise 
  analogWrite(EN2,vitesse);
  //Moteur 3 - vitesse de rotation choisise 
  analogWrite(EN3,vitesse);}
  
//ROTATION VERS LA GAUCHE
void rotationGauche(int vitesse){
  
  // Direction du Moteur 1 inverse
  digitalWrite(IN1,HIGH); 
  digitalWrite(IN2,LOW);  
  // Direction du Moteur 2 inverse
  digitalWrite(IN3,HIGH); 
  digitalWrite(IN4,LOW); 
  // Direction du Moteur 3 inverse
  digitalWrite(IN5,HIGH); 
  digitalWrite(IN6,LOW); 
  
  //Moteur 1 - vitesse de rotation choisie (le robot tourne sur lui-même)
  analogWrite(EN1,vitesse);
  //Moteur 2 - vitesse de rotation choisise 
  analogWrite(EN2,vitesse);
  //Moteur 3 - vitesse de rotation choisise 
  analogWrite(EN3,vitesse);}

//DEPLACEMENTS
void deplacements(int vitesse, int num){
  
//1
if (num==1){
  //On coupe le moteur 1
  analogWrite(EN1,0);

  // Direction du Moteur 2 
  digitalWrite(IN3,LOW); 
  digitalWrite(IN4,HIGH);
  // Direction du Moteur 3 
  digitalWrite(IN5,HIGH); 
  digitalWrite(IN6,LOW);  

  //Moteurs tournent
  analogWrite(EN2,vitesse);
  analogWrite(EN3,vitesse);}

  //2
if (num==2){
  //On coupe le moteur 3
  analogWrite(EN3,0);

  // Direction du Moteur 2 
  digitalWrite(IN3,LOW); 
  digitalWrite(IN4,HIGH);
  // Direction du Moteur 1 
  digitalWrite(IN1,HIGH); 
  digitalWrite(IN2,LOW);  

  //Moteurs tournent
  analogWrite(EN2,vitesse);
  analogWrite(EN1,vitesse);}

  //3
if (num==3){
  //On coupe le moteur 2
  analogWrite(EN2,0);

  // Direction du Moteur 3 
  digitalWrite(IN5,LOW); 
  digitalWrite(IN6,HIGH);
  // Direction du Moteur 1 
  digitalWrite(IN1,HIGH); 
  digitalWrite(IN2,LOW);  

  //Moteurs tournent
  analogWrite(EN3,vitesse);
  analogWrite(EN1,vitesse);}

  //4
if (num==4){
  //On coupe le moteur 1
  analogWrite(EN1,0);

  // Direction du Moteur 3 
  digitalWrite(IN5,LOW); 
  digitalWrite(IN6,HIGH);
  // Direction du Moteur 2 
  digitalWrite(IN3,HIGH); 
  digitalWrite(IN4,LOW);  

  //Moteurs tournent
  analogWrite(EN2,vitesse);
  analogWrite(EN3,vitesse);}

  //5
if (num==5){
  //On coupe le moteur 3
  analogWrite(EN3,0);

  // Direction du Moteur 2 
  digitalWrite(IN3,HIGH); 
  digitalWrite(IN4,LOW);
  // Direction du Moteur 1 
  digitalWrite(IN1,LOW); 
  digitalWrite(IN2,HIGH);  

  //Moteurs tournent
  analogWrite(EN2,vitesse);
  analogWrite(EN1,vitesse);}

  //6
if (num==6){
  //On coupe le moteur 2
  analogWrite(EN3,0);

  // Direction du Moteur 3 
  digitalWrite(IN5,HIGH); 
  digitalWrite(IN6,LOW);
  // Direction du Moteur 1 
  digitalWrite(IN1,LOW); 
  digitalWrite(IN2,HIGH);  

  //Moteurs tournent
  analogWrite(EN3,vitesse);
  analogWrite(EN1,vitesse);}
}
  
void setup() { 
pinMode(EN1,OUTPUT); // Configurer les broches comme sortie
pinMode(EN2,OUTPUT);
pinMode(EN3,OUTPUT);
pinMode(IN1,OUTPUT); 
pinMode(IN2,OUTPUT); 
pinMode(IN3,OUTPUT); 
pinMode(IN4,OUTPUT);
pinMode(IN5,OUTPUT); 
pinMode(IN6,OUTPUT);
}
void loop() { 

// Moteur 1 - Plein régime:
//analogWrite(EN1,255);
// Moteur 2 - Plein régime:
//analogWrite(EN2,255);
// Moteur 3 - Plein régime:
//analogWrite(EN3,255);

//rotationDroite(255);
//rotationGauche(255);

deplacements(255,1);
delay(2000);
deplacements(255,2);
delay(2000);
rotationDroite(255);
delay(2000);
}
  
  
