extern "C"{
#include "sTheUnit.h"
}
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
#define CAP_AMBIENT_ON_OFF 6

// 0x4B is the default i2c address
#define MAX9744_I2CADDR 0x4B
// 35 is ok for sound off
#define SOUND_ON_STANDARD_VALUE 30
#define SOUND_OFF_STANDARD_VALUE 0
// 44 is ok for max sound, 63 is max
#define SOUND_MAX_VALUE 40
#define SOUND_DIM_DELAY 80
#define SOUND_ON_OFF_DELAY 1000
#define SOUND_DIM_STEP 2


// We'll track the volume level in this variable.
int8_t thevol = SOUND_OFF_STANDARD_VALUE;
#define LIGHT_ON_STANDARD_VALUE 100
#define LIGHT_OFF_STANDARD_VALUE 0
#define LIGHT_ON_MAX_VALUE 130
int lightDimValue = LIGHT_OFF_STANDARD_VALUE;
int ambientDimValue = LIGHT_OFF_STANDARD_VALUE;
#define LIGHT_DIM_STEP 5
#define LIGHT_DIM_DELAY 50
#define LIGHT_DIM_OFF_DELAY 80
#define LIGHT_ON_OFF_DELAY 1000
#define AMBIENT_DIM_STEP 1
#define AMBIENT_DIM_DELAY 25

#define LIGHT_PIN 6
#define AMBIENT_PIN 5
#define LOUDSPEAKER_ONOFF_PIN 4
#define LOUDSPEAKER_PLUS_PIN 3
#define LOUDSPEAKER_MINUS_PIN 2

void setup() {
  Serial.begin(9600);
  Serial.println("Starting Findl.ing WorkWithSoundAndLight Controller ...");
  Wire.begin();
  
//  setPwmFrequency(LIGHT_PIN, 1);
  
  setupCapSensor();  
  setupAmplifier();
  setupLoudspeakerSensor();
  setupLight();
  setupStateMachines();  
  Serial.println("Starting Findl.ing WorkWithSoundAndLight Controller DONE");

}
void setupLoudspeakerSensor(){
  pinMode(LOUDSPEAKER_ONOFF_PIN, INPUT);
  pinMode(LOUDSPEAKER_PLUS_PIN, INPUT);
  pinMode(LOUDSPEAKER_MINUS_PIN, INPUT);
}

