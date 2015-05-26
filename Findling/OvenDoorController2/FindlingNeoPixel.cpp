#include "FindlingNeoPixel.h"


FindlingNeoPixel::FindlingNeoPixel(
  int pin,
  int i_redStart,
  int i_redEnd,
  int i_greenStart,
  int i_greenEnd,
  int i_blueStart,
  int i_blueEnd)
//: pixels(Adafruit_NeoPixel(1, pin, NEO_GRB + NEO_KHZ800))
  : pixels(1, 7, NEO_GRB + NEO_KHZ800)
{
  pinMode(pin, OUTPUT);
  _pin = pin;
  ioTime = 10;
  previousMillis = 0;
  t = 0;
  isOff = true;
  isOn = false;
  isTurningOn = false;
  isTurningOff = false;

  redStart = i_redStart;
  redEnd = i_redEnd;
  greenStart = i_greenStart;
  greenEnd = i_greenEnd;
  blueStart = i_blueStart;
  blueEnd = i_blueEnd;

  pixels.begin(); // This initializes the NeoPixel library.
}

void FindlingNeoPixel::turnOn()
{
  isTurningOn = true;
  isTurningOff = false;
  Serial.println("turningOn");
}

void FindlingNeoPixel::turnOff()
{
  isTurningOff = true;
  isTurningOn = false;
  Serial.println("turningOff");
}
void FindlingNeoPixel::off()
{
  turnOff();
  pixels.setPixelColor(0, pixels.Color(0, 0, 0));
  pixels.show(); // This sends the updated pixel color to the hardware.
  Serial.println("off");
}

void FindlingNeoPixel::update()
{
  if (isTurningOn && (t == 100)) {
    isOn = true;
    isTurningOn = false;
    t = 100;
  }
  if (isTurningOff && (t == 0)) {
    isTurningOff = false;
    isOff = true;
    t = 0;
    pixels.setPixelColor(0, pixels.Color(0, 0, 0));
    pixels.show(); // This sends the updated pixel color to the hardware.
  }
  unsigned long currentMillis = millis();
  if (isTurningOn && (currentMillis - previousMillis >= ioTime)) {
    int r = nextColor(redStart, redEnd, t);
    int g = nextColor(greenStart, greenEnd, t);
    int b = nextColor(blueStart, blueEnd, t);
    Serial.print("Turning on:  "); Serial.print(r); Serial.print(":"); Serial.print(g); Serial.print(":"); Serial.println(b);
    pixels.setPixelColor(0, pixels.Color(r, g, b));
    pixels.show(); // This sends the updated pixel color to the hardware.
    previousMillis = currentMillis;   // Remember the time
    t++;
  }
  if (isTurningOff && (currentMillis - previousMillis >= ioTime)) {
    int r = nextColor(redStart, redEnd, t);
    int g = nextColor(greenStart, greenEnd, t);
    int b = nextColor(blueStart, blueEnd, t);
    Serial.print("Turning off: "); Serial.print(r); Serial.print(":"); Serial.print(g); Serial.print(":"); Serial.println(b);
    pixels.setPixelColor(0, pixels.Color(r, g, b));
    pixels.show(); // This sends the updated pixel color to the hardware.
    previousMillis = currentMillis;   // Remember the time
    t--;
  }

}

void FindlingNeoPixel::printState()
{
  Serial.print("State: ");
  Serial.print("isTurningOn:");
  Serial.print(isTurningOn);
  Serial.print(", isOn:");
  Serial.print(isOn);
  Serial.print(", isTurningOff:");
  Serial.print(isTurningOff);
  Serial.print(", isOff:");
  Serial.println(isOff);
}

int FindlingNeoPixel::nextColor(int colorStart, int colorEnd, int t) {
  float T = t / 100.0;
  return (int)((float)colorStart + ((float)colorEnd - (float)colorStart) * T);
}
