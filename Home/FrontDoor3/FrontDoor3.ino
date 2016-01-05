
#include <SPI.h>
#include <Ethernet.h>

// Enter a MAC address for your controller below.
// Newer Ethernet shields have a MAC address printed on a sticker on the shield
//de:ad:be:ef:fe:ed
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
// if you don't want to use DNS (and reduce your sketch size)
// use the numeric IP instead of the name for the server:
IPAddress server(192,168,1,38);  // numeric IP for Google (no DNS)
EthernetClient client;
// Set the static IP address to use if the DHCP fails to assign
IPAddress ip(192, 168, 1, 177);

// constants won't change. They're used here to
// set pin numbers:
const int buttonPin = 2;    // the number of the pushbutton pin
const int ledPin = 8;      // the number of the LED pin

// Variables will change:
int ledState = HIGH;         // the current state of the output pin
int buttonState = LOW;             // the current reading from the input pin
int lastButtonState = LOW;   // the previous reading from the input pin

// the following variables are long's because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.
long lastDebounceTime = 0;  // the last time the output pin was toggled
long debounceDelay = 50;    // the debounce time; increase if the output flickers
void initializePins(){
  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);
  // set initial LED state
  digitalWrite(ledPin, LOW);
}
void initializeHttpClient(){
  // start the Ethernet connection:
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    // no point in carrying on, so do nothing forevermore:
    // try to congifure using IP address instead of DHCP:
    Ethernet.begin(mac, ip);
  }
}
void setup() {
  Serial.begin(9600);
        Serial.println("starting...");

  initializePins();
  //initializeHttpClient();
}

void loop() {
  Serial.println("loop");
  if(isButtonPressed()){
    Serial.println("pressed");
    digitalWrite(ledPin,HIGH);
    //sendButtonPressed();
  }else{
      digitalWrite(ledPin,LOW);
  }
  delay(25);
}

boolean isButtonPressed(){
  boolean isPressed = false;
  // read the state of the switch into a local variable:
  int reading = digitalRead(buttonPin);

  // check to see if you just pressed the button
  // (i.e. the input went from LOW to HIGH),  and you've waited
  // long enough since the last press to ignore any noise:

  // If the switch changed, due to noise or pressing:
  if (reading != lastButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer
    // than the debounce delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading != buttonState) {
      buttonState = reading;

      // only toggle the LED if the new button state is HIGH
      if (buttonState == LOW) {
        ledState = !ledState;
        isPressed = true;
      }
    }
  }
  // save the reading.  Next time through the loop,
  // it'll be the lastButtonState:
  lastButtonState = reading;
  return isPressed;
}

void sendButtonPressed(){
      Serial.println("connecting ...");
    // if you get a connection, report back via serial:
    if (client.connect(server, 8080)) {
      Serial.println("connected");
      // Make a HTTP request:
      client.println("GET /FrontDoor/Ring?state=on HTTP/1.1");
      client.println("Host: FrontDoorController");
      client.println("Connection: close");
      client.println();
    }
    else {
      
      // kf you didn't get a connection to the server:
      Serial.println("connection failed");
      for(int i=0; i<10; i++){
        digitalWrite(ledPin, HIGH);
        delay(300);
        digitalWrite(ledPin, LOW);
        delay(300);
      }
    }        
  
}
