const int ledPin  =13;
const int middleValue = 340;
const int numberOfSamples =128;

int sample;
long signal;
long averageReading;

long runningAverage = 0;
const int averagedOver = 16;

const int threshold = 30;
int lowest = 1000;
int highest = 0;
void setup(){
  pinMode(ledPin,OUTPUT);
  Serial.begin(9600);
}

void loop(){
  sample = analogRead(A0);
  
  long sumOfSquares = 0;
  for(int i=0; i<numberOfSamples; i++){
    sample = analogRead(A0);
    signal = (sample - middleValue);
    signal *= signal;
    sumOfSquares += signal;
  }
  averageReading = sumOfSquares / numberOfSamples;
 //analogWrite(A0,map(averageReading,5,50,0,255));
 analogWrite(A1,averageReading);
  if(averageReading<lowest){
    lowest = averageReading;
  }
  if(averageReading>highest){
    highest = averageReading;
  }
  //Serial.println(map(averageReading,40,80,0,100));
  //Serial.println(map(lowest,40,80,0,100));
  Serial.println(averageReading);

  //Serial.println(sample);
  /*sample = map(sample,300,400,0,100);
  Serial.println(sample);
  Serial.println(lowest);
  Serial.println(highest);
  Serial.println("<---");
  */
  if(averageReading>threshold){
    digitalWrite(ledPin,HIGH);
  }else{
    digitalWrite(ledPin,LOW);
  }
  //delay(2000);
 /*
 long sumOfSquares = 0;
  for(int i=0; i<numberOfSamples; i++){
    sample = analogRead(A0);
    Serial.println(sample);
    sample = map(sample,300,360,0,1000);
    Serial.println(sample);
    Serial.println("---");
    signal = (sample - middleValue);
    signal *= signal;
    sumOfSquares += signal;
  }
  averageReading = sumOfSquares / numberOfSamples;
  runningAverage = (((averagedOver-1)*runningAverage)+averageReading)/averagedOver;
  
  if(runningAverage>threshold){
    digitalWrite(ledPin,HIGH);
  }else{
    digitalWrite(ledPin,LOW);  
  }
  
  Serial.println(runningAverage);
  delay(1000);
*/  
}
