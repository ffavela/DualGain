#include"DualGain.h"

#define Pin13LED  13
int x = 0;    // variable
byte state = HIGH;

String myString="";
void mySerialFunct(void);

//The structure to write into the EEPROM, change accordingly
IDStruct idStruct = {.typeID='S',// either 'M' or 'S' for master or
				 // slave
                     .numberID=2,// the number of master or slave
		     .serialID=13};// the serial board ID, identical
				    // to the numberID of a master

IDStruct localID;

byte eeAddr=0;

void setup() {
  Serial.begin(9600);      // open the serial port at 9600 bps:
  pinMode(Pin13LED, OUTPUT);
  writeEEPROMStructID(&idStruct);
}

void loop() {
  if (Serial.available() > 0)
    {
      myString = Serial.readStringUntil('$');
      Serial.println(myString);

      if(myString == "ID"){
        getEEPROMStructID(&localID);

        Serial.println("Printing info");
        Serial.print("Type: ");
        Serial.println(localID.typeID);

        Serial.print("numberID: ");
        Serial.println(localID.numberID);

	Serial.print("serialID: ");
        Serial.println(localID.serialID);
      }
      myString="";
    }
}
