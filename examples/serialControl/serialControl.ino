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
int blkInt=100;

unsigned long previousMillis = 0;
/* const long interval = 100; */
int ledState = LOW;

/*-----( Declare Functions )-----*/
unsigned long myBlink(unsigned long, String, int);
String getState(String);
void sendRS485Data(String);
int getNumOfTimes(String);
/* boolean checkFields(int fieldN, String str2Parse, char myChar); */
String getValue(String str2Parse, char myChar, int myIdx);
boolean isStringInt(String myStr);

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
    int numOfTimes=0;
    int strLength=someInfo.length();
    numOfTimes=getNumOfTimes(someInfo,':');
    if (numOfTimes > 0 && numOfTimes < strLength){
      String mySubStr1=getValue(someInfo,':',0);
      RS485Serial.println(mySubStr1);

      String mySubStr2=getValue(someInfo,':',1);
      if(mySubStr1=="b" && isStringInt(mySubStr2)){
        blkInt=mySubStr2.toInt();
        state="b";
      }
  }

    someInfo = "";

    stringComplete = false;
  }

  previousMillis=myBlink(currentMillis,state,blkInt);
}//--(end main loop )---

/*-----( Declare User-written Functions )-----*/
//NONE

unsigned long myBlink(unsigned long currentMillis,
                      String state="n",int blinkInterval=100) {
  if (state != "b") {
    return currentMillis;
  }

  if (currentMillis - previousMillis >= blinkInterval) {
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
  int strLength=someInfo.length();
  RS485Serial.println(strLength);
  numOfTimes=getNumOfTimes(someInfo,':');
  RS485Serial.println("Number of instances of the char ':' is ");
  RS485Serial.println(numOfTimes);
  if (numOfTimes > 0 && numOfTimes < strLength){
    String mySubStr=getValue(someInfo,':',0);
    RS485Serial.print("First string: ");
    RS485Serial.println(mySubStr);
    RS485Serial.print("First string integer?: ");
    RS485Serial.println(isStringInt(mySubStr));

    mySubStr=getValue(someInfo,':',1);
    RS485Serial.print("Second string: ");
    RS485Serial.println(mySubStr);
    RS485Serial.print("Second string integer?: ");
    RS485Serial.println(isStringInt(mySubStr));
  }
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

/* boolean checkFields(int fieldN, String str2Parse, char myChar){ */
/*   nOT=getNumOfTimes(str2Parse,myChar); */
/*   if ( nOT != fieldN-1){ */
/*     return false; */
/*   } */

/* } */

String getValue(String str2Parse, char myChar, int myIdx){
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = str2Parse.length()-1;

  for(int i=0; i<=maxIndex && found<=myIdx; i++){
    if(str2Parse.charAt(i)==myChar || i==maxIndex){
        found++;
        strIndex[0] = strIndex[1]+1;
        strIndex[1] = (i == maxIndex) ? i+1 : i;
    }
  }
  return found>myIdx ? str2Parse.substring(strIndex[0], strIndex[1]) : "";
}

boolean isStringInt(String myStr){
  int i=0;
  char myChar=myStr[0];
  int strLength=myStr.length();
  while (i < strLength){
    myChar=myStr[i];
    if(!isDigit(myChar)){
      return false;
    }
    i++;
  }
  return true;
}
//*********( THE END )***********//
