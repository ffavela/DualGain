/*-----( Import needed libraries )-----*/
#include <SoftwareSerial.h>
/*-----( Declare Constants and Pin Numbers )-----*/
#define SSerialRX        10  //Serial Receive pin
#define SSerialTX        11  //Serial Transmit pin

#define SSerialTxControl 3   //RS485 Direction control
#define RS485Transmit    HIGH
#define RS485Receive     LOW

#define Pin13LED         13

SoftwareSerial RS485Serial(SSerialRX, SSerialTX); // RX, TX

String myString="";
String myLocalString="";

void sendRS485Data(String myString);
void mySerialFunct(void);

void setup()
{
  // Start the built-in serial port, probably to Serial Monitor
  Serial.begin(9600);
  Serial.println("SerialRemote");  // Can be ignored

  pinMode(Pin13LED, OUTPUT);
  pinMode(SSerialTxControl, OUTPUT);

  digitalWrite(SSerialTxControl, RS485Receive);  // Init Transceiver

  // Start the software serial port, to another device
  RS485Serial.begin(4800);   // set the data rate
}


void loop()
{
  if (RS485Serial.available() > 0){
    myString=RS485Serial.readStringUntil('$');
    sendRS485Data("Master 1: ");
    myString+='$';
    sendRS485Data(myString);
    Serial.print(myString);
    delay(40);//Waiting for the Serial buffer to get filled

    if (Serial.available()){
      myLocalString = Serial.readStringUntil('$');
      sendRS485Data("Master 1 slave response: ");
      sendRS485Data(myLocalString);
    }
  }
}

void sendRS485Data(String myString){
  digitalWrite(SSerialTxControl, RS485Transmit); // Enable RS485 Transmit
  RS485Serial.println(myString);
  delay(3); //This seems important
  digitalWrite(SSerialTxControl, RS485Receive);  // Disable RS485 Transmit
}
