int sensorPin = A5; //analog pin 0

void setup(){
  Serial.begin(9600);
}

int measure(){}
void loop(){
  int val = analogRead(sensorPin);
//  Serial.println(val);


  val = analogRead(A0);
  Serial.print("A0 ");
  Serial.println(val);
  val = analogRead(A1);
  Serial.print("A1 ");
  Serial.println(val);
  val = analogRead(A2);
  Serial.print("A2 ");
  Serial.println(val);
  val = analogRead(A3);
  Serial.print("A3 ");
  Serial.println(val);
  val = analogRead(A4);
  Serial.print("A4 ");
  Serial.println(val);
  val = analogRead(A5);
  Serial.print("A5 ");
  Serial.println(val);
    Serial.println("-------");
  //just to slow down the output - remove if trying to catch an object passing by
  delay(1500);

}
