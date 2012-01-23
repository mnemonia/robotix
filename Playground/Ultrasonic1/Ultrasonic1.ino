#include <Ultrasonic.h>

Ultrasonic ultrasonic(A5,A4);

void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("Ultrasonic Test 1");
}

void loop()
{
  Serial.println(ultrasonic.Ranging(CM));
  delay(100);
}




