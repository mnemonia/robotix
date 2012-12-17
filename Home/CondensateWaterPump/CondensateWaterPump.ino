const int upperLevelSensorPin = A1;
const int lowerLevelSensorPin = A0;
const int upperLevelActorPin = 5;
const int lowerLevelActorPin = 6;
const int onIndicatorPin = 4;
const int runningPumpIndicatorPin = 3;
const int notRunningPumpIndicatorPin = 2;
int upperLevelSensorValue = 0;
int lowerLevelSensorValue = 0;

//
boolean isPumping = false;

// Pump Settings
const int pumpFwdDirectionPin = 8;//11;
const int pumpBwdDirectionPin = 11;
const int pumpSpeedPin = 9;
const int pumpSpeed = 255;

const int waterIndicatorValue = 25;

void setup() {
  Serial.begin(9600);
  // declare the ledPin as an OUTPUT:
  init(onIndicatorPin);
  init(runningPumpIndicatorPin);
  init(notRunningPumpIndicatorPin);


  init(upperLevelActorPin);
  init(lowerLevelActorPin);

  init(pumpFwdDirectionPin);
  init(pumpBwdDirectionPin);
  init(pumpSpeedPin);

  on(onIndicatorPin);
  off(runningPumpIndicatorPin);
  off(notRunningPumpIndicatorPin);
}

void loop() {
  if(isPumping){
    if(isEmpty()){
      stopPump();
    }
  }
  
  if(!isPumping){
    if(isNeedPump()){
      startPump();
    }
  }

  debug();
  delay(2000);
}

boolean isEmpty(){
  // read the value from the sensor:
  on(lowerLevelActorPin);
  delay(20);
  lowerLevelSensorValue = analogRead(lowerLevelSensorPin);    
  off(lowerLevelActorPin);
  return lowerLevelSensorValue < waterIndicatorValue;
}

void debug(){
  Serial.print("Upper Level Sensor Value: ");
  Serial.println(upperLevelSensorValue);
  Serial.print("Lower Level Sensor Value: ");
  Serial.println(lowerLevelSensorValue);
}

boolean isNeedPump(){
  // read the value from the sensor:
  on(upperLevelActorPin);
  delay(20);
  upperLevelSensorValue = analogRead(upperLevelSensorPin);    
  off(upperLevelActorPin);

  return upperLevelSensorValue > waterIndicatorValue;
}

void startPump(){
  isPumping = true;
  on(runningPumpIndicatorPin);
  off(notRunningPumpIndicatorPin);  
  analogWrite(pumpSpeedPin, pumpSpeed);
  on(pumpFwdDirectionPin);
  off(pumpBwdDirectionPin);
}

void stopPump(){
  isPumping = false;
  off(runningPumpIndicatorPin);
  on(notRunningPumpIndicatorPin);  
  analogWrite(pumpSpeedPin, 0);
  off(pumpFwdDirectionPin);
  off(pumpBwdDirectionPin);
}

void on(int pin){
  digitalWrite(pin,HIGH);
}

void off(int pin){
  digitalWrite(pin,LOW);
}

void init(int pin){
  pinMode(pin,OUTPUT);
}

