#include <SoftwareSerial.h>

#define SSerialRX        0  //Serial Receive pin
#define SSerialTX        1  //Serial Transmit pin

#define SSerialTxControl 2   //RS485 Direction control
#define RS485Transmit    HIGH
#define RS485Receive     LOW

#define pin13LED         13

/*-----( Declare objects )-----*/
SoftwareSerial RS485Serial(SSerialRX, SSerialTX); // RX, TX

/*-----( Declare Variables )-----*/
boolean stringComplete = false;
String someInfo="";
String state="";

unsigned long previousMillis = 0;
const long interval = 100;
int ledState = LOW;

/*-----( Declare Functions )-----*/
unsigned long myBlink(unsigned long, String);
String getState(String);
void sendRS485Data(String);
int getNumOfTimes(String);

void setup()   /****** SETUP: RUNS ONCE ******/
{
  pinMode(pin13LED, OUTPUT);
  pinMode(SSerialTxControl, OUTPUT);
  digitalWrite(SSerialTxControl, RS485Receive);  // Init Transceiver

  // Start the software serial port, to another device
  RS485Serial.begin(4800); // set the data rate
}//--(end setup )---


void loop()   /****** LOOP: RUNS CONSTANTLY ******/
{
  unsigned long currentMillis = millis();
  //Copy input data to output
  while (RS485Serial.available())
  {
    char inChar = (char)RS485Serial.read();
    if (inChar == '\n') {//If using the IDE monitor newline must be selected.
      stringComplete = true;
    } else {
      someInfo += inChar;
    }
  }

  if (stringComplete) {
    sendRS485Data(someInfo);

    state=getState(someInfo);
    someInfo = "";

    stringComplete = false;
  }

  previousMillis=myBlink(currentMillis,state);
}//--(end main loop )---

/*-----( Declare User-written Functions )-----*/
//NONE

unsigned long myBlink(unsigned long currentMillis, String state="n") {
  if (state != "b") {
    return currentMillis;
  }

  if (currentMillis - previousMillis >= interval) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;

    // if the LED is off turn it on and vice-versa:
    if (ledState == LOW) {
      ledState = HIGH;
    } else {
      ledState = LOW;
    }

    // set the LED with the ledState of the variable:
    digitalWrite(pin13LED, ledState);
  }
  return previousMillis;
}

String getState(String someInfo){
  if (someInfo == "y"){
      RS485Serial.println("Turning led on");
      state="y";
      digitalWrite(pin13LED, HIGH);
    } else if (someInfo == "b"){
      RS485Serial.println("blink state");
      state="b";
      digitalWrite(pin13LED, LOW);
    } else {
      state="n";
      digitalWrite(pin13LED, LOW);
    }
  return state;
}

void sendRS485Data(String someInfo){
  int numOfTimes=0;
  digitalWrite(SSerialTxControl, RS485Transmit); // Enable RS485 Transmit
  RS485Serial.println(someInfo);
  RS485Serial.println(someInfo.length());
  numOfTimes=getNumOfTimes(someInfo,':');
  RS485Serial.println("Number of instances of the char ':' is ");
  RS485Serial.println(numOfTimes);
  delay(5);
  digitalWrite(SSerialTxControl, RS485Receive);  // Disable RS485 Transmit
  delay(5);
}

int getNumOfTimes(String str2Parse, char myChar){
  int strLen = str2Parse.length();
  int numOfTimes = 0;
  int i=0;
  /* char myChar=':'; */
  for (i=0; i<strLen; i++){
    if (str2Parse[i] == myChar){
      numOfTimes += 1;
    }
  }
  return numOfTimes;
}

//*********( THE END )***********//
