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
// 35 is ok for sound off, 30 is no noise
#define SOUND_ON_STANDARD_VALUE 35
#define SOUND_OFF_STANDARD_VALUE 0
// 44 is ok for max sound, 63 is max, 40 is no noise
#define SOUND_MAX_VALUE 50
#define SOUND_MIN_VALUE 8
#define SOUND_DIM_DELAY 80
#define SOUND_ON_OFF_DELAY 1000
#define SOUND_DIM_STEP 1


// We'll track the volume level in this variable.
int thevol = SOUND_OFF_STANDARD_VALUE;
#define LIGHT_ON_STANDARD_VALUE 100
#define LIGHT_OFF_STANDARD_VALUE 0
// 130 is no noise
#define LIGHT_ON_MAX_VALUE 170
#define LIGHT_ON_MIN_VISIBLE_VALUE 10
int lightDimValue = LIGHT_OFF_STANDARD_VALUE;
int ambientDimValue = LIGHT_OFF_STANDARD_VALUE;
#define LIGHT_DIM_STEP 5
#define LIGHT_DIM_MINUS_STEP 2
#define LIGHT_MANUAL_DIM_STEP 2
#define AMBIENT_DIM_STEP 1
#define AMBIENT_DIM_MIN 0

#define LIGHT_PIN 6
#define AMBIENT_PIN 5
#define LOUDSPEAKER_ONOFF_PIN 4
#define LOUDSPEAKER_PLUS_PIN 3
#define LOUDSPEAKER_MINUS_PIN 2

long currentMillies = 0L;
long previousMillis = 0;
long interval = 20;  

char inData[20]; // Allocate some space for the string
char inChar=-1; // Where to store the character read
byte index = 0; // Index into array; where to store the character

