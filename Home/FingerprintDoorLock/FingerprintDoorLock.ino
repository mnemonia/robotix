/*************************************************** 
  This is an example sketch for our optical Fingerprint sensor

  Designed specifically to work with the Adafruit BMP085 Breakout 
  ----> http://www.adafruit.com/products/751

  These displays use TTL Serial to communicate, 2 pins are required to 
  interface
  Adafruit invests time and resources providing this open source code, 
  please support Adafruit and open-source hardware by purchasing 
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.  
  BSD license, all text above must be included in any redistribution
 ****************************************************/


#include <Adafruit_Fingerprint.h>
#if ARDUINO >= 100
 #include <SoftwareSerial.h>
#else
 #include <NewSoftSerial.h>
#endif

#define DOOR_LOCK_PIN 9
#define FINGERPRINT_SENSOR_PIN 12
#define FINGERPRINT_SENSOR_GREEN 2
#define FINGERPRINT_SENSOR_WHITE 3
#define LED_PIN 13

int getFingerprintIDez();

// pin #2 is IN from sensor (GREEN wire)
// pin #3 is OUT from arduino  (WHITE wire)
#if ARDUINO >= 100
SoftwareSerial mySerial(FINGERPRINT_SENSOR_GREEN, FINGERPRINT_SENSOR_WHITE);
#else
NewSoftSerial mySerial(FINGERPRINT_SENSOR_GREEN, FINGERPRINT_SENSOR_WHITE);
#endif

Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

void setup()  
{
  Serial.begin(9600);
  Serial.println("findl.ing door lock");

  pinMode(DOOR_LOCK_PIN, OUTPUT);
  pinMode(FINGERPRINT_SENSOR_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);

  testOpenCloseDoor();
  turnOnFingerprintSensor();

  Serial.println("findl.ing door lock READY");
}

void turnOnFingerprintSensor(){
  Serial.print("Turning on fingerprint sensor ...");
  startFingerprintsensor();  
  delay(200);
  // set the data rate for the sensor serial port
  finger.begin(57600);
  if (finger.verifyPassword()) {
    Serial.print("Turning on fingerprint sensor SUCCESS");
  } else {
    Serial.print("Turning on fingerprint sensor FAIL. Sensor not found.");
    stopFingerprintsensor();
    showAlarmForever();  
  }
}

void testOpenCloseDoor(){
  openDoor();
  delay(2000);
  closeDoor();
}

void showAlarmForever(){
    Serial.print("findl.ing door lock FAIL. Alarm: Service out-of-order.");
    while (1){
      digitalWrite(LED_PIN,HIGH);
      delay(100);
      digitalWrite(LED_PIN,LOW);
      delay(100);
    }
}

void openDoor(){
  digitalWrite(LED_PIN,HIGH);
  digitalWrite(DOOR_LOCK_PIN,HIGH);
  Serial.println("findl.ing door lock OPEN");
}
void closeDoor(){
  digitalWrite(LED_PIN,LOW);
  digitalWrite(DOOR_LOCK_PIN,LOW);
}
void startFingerprintsensor(){
  digitalWrite(FINGERPRINT_SENSOR_PIN,HIGH);
}
void stopFingerprintsensor(){
  digitalWrite(FINGERPRINT_SENSOR_PIN,LOW);
}

void loop()                     // run over and over again
{
  int identified = getFingerprintIDez();
  switch(identified){
    case -1:
      closeDoor();
      delay(50);
      break;
    default:
      openDoor();
      delay(1000);
  }
}

uint8_t getFingerprintID() {
  uint8_t p = finger.getImage();
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image taken");
      break;
    case FINGERPRINT_NOFINGER:
      Serial.println("No finger detected");
      return -1;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return -1;
    case FINGERPRINT_IMAGEFAIL:
      Serial.println("Imaging error");
      return -1;
//    default:
//      Serial.println("Unknown error");
//      return p;
  }

  // OK success!

  p = finger.image2Tz();
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image converted");
      break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println("Image too messy");
      return -1;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return -1;
    case FINGERPRINT_FEATUREFAIL:
      Serial.println("Could not find fingerprint features");
      return -1;
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println("Could not find fingerprint features");
      return -1;
//    default:
//      Serial.println("Unknown error");
//      return p;
  }
  
  // OK converted!
  p = finger.fingerFastSearch();
  switch(p){
    case FINGERPRINT_OK:
      Serial.println("Found a print match!");
      break;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return -1;
    case FINGERPRINT_NOTFOUND:
      Serial.println("Did not find a match");
      return -1;
  }

  // found a match!
  Serial.print("Found ID #"); Serial.print(finger.fingerID); 
  Serial.print(" with confidence of "); Serial.println(finger.confidence); 
  return finger.fingerID;
}

// returns -1 if failed, otherwise returns ID #
int getFingerprintIDez() {
  uint8_t p = finger.getImage();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.image2Tz();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.fingerFastSearch();
  if (p != FINGERPRINT_OK)  return -1;
  
  // found a match!
  Serial.print("Found ID #"); Serial.print(finger.fingerID); 
  Serial.print(" with confidence of "); Serial.println(finger.confidence);
  return finger.fingerID; 
}
