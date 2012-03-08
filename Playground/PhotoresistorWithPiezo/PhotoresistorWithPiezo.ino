int photosensorPinLeft = A0;
int photosensorPinRight = A1;
int piezoPinLeft = 9;
int piezoPinRight = 10;

int valLeft = 0;
int valRight = 0;

void setup() {
  pinMode(piezoPinLeft, OUTPUT);
  pinMode(piezoPinRight, OUTPUT);

  Serial.begin(9600);
  Serial.println("Ready!");
}

void loop() {
  digitalWrite(piezoPinLeft, LOW);
  digitalWrite(piezoPinRight, LOW);
  valLeft = analogRead(photosensorPinLeft);
  valLeft = valLeft/2;
  valRight = analogRead(photosensorPinRight);
  valRight = valRight/2;

  Serial.print("Left[");
  Serial.print(valLeft);
  Serial.print("] ");
  Serial.print("Right[");
  Serial.print(valRight);
  Serial.println("]");
/*

  for( int i=0; i<500; i++ ) {  // play it for 50 cycles
    digitalWrite(piezoPinLeft, HIGH);
    digitalWrite(piezoPinRight, HIGH);
    delayMicroseconds(valLeft);
    delayMicroseconds(valRight);
    digitalWrite(piezoPinLeft, LOW);
    digitalWrite(piezoPinRight, LOW);
    delayMicroseconds(valLeft);
    delayMicroseconds(valRight);
  }
  */
}
