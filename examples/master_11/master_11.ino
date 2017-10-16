///////////////////////////////////////////////////////
/* release version */
byte releaseArr[2]={1,1};
//////////////////////////////////////////////////////

// 12.10.2017
// Modified the comments added a powerOn/Off functions

// 03.10.2017
// Added release blink function, still need to test on DG

// 14.09.2017
// aggiunta sequenza dopo scheda funzionante

// 11.09.2017
// aggiunta una sequenza di powerOn dei gruppi di PGAs

#include <Wire.h>
#include "DualGain.h"

const byte LD1_pin =  7;
const byte LD2_pin =  8;
const byte LD3_pin =  9;
const byte LD4_pin = 10;
const byte LD5_pin = 13;

//Pointing to the LD1_pin address
const byte *LDPointer=&LD1_pin;

void setup() {
	Wire.begin();
	delay(5);

	pinMode(LD1_pin, OUTPUT);
	pinMode(LD2_pin, OUTPUT);
	pinMode(LD3_pin, OUTPUT);
	pinMode(LD4_pin, OUTPUT);
	pinMode(LD5_pin, OUTPUT);

  //The new function 
  powerOff();

  //Blinking the release version
  releaseBlink(LD5_pin,releaseArr);

  //turn power on all groups
  powerOnGroup(LDPointer);
}

void loop() {
	digitalWrite(LD5_pin, HIGH);
	delay(50);
	digitalWrite(LD5_pin, LOW);
	delay(1950);
}
