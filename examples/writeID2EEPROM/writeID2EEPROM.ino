#include"DualGain.h"

#define Pin13LED         13
int x = 0;    // variable
byte state = HIGH;

String myString="";
void mySerialFunct(void);

/* struct idStruct{ */
/*   'M'; //char typeID; */
/*    0; //int numberID; */
/* }; */

IDStruct idStruct = {.typeID='S',
                     .numberID=777};

IDStruct localID;

/* struct idEEPROM{ */
/*   'M'; //char typeID; */
/*    0; //int numberID; */
/* }; */


void setup() {
  Serial.begin(9600);      // open the serial port at 9600 bps:
  pinMode(Pin13LED, OUTPUT);
  /* writeEEPROMStructID(idStruct); */
  /* byte eeAddr=0; */
  /* EEPROM.put(eeAddr,idStruct); */
  /* writeEEPROMStructID(&idStruct); */
}

void loop() {
  byte eeAddr=0;
  if (Serial.available() > 0)
    {
      myString = Serial.readStringUntil('$');
      Serial.println(myString);

      if(myString == "ID"){
        getEEPROMStructID(&localID);

        Serial.println("Printing info");
        Serial.print("Type: ");
        Serial.println(localID.typeID);

        Serial.print("number: ");
        Serial.println(localID.numberID);
      }
      myString="";
    }
}
