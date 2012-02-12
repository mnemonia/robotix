unsigned long time;
int sA;
int sB;
long signalA;
long signalB;
long averageReadingA;
long averageReadingB;
const int numberOfSamples =128;
const int middleValue = 340;

void setup(){
  Serial.begin(9600);
  pinMode(12,OUTPUT);
  pinMode(13,OUTPUT);
}
void loop(){
  senseSound();
   delay(20);
}

void senseSound(){
  long A = average(A0);
  long B = average(A1);
  
  if(A>B){
    Serial.println("A");
    digitalWrite(13,HIGH);
    digitalWrite(12,LOW);
  }else{
    Serial.println("B");
    digitalWrite(12,HIGH);
    digitalWrite(13,LOW);
  }
}

long average(int pin){
  int sA;
  long sumOfSquaresA = 0;
  for(int i=0; i<numberOfSamples; i++){
    sA = analogRead(pin);
    signalA = (sA - middleValue);
    signalA *= signalA;
    sumOfSquaresA += signalA;
  }
  return sumOfSquaresA / numberOfSamples; 
}

void senseSound2(){
  long sumOfSquaresA = 0;
  long sumOfSquaresB = 0;
  int A = 0;
  int B = 0;
  for(int i=0; i<numberOfSamples; i++){
    int a = 0;
    int b = 0;
    sA = analogRead(A0);
    sB = analogRead(A1);
    if(sA>sB){
      a++;
    }else{
      b++;
    }
    A += a;
    B += b;
/*
signalA = (sA - middleValue);
    signalA *= signalA;
    sumOfSquaresA += signalA;
    signalB = (sB - middleValue);
    signalB *= signalB;
    sumOfSquaresB += signalB;
*/
  }

  if(A>B){
    Serial.println("A");
    digitalWrite(13,HIGH);
    digitalWrite(12,LOW);
  }else{
    Serial.println("B");
    digitalWrite(12,HIGH);
    digitalWrite(13,LOW);
  }
  //averageReadingA = sumOfSquaresA / numberOfSamples;
  //averageReadingB = sumOfSquaresB / numberOfSamples;
}
