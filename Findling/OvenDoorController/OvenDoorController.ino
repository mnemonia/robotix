#include <Adafruit_NeoPixel.h>

const int hallC1 = 5;
const int hallC2 = 8;
const int hallC3 = 11;
const int lightA1 = 3;
const int lightA2 = 6;
const int lightA3 = 9;

int lightStateA1 = LOW;
int lightStateA2 = LOW;
int lightStateA3 = LOW;

boolean isLightOnA1 = false;
boolean isLightOnA2 = false;
boolean isLightOnA3 = false;

Adafruit_NeoPixel pixelA1 = Adafruit_NeoPixel(1, lightA1, NEO_RGB + NEO_KHZ800);
Adafruit_NeoPixel pixelA2 = Adafruit_NeoPixel(1, lightA2, NEO_RGB + NEO_KHZ800);
Adafruit_NeoPixel pixelA3 = Adafruit_NeoPixel(1, lightA3, NEO_RGB + NEO_KHZ800);

void setup() {
  Serial.begin(9600);
  pinMode(hallC1, INPUT);
  pinMode(hallC2, INPUT);
  pinMode(hallC3, INPUT);
  // initialize the pushbutton pin as an input:
  pinMode(lightA1, OUTPUT);
  pinMode(lightA2, OUTPUT);
  pinMode(lightA3, OUTPUT);
  
  pixelA1.begin();
  pixelA2.begin();
  pixelA3.begin();

}

void loop() {
  checkAndSetA1();
  checkAndSetA2();
  checkAndSetA3();  
  delay(25);
}

void checkAndSetA1(){
  // read the state of the pushbutton value:
  lightStateA1 = digitalRead(hallC1);
  // check if the pushbutton is pressed.
  // if it is, the buttonState is HIGH:
  if (lightStateA1 == HIGH) {
    if(!isLightOnA1){
      pixelA1.setPixelColor(0, pixelA1.Color(0,150,0)); // Moderately bright green color.
      pixelA1.show(); // This sends the updated pixel color to the hardware.
      isLightOnA1 = true;      
    }
  }
  else {
    pixelA1.setPixelColor(0, pixelA1.Color(0,0,0)); // Moderately bright green color.
    pixelA1.show(); // This sends the updated pixel color to the hardware.
    isLightOnA1 = false;      
  }
}

void checkAndSetA2(){
  // read the state of the pushbutton value:
  lightStateA2 = digitalRead(hallC2);

  // check if the pushbutton is pressed.
  // if it is, the buttonState is HIGH:
  if (lightStateA2 == HIGH) {
    if(!isLightOnA2){
      pixelA2.setPixelColor(0, pixelA2.Color(0,150,0)); // Moderately bright green color.
      pixelA2.show(); // This sends the updated pixel color to the hardware.
      isLightOnA2 = true;      
    }
  }
  else {
    pixelA2.setPixelColor(0, pixelA2.Color(0,0,0)); // Moderately bright green color.
    pixelA2.show(); // This sends the updated pixel color to the hardware.
    isLightOnA2 = false;      
  }
}

void checkAndSetA3(){
  // read the state of the pushbutton value:
  lightStateA3 = digitalRead(hallC3);
  Serial.print("A3: ");
  Serial.println(lightStateA3);

  // check if the pushbutton is pressed.
  // if it is, the buttonState is HIGH:
  if (lightStateA3 == HIGH) {
    if(!isLightOnA3){
      pixelA3.setPixelColor(0, pixelA3.Color(0,150,0)); // Moderately bright green color.
      pixelA3.show(); // This sends the updated pixel color to the hardware.
      isLightOnA3 = true;      
    }
  }
  else {
    isLightOnA3 = false;      
    pixelA3.setPixelColor(0, pixelA3.Color(0,0,0)); // Moderately bright green color.
    pixelA3.show(); // This sends the updated pixel color to the hardware.
  }
}