void setup() {
  Serial.begin(9600);
  Serial.println("Starting Findl.ing Workdesk Controller ...");
  
  //setPwmFrequency(LIGHT_PIN, 1);
  
  Wire.begin();
  setupStateMachines();  
  setupAmplifier();
  setupLoudspeakerSensor();
  setupLight();
  setupCapSensor();  
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
    ///!!!while (1);
  }
} 
void setupCapSensor(){
  if (!cap.begin()) {
    Serial.println("CAP1188 not found");
    ///!!!while (1);
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

void readSensors() {
  checkAndSetLightControls();
  ////checkAndSetAudioControls();
  checkAndSetLoundspeakerControls();  
  ////checkAndSetAmbientControls();
  cap.touched();
}

void loop(){
  unsigned long currentMillis = millis();
 
  if(currentMillis - previousMillis > interval) {
    // save the last time you blinked the LED
    previousMillis = currentMillis; 
    incrementTime();
  }  
  
}

void incrementTime(){
//  manualLightControl();
//  manualSoundControl();
  readSensors();
  TRG_.TICK_(); 		/* increment CIP Machine time by one Tick */
  if (TRG_.PENDING_.TIMEUP_) TRG_.TIMEUP_(); /* timeup call */
// Serial.println("TICK");
}

void manualLightControl(){
  if(comp("L+")==0){
    Serial.println("Manual Light +");
    IN_.LightDimPlusEvents(C6_PRESS);
  }else{
    IN_.LightDimPlusEvents(C6_RELEASE);
  }
  if(comp("L-")==0){
    Serial.println("Manual Light -");
    IN_.LightDimMinusEvents(C7_PRESS);
  }else{
    IN_.LightDimMinusEvents(C7_RELEASE);
  }
  if(comp("L")==0){
    Serial.println("Manual Light Toggle");
    IN_.LightSwitchEvent(C2_TOGGLE);
  }
  
}

void manualSoundControl(){
  if(comp("s+")==0){
    Serial.println("Manual Sound +");
    IN_.SoundPlusChannel(C8_PRESSED);
  }else{
    IN_.SoundPlusChannel(C8_RELEASED);
  }
  if(comp("s-")==0){
    Serial.println("Manual Sound -");
    IN_.SoundMinusChannel(C9_PRESSED);
  }else{
    IN_.SoundMinusChannel(C9_RELEASED);
  }
  if(comp("s")==0){
    Serial.println("Manual Sound Toggle");
    IN_.SoundSwitchChannel(C10_TOGGLE);
  }
  
}

char comp(char* This) {
    while (Serial.available() > 0) // Don't read unless
                                   // there you know there is data
    {
        if(index < 19) // One less than the size of the array
        {
            inChar = Serial.read(); // Read a character
            inData[index] = inChar; // Store it
            index++; // Increment where to write next
            inData[index] = '\0'; // Null terminate the string
        }
    }

    if (strcmp(inData,This)  == 0) {
        for (int i=0;i<19;i++) {
            inData[i]=0;
        }
        index=0;
        return(0);
    }
    else {
        return(1);
    }
}

void checkAndSetLightControls(){
  uint8_t touched = cap.touched();
  if (touched == 0) {
    // No touch detected
    return;
  }
  if(touched & (1 << CAP_LIGHT_PLUS)){
    Serial.println("Light Sense Plus Press");
    IN_.LightDimPlusEvents(C6_PRESS);
  }

  if(touched & (1 << CAP_LIGHT_MINUS)){
    Serial.println("Light Sense Minus Press");
    IN_.LightDimMinusEvents(C7_PRESS);
  }
  
  if(touched & (1 << CAP_LIGHT_ON_OFF)){
    Serial.println("Light Sense Plus Release");
    IN_.LightDimPlusEvents(C6_RELEASE);
    Serial.println("Light Sense Minus Release");
    IN_.LightDimMinusEvents(C7_RELEASE);
    Serial.println("Light Sense ON/OFF");
    IN_.LightSwitchEvent(C2_TOGGLE);
  }
}

void checkAndSetLoundspeakerControls(){
  int touched = digitalRead(LOUDSPEAKER_ONOFF_PIN);
  if (touched == LOW) {
    Serial.println("Loudspeaker Sense ON/OFF");
    IN_.SoundPlusChannel(C8_RELEASED);
    IN_.SoundMinusChannel(C9_RELEASED);
    IN_.SoundSwitchChannel(C10_TOGGLE);
  }else{
    touched = digitalRead(LOUDSPEAKER_MINUS_PIN);    
    if (touched == LOW) {
      Serial.println("Loudspeaker Sense Minus");
      IN_.SoundMinusChannel(C9_PRESSED);
    }else{
      touched = digitalRead(LOUDSPEAKER_PLUS_PIN);    
      if (touched == LOW) {
        Serial.println("Loudspeaker Sense Plus");
        IN_.SoundPlusChannel(C8_PRESSED);
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
  lightDimValue -= LIGHT_DIM_MINUS_STEP;
  if(lightDimValue <= LIGHT_OFF_STANDARD_VALUE){
    lightDimValue = LIGHT_OFF_STANDARD_VALUE;
  }
}

void incManualBrightness(){
  lightDimValue += LIGHT_MANUAL_DIM_STEP;
  if(lightDimValue >= LIGHT_ON_MAX_VALUE){
    lightDimValue = LIGHT_ON_MAX_VALUE;
  }
}

void decManualBrightness(){
  lightDimValue -= LIGHT_MANUAL_DIM_STEP;
  if(lightDimValue <= LIGHT_OFF_STANDARD_VALUE){
    lightDimValue = LIGHT_OFF_STANDARD_VALUE;
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
  if(ambientDimValue <= LIGHT_OFF_STANDARD_VALUE){
    ambientDimValue = LIGHT_OFF_STANDARD_VALUE;
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
  }else if(thevol <= SOUND_MIN_VALUE){
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

void uCHAN_AmbientDimAction (unsigned char name_)
{
	/* Accessing MESSAGE */
	switch (name_)
	{
	case C4_MINUS:
                if(ambientDimValue <= AMBIENT_DIM_MIN){
                  Serial.print("Dimming ambient light down done on ");
                  Serial.println(ambientDimValue);
                  ambientDimValue = 0;
                  dimAmbient(ambientDimValue);
                  IN_.AmbientDimReply(C5_IS_OFF);
                }else{
                  Serial.print("Dimming ambient light down to ");
                  Serial.println(ambientDimValue);
                  decAmbientBrightness();
                  dimAmbient(ambientDimValue);
                }
		break;
	case C4_PLUS:
                if(ambientDimValue >= LIGHT_ON_STANDARD_VALUE){
                  ambientDimValue = LIGHT_ON_STANDARD_VALUE;
                  Serial.print("Dimming ambient light up done on ");
                  Serial.println(ambientDimValue);
                  IN_.AmbientDimReply(C5_IS_ON);
                }else{
                  Serial.print("Dimming ambient light up to ");
                  Serial.println(ambientDimValue);
                  incAmbientBrightness();
                  dimAmbient(ambientDimValue);
                }
		break;
	default: 
		break;
	}
}

void uCHAN_SoundActions (unsigned char name_)
{
	/* Accessing MESSAGE */
	switch (name_)
	{
	case C11_MINUS:
		decLoudness();
                Serial.print("Sound - ");
                Serial.println(thevol);
                handleAmplifierCommand(thevol);
                if(thevol <= SOUND_OFF_STANDARD_VALUE){
                  Serial.println("Sound Off");
                  IN_.SoundControlEvents(C12_IS_OFF);                
                }
		break;
	case C11_PLUS:
		incLoudness();
                Serial.print("Sound + ");
                Serial.println(thevol);
                handleAmplifierCommand(thevol);
                if(thevol >= SOUND_ON_STANDARD_VALUE){
                  Serial.println("Sound On");
                  IN_.SoundControlEvents(C12_IS_ON);                
                }
		break;
	case C11_PLUS_STEP:
		incLoudness();
		incLoudness();
		incLoudness();
                Serial.print("Sound Direct + ");
                Serial.println(thevol);
                handleAmplifierCommand(thevol);
                Serial.println("Sound On");
                IN_.SoundControlEvents(C12_IS_ON);
		break;
	default: 
		break;
	}  
}

void uCHAN_LightControllerActions (unsigned char name_)
{
	/* Accessing MESSAGE */
	switch (name_)
	{
  	case C14_MINUS:
               decBrightness();
                Serial.print("Dimming light down to ");
                Serial.println(lightDimValue);
                dimLight(lightDimValue);

                if(lightDimValue <= LIGHT_OFF_STANDARD_VALUE){
                  Serial.print("Dimming light down done on ");
                  Serial.println(lightDimValue);
                  IN_.LightControllerEvents(C13_IS_OFF);
                }
                
		break;
	case C14_MINUS_STEP:
               decManualBrightness();
                Serial.print("Dimming light down to ");
                Serial.println(lightDimValue);
                dimLight(lightDimValue);

                if(lightDimValue <= LIGHT_OFF_STANDARD_VALUE){
                  Serial.print("Dimming light down done on ");
                  Serial.println(lightDimValue);
                  IN_.LightControllerEvents(C13_IS_OFF);
                }
		break;
	case C14_PLUS:
                incBrightness();
                Serial.print("Dimming light up to ");
                Serial.println(lightDimValue);
                dimLight(lightDimValue);

                if(lightDimValue >= LIGHT_ON_STANDARD_VALUE){
                  Serial.print("Dimming light up done on ");
                  Serial.println(lightDimValue);
                  IN_.LightControllerEvents(C13_IS_ON);
                }		
		break;
	case C14_PLUS_STEP:
                incManualBrightness();
                Serial.print("Dimming light up to ");
                Serial.println(lightDimValue);
                dimLight(lightDimValue);

                if(lightDimValue >= LIGHT_ON_STANDARD_VALUE){
                  Serial.print("Dimming light up done on ");
                  Serial.println(lightDimValue);
                  IN_.LightControllerEvents(C13_IS_ON);
                }		
		break;
	case C14_PLUS_STEP_DIRECT:
                incBrightness();
                Serial.print("Dimming light direct up to ");
                Serial.println(lightDimValue);
                dimLight(lightDimValue);
                  IN_.LightControllerEvents(C13_IS_ON);

                if(lightDimValue >= LIGHT_ON_MIN_VISIBLE_VALUE){
                  Serial.print("Dimming light direct up done on ");
                  Serial.println(lightDimValue);
                  IN_.LightControllerEvents(C13_IS_ON);
                }
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
	OUT_.AmbientDimAction = uCHAN_AmbientDimAction;
	OUT_.LightControllerActions = uCHAN_LightControllerActions;
	OUT_.SoundActions = uCHAN_SoundActions;
}

  
}//end extern C
