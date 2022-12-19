#include <Adafruit_NeoPixel.h>
 
// Parameter 32 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
int X=54;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(X, 6, NEO_GRB + NEO_KHZ800);





//Parameters
const int clkPin   = 2;
const int dtPin   = 4;
const int swPin   = 7;
//Variables
int rotVal  = 0;
int i =0;
bool clkState   = LOW;
bool clkLast  = HIGH;
bool swState  = HIGH;
bool swLast   = HIGH;
void setup() {
  //Init Serial USB
  Serial.begin(9600);
  Serial.println(F("Initialize System"));
  //Init Rotary
  pinMode(clkPin,INPUT);
  pinMode(dtPin,INPUT);
  pinMode(swPin,INPUT_PULLUP);

  strip.begin();
  strip.show(); // Initialise toute les led à 'off'
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