void setupAmplifier(){
  if (! setvolume(SOUND_OFF_STANDARD_VALUE)) {
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
void dimLight(int8_t brightness){
  analogWrite(LIGHT_PIN, brightness);
}
void dimAmbient(int8_t brightness){
  analogWrite(AMBIENT_PIN, brightness);
}

// Setting the volume is very simple! Just write the 6-bit
// volume to the i2c bus. That's it!
boolean setvolume(int8_t v) {
  // cant be higher than 63 or lower than 0
  if (v > SOUND_MAX_VALUE) v = SOUND_MAX_VALUE;
  if (v < SOUND_OFF_STANDARD_VALUE) v = SOUND_OFF_STANDARD_VALUE;
  
  Serial.print("Setting volume to ");
  Serial.println(v);
  Wire.beginTransmission(MAX9744_I2CADDR);
  Wire.write(v);
  if (Wire.endTransmission() == 0) 
    return true;
  else
    return false;
}


void setupStateMachines(){
  if (fINIT_())
  {
  	/* activation of drive loop */
  }
  else 
  {
  	/* initialization failed, abort drive */
  }
}

void loop() {
  checkAndSetLightControls();
  //checkAndSetAudioControls();
  checkAndSetLoundspeakerControls();  
  //checkAndSetAmbientControls();
  cap.touched();
  delay(50);
}

void checkAndSetLightControls(){
  uint8_t touched = cap.touched();
  if (touched == 0) {
    // No touch detected
    return;
  }
  if(touched & (1 << CAP_LIGHT_PLUS)){
    Serial.println("Light Sense Plus");
    IN_.LightBrightnessIn(C7_PLUS);
  }
  else if(touched & (1 << CAP_LIGHT_MINUS)){
    Serial.println("Light Sense Minus");
    IN_.LightBrightnessIn(C7_MINUS);
  }
  else if(touched & (1 << CAP_LIGHT_ON_OFF)){
    Serial.println("Light Sense ON/OFF");
    IN_.LightSwitchIn(C5_TOGGLE);
  }
}
/*
void checkAndSetAmbientControls(){
  uint8_t touched = cap.touched();
  if (touched == 0) {
    // No touch detected
    return;
  }
  if(touched & (1 << CAP_AMBIENT_ON_OFF)){
    Serial.println("Ambient Sense On/Off");
    IN_.AmbientSwitch(C11_TOGGLE);
  }
}
*/

void checkAndSetAudioControls(){
  uint8_t touched = cap.touched();
  if (touched == 0) {
    // No touch detected
    return;
  }
  if(touched & (1 << CAP_AUDIO_PLUS)){
    Serial.println("Audio Sense Plus");
    IN_.SoundLoudnessIn(C8_PLUS);
  }
  else if(touched & (1 << CAP_AUDIO_MINUS)){
    Serial.println("Audio Sense Minus");
    IN_.SoundLoudnessIn(C8_MINUS);
  }
  else if(touched & (1 << CAP_AUDIO_ON_OFF)){
    Serial.println("Audio Sense ON/OFF");
    IN_.SoundSwitchIn(C6_TOGGLE);
  }
}

void checkAndSetLoundspeakerControls(){
  int touched = digitalRead(LOUDSPEAKER_ONOFF_PIN);
  if (touched == LOW) {
    Serial.println("Loudspeaker Sense ON/OFF");
    IN_.SoundSwitchIn(C6_TOGGLE);
  }else{
    touched = digitalRead(LOUDSPEAKER_MINUS_PIN);    
    if (touched == LOW) {
      Serial.println("Loudspeaker Sense Minus");
      IN_.SoundLoudnessIn(C8_MINUS);
    }else{
      touched = digitalRead(LOUDSPEAKER_PLUS_PIN);    
      if (touched == LOW) {
        Serial.println("Loudspeaker Sense Minus");
        IN_.SoundLoudnessIn(C8_PLUS);
      }
    }
  }
}

void incBrightness(){
  lightDimValue += LIGHT_DIM_STEP;
  if(lightDimValue >= LIGHT_ON_MAX_VALUE){
    lightDimValue = LIGHT_ON_MAX_VALUE;
  }
}

void decBrightness(){
  lightDimValue -= LIGHT_DIM_STEP;
  if(lightDimValue <= 0){
    lightDimValue = 0;
  }
}


void incAmbientBrightness(){
  ambientDimValue += AMBIENT_DIM_STEP;
  if(ambientDimValue >= 255){
    ambientDimValue = 255;
  }
}

void decAmbientBrightness(){
  ambientDimValue -= AMBIENT_DIM_STEP;
  if(ambientDimValue <= 0){
    ambientDimValue = 0;
  }
}


void incLoudness(){
  thevol += SOUND_DIM_STEP;
  if(thevol > SOUND_MAX_VALUE){
    thevol = SOUND_MAX_VALUE;
  }
}

void decLoudness(){
  thevol -= SOUND_DIM_STEP;
  if(thevol <= 0){
    thevol = 0;
  }
}


void handleAmplifierCommand(int8_t volume){
  if (volume > 63) volume = 63;
  if (volume < 0) volume = 0;
 
  setvolume(volume);
}

/**
 * Divides a given PWM pin frequency by a divisor.
 * 
 * The resulting frequency is equal to the base frequency divided by
 * the given divisor:
 *   - Base frequencies:
 *      o The base frequency for pins 3, 9, 10, and 11 is 31250 Hz.
 *      o The base frequency for pins 5 and 6 is 62500 Hz.
 *   - Divisors:
 *      o The divisors available on pins 5, 6, 9 and 10 are: 1, 8, 64,
 *        256, and 1024.
 *      o The divisors available on pins 3 and 11 are: 1, 8, 32, 64,
 *        128, 256, and 1024.
 * 
 * PWM frequencies are tied together in pairs of pins. If one in a
 * pair is changed, the other is also changed to match:
 *   - Pins 5 and 6 are paired on timer0
 *   - Pins 9 and 10 are paired on timer1
 *   - Pins 3 and 11 are paired on timer2
 * 
 * Note that this function will have side effects on anything else
 * that uses timers:
 *   - Changes on pins 3, 5, 6, or 11 may cause the delay() and
 *     millis() functions to stop working. Other timing-related
 *     functions may also be affected.
 *   - Changes on pins 9 or 10 will cause the Servo library to function
 *     incorrectly.
 * 
 * Thanks to macegr of the Arduino forums for his documentation of the
 * PWM frequency divisors. His post can be viewed at:
 *   http://www.arduino.cc/cgi-bin/yabb2/YaBB.pl?num=1235060559/0#4
 */
void setPwmFrequency(int pin, int divisor) {
  byte mode;
  if(pin == 5 || pin == 6 || pin == 9 || pin == 10) {
    switch(divisor) {
      case 1: mode = 0x01; break;
      case 8: mode = 0x02; break;
      case 64: mode = 0x03; break;
      case 256: mode = 0x04; break;
      case 1024: mode = 0x05; break;
      default: return;
    }
    if(pin == 5 || pin == 6) {
      TCCR0B = TCCR0B & 0b11111000 | mode;
    } else {
      TCCR1B = TCCR1B & 0b11111000 | mode;
    }
  } else if(pin == 3 || pin == 11) {
    switch(divisor) {
      case 1: mode = 0x01; break;
      case 8: mode = 0x02; break;
      case 32: mode = 0x03; break;
      case 64: mode = 0x04; break;
      case 128: mode = 0x05; break;
      case 256: mode = 0x06; break;
      case 1024: mode = 0x7; break;
      default: return;
    }
    TCCR2B = TCCR2B & 0b11111000 | mode;
  }
}

extern "C" {

  /*********************************************************************
	User defined Output Channel Functions
*********************************************************************/

/* Output Channel Functions,
	called by CIP Machine when a Message is written.
	User defined function, with name to consider as suggestion */

void uCHAN_AmbientAction (unsigned char name_)
{
  if(true){
    return;
  }
	/* Accessing MESSAGE */
	switch (name_)
	{
	case C12_OFF:
                while(ambientDimValue > LIGHT_OFF_STANDARD_VALUE){
                  decAmbientBrightness();
                  dimAmbient(ambientDimValue);
                  delay(AMBIENT_DIM_DELAY);
                }

                ambientDimValue = LIGHT_OFF_STANDARD_VALUE;
                dimAmbient(ambientDimValue);
                Serial.print("Ambient Off ");
                Serial.println(ambientDimValue);
                delay(LIGHT_ON_OFF_DELAY);
		break;
	case C12_ON:
                while(ambientDimValue < LIGHT_ON_STANDARD_VALUE){
                  incAmbientBrightness();
                  dimAmbient(ambientDimValue);
                  delay(AMBIENT_DIM_DELAY);
                }
                ambientDimValue = LIGHT_ON_STANDARD_VALUE;
                dimAmbient(ambientDimValue);
                Serial.print("Ambient On ");
                Serial.println(ambientDimValue);
                delay(LIGHT_ON_OFF_DELAY);
		break;
	default: 
		break;
	}
}

/* Parameters
	name_		name value of message */

void uCHAN_LightActionOut (unsigned char name_)
{
	/* Accessing MESSAGE */
	switch (name_)
	{
	case C9_MINUS:
                decBrightness();
                dimLight(lightDimValue);
                Serial.print("Light - ");
                Serial.println(lightDimValue);
                delay(LIGHT_DIM_DELAY);
		break;
	case C9_OFF:
                while(lightDimValue > LIGHT_OFF_STANDARD_VALUE){
                  decBrightness();
                  dimLight(lightDimValue);
                  delay(LIGHT_DIM_OFF_DELAY);
                }

                lightDimValue = LIGHT_OFF_STANDARD_VALUE;
                dimLight(lightDimValue);
                Serial.print("Light Off ");
                Serial.println(lightDimValue);
                delay(LIGHT_ON_OFF_DELAY);
		break;
	case C9_ON:
                while(lightDimValue < LIGHT_ON_STANDARD_VALUE){
                  incBrightness();
                  dimLight(lightDimValue);
                  delay(LIGHT_DIM_OFF_DELAY);
                }
                lightDimValue = LIGHT_ON_STANDARD_VALUE;
                dimLight(lightDimValue);
                Serial.print("Light On ");
                Serial.println(lightDimValue);
                delay(LIGHT_ON_OFF_DELAY);
		break;
	case C9_PLUS:
                incBrightness();
                dimLight(lightDimValue);
                Serial.print("Light + ");
                Serial.println(lightDimValue);
                delay(LIGHT_DIM_DELAY);
		break;
	default: 
		break;
	}
}

void uCHAN_SoundActionOut (unsigned char name_)
{
	/* Accessing MESSAGE */
	switch (name_)
	{
	case C10_MINUS:
		decLoudness();
                Serial.print("Sound - ");
                Serial.println(thevol);
                handleAmplifierCommand(thevol);
                delay(SOUND_DIM_DELAY);
		break;
	case C10_OFF:
                thevol = SOUND_OFF_STANDARD_VALUE;
                Serial.print("Sound Off ");
                Serial.println(thevol);
                handleAmplifierCommand(thevol);                
                delay(SOUND_ON_OFF_DELAY);
		break;
	case C10_ON:
                thevol = SOUND_ON_STANDARD_VALUE;
                Serial.print("Sound On ");
                Serial.println(thevol);
                handleAmplifierCommand(thevol);                
                delay(SOUND_ON_OFF_DELAY);
		break;
	case C10_PLUS:
		incLoudness();
                Serial.print("Sound + ");
                Serial.println(thevol);
                handleAmplifierCommand(thevol);
                delay(SOUND_DIM_DELAY);
		break;
	default: 
		break;
	}
}


/*********************************************************************
	User defined Output Channel Interface Initialization Function
*********************************************************************/

void iCHAN_(void)
{
		/* Initializing Input Error Function only if Input Error Option set */

	#ifdef _EINPUT__
		IN_.EINPUT_ = uEINPUT_;
	#endif 

		/* Initializing Output Interface */

	OUT_.AmbientAction = uCHAN_AmbientAction;
	OUT_.LightActionOut = uCHAN_LightActionOut;
	OUT_.SoundActionOut = uCHAN_SoundActionOut;
}

  
}//end extern C
