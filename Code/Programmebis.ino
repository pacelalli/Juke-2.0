#include <Adafruit_NeoPixel.h>
#include <SoftwareSerial.h>
 
// Parameter 32 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
int X=54;
static int8_t Send_buf[8] = {0} ;//The MP3 player undestands orders in a 8 int string

#define RX 33

#define TX 32
Adafruit_NeoPixel strip = Adafruit_NeoPixel(X, 26, NEO_GRB + NEO_KHZ800);
SoftwareSerial mySerial(RX,TX);


#define NEXT_SONG 0X01 
#define PREV_SONG 0X02 
#define CMD_PLAY_W_INDEX 0X03 //DATA IS REQUIRED (number of song)
#define VOLUME_UP_ONE 0X04
#define VOLUME_DOWN_ONE 0X05
#define CMD_SET_VOLUME 0X06//DATA IS REQUIRED (number of volume from 0 up to 30(0x1E))
#define SET_DAC 0X17
#define CMD_PLAY_WITHVOLUME 0X22 //data is needed  0x7E 06 22 00 xx yy EF;(xx volume)(yy number of song)
#define CMD_SEL_DEV 0X09 //SELECT STORAGE DEVICE, DATA IS REQUIRED
#define DEV_TF 0X02 //HELLO,IM THE DATA REQUIRED
#define SLEEP_MODE_START 0X0A
#define SLEEP_MODE_WAKEUP 0X0B
#define CMD_RESET 0X0C//CHIP RESET
#define CMD_PLAY 0X0D //RESUME PLAYBACK
#define CMD_PAUSE 0X0E //PLAYBACK IS PAUSED
#define CMD_PLAY_WITHFOLDER 0X0F//DATA IS NEEDED, 0x7E 06 0F 00 01 02 EF;(play the song with the directory \01\002xxxxxx.mp3
#define STOP_PLAY 0X16
#define PLAY_FOLDER 0X17// data is needed 0x7E 06 17 00 01 XX EF;(play the 01 folder)(value xx we dont care)
#define SET_CYCLEPLAY 0X19//data is needed 00 start; 01 close
#define SET_DAC 0X17//data is needed 00 start DAC OUTPUT;01 DAC no output
#define SINGLE_PLAY 0X08//Single play(without folder)

//Parameters
const int clkPin   = 22;
const int dtPin   = 24;
const int swPin   = 27;

//Variables
int rotVal  = 0;
int i =0;
bool clkState   = LOW;
bool clkLast  = HIGH;
bool swState  = HIGH;
bool swLast   = HIGH;
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

//Init Serial USB
  Serial.begin(9600);
  Serial.println(F("Initialize System"));
  //Init Rotary
  pinMode(clkPin,INPUT);
  pinMode(dtPin,INPUT);
  pinMode(swPin,INPUT_PULLUP);

  strip.begin();
  strip.show(); // Initialise toute les led à 'off'


  
   mySerial.begin(9600);//Start our Serial coms for our serial monitor!

  delay(500);//Wait chip initialization is complete

  sendCommand(CMD_SEL_DEV, DEV_TF);//select the TF card  

  delay(200);
}

void loop() {
  
  readRotary();
  strip.setPixelColor(rotVal,0,0,233);
  i=rotVal;
  
  strip.setPixelColor(rotVal+1,0,0,0); 
  strip.setPixelColor(rotVal-1,0,0,0); 
  strip.setPixelColor(rotVal+10,0,0,0); 
  strip.setPixelColor(rotVal-10,0,0,0);
  if (swState == LOW){
    strip.setPixelColor(rotVal,233,0,0);
    strip.show();
    
    sendCommand(SINGLE_PLAY, 0X0+rotVal+1);//Premier chanson sans repertoire
    choregraphies(rotVal+1);
    
  }
  strip.show();  
}

void readRotary( ) { /* function readRotary */
  ////Test routine for Rotary
  // gestion position
  clkState = digitalRead(clkPin);
  if ((clkLast == LOW) && (clkState == HIGH)) {//rotary moving
      Serial.print("Rotary position ");
      if (digitalRead(dtPin) == HIGH) {
          rotVal = rotVal - 1;
          if ( rotVal < 0 ) {
              rotVal = 10;
          }
      }
      else {
          rotVal++;
          if ( rotVal > 10 ) {
              rotVal = 0;
          }
      }
      Serial.println(rotVal);
      delay(200);
  }
  clkLast = clkState;
  //gestion bouton
  swState = digitalRead(swPin);
  if (swState == LOW && swLast == HIGH) {
      Serial.println("Rotary pressed");
      delay(100);//debounce
  }
  swLast = swState;
}

void sendCommand(int8_t command, int16_t dat) {

  delay(20);

  Send_buf[0] = 0x7e; //starting byte

  Send_buf[1] = 0xff; //version

  Send_buf[2] = 0x06; //the number of bytes of the command without starting byte and ending byte

  Send_buf[3] = command; //

  Send_buf[4] = 0x00;//0x00 = no feedback, 0x01 = feedback

  Send_buf[5] = (int8_t)(dat >> 8);//datah

  Send_buf[6] = (int8_t)(dat); //datal

  Send_buf[7] = 0xef; //ending byte

  for(uint8_t i=0; i<8; i++){

    mySerial.write(Send_buf[i]) ;
}
}

void choregraphies (int num){

  //TOUT EN GUCCI
  if (num==1){
    rotationDroite(255);
    delay(5000);
  }

  //ASALTO
  if (num==2){
    rotationGauche(255);
    delay(5000);
  }
}
