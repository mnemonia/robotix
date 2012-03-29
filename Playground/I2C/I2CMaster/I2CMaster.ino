#include <Wire.h>

#define LED_PIN 13
byte x = 0;

void setup()
{
  Wire.begin(); // Start I2C Bus as Master
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

}
void loop()
{
  
  digitalWrite(LED_PIN, HIGH);
  Wire.beginTransmission(9); // transmit to device #9
  digitalWrite(LED_PIN, LOW);
  Wire.write(x);              // sends x 
  Wire.endTransmission();    // stop transmitting
  x++;
  if (x > 5) x=0;
  delay(220);
}
