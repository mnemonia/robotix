#include <Wire.h>
#include <SPI.h>
#include <Adafruit_CAP1188.h>

// Reset Pin is used for I2C or SPI
#define CAP1188_RESET  9
Adafruit_CAP1188 cap = Adafruit_CAP1188();
#define CAP_AUDIO_PLUS 0
#define CAP_AUDIO_MINUS 1
#define CAP_AUDIO_ON_OFF 2
#define CAP_LIGHT_PLUS 3
#define CAP_LIGHT_MINUS 4
#define CAP_LIGHT_ON_OFF 5
 
// 0x4B is the default i2c address
#define MAX9744_I2CADDR 0x4B

// We'll track the volume level in this variable.
int8_t thevol = 31;
int lightDimValue = 31;
#define LIGHT_DIM_STEP 5
#define LIGHT_DIM_DELAY 50

#define LIGHT_PIN 6

void setup() {
  Serial.begin(9600);
  Serial.println("MAX9744 demo");
  Wire.begin();
  
  setupCapSensor();  
  setupAmplifier();
  setupLight();
}

void setupAmplifier(){
  if (! setvolume(thevol)) {
    Serial.println("Failed to set volume, MAX9744 not found!");
    while (1);
  }
} 
void setupCapSensor(){
  if (!cap.begin()) {
    Serial.println("CAP1188 not found");
    while (1);
  }
  Serial.println("CAP1188 found!");
}
void setupLight(){
  pinMode(LIGHT_PIN, OUTPUT);
} 
// Setting the volume is very simple! Just write the 6-bit
// volume to the i2c bus. That's it!
boolean setvolume(int8_t v) {
  // cant be higher than 63 or lower than 0
  if (v > 63) v = 63;
  if (v < 0) v = 0;
  
  Serial.print("Setting volume to ");
  Serial.println(v);
  Wire.beginTransmission(MAX9744_I2CADDR);
  Wire.write(v);
  if (Wire.endTransmission() == 0) 
    return true;
  else
    return false;
}

int8_t checkAmplifierTouchControls(){
  uint8_t touched = cap.touched();

  if (touched == 0) {
    // No touch detected
    return -1;
  }
  
  if(touched & (1 << CAP_AUDIO_PLUS)){
    Serial.println("Audio +");
    thevol++;
    return thevol;
  }
  if(touched & (1 << CAP_AUDIO_MINUS)){
    Serial.println("Audio -");
    thevol--;
    return thevol;
  }
  return -1;
}

int checkLightTouchControls(){
  uint8_t touched = cap.touched();
  if (touched == 0) {
    // No touch detected
    return -1;
  }
Serial.println("Light touched");
  
  if(touched & (1 << CAP_LIGHT_PLUS)){
    Serial.print("Light + ");
    incBrightness();
    Serial.println(lightDimValue);
    return lightDimValue;
  }
  if(touched & (1 << CAP_LIGHT_MINUS)){
    Serial.print("Light - ");
    decBrightness();
    Serial.println(lightDimValue);
    return lightDimValue;
  }
  return -1;
}

void incBrightness(){
  lightDimValue += LIGHT_DIM_STEP;
  if(lightDimValue >= 255){
    lightDimValue = 255;
  }
}

void decBrightness(){
  lightDimValue -= LIGHT_DIM_STEP;
  if(lightDimValue <= 0){
    lightDimValue = 0;
  }
}

void handleAmplifierCommand(int8_t volume){
  if (volume > 63) volume = 63;
  if (volume < 0) volume = 0;
 
  setvolume(volume);
}

// Read in + and - characters to set the volume.
void loop() {
  int8_t volume = checkAmplifierTouchControls();
  if(volume >= 0){
    handleAmplifierCommand(volume);
    delay(80);
  }
  
  int brightness = checkLightTouchControls();
  if(brightness >= 0){
    dimLight(brightness);
    delay(LIGHT_DIM_DELAY);
  }
  
  delay(50);
}

void dimLight(int8_t brightness){
  analogWrite(LIGHT_PIN, brightness);
}

