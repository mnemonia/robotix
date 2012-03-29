int photosensorPinLeft = A0;

int valLeft = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("Ready!");
}

void loop() {
  valLeft = analogRead(photosensorPinLeft);
  valLeft = valLeft/2;

  Serial.print("Left[");
  Serial.print(valLeft);
  Serial.println("] ");
}
