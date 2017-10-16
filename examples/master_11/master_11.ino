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

	// start powerON sequence channels 00-31 @ G1/G2
	digitalWrite(LD1_pin, HIGH);
	digitalWrite(LD2_pin, HIGH);
	digitalWrite(LD3_pin, HIGH);
	digitalWrite(LD4_pin, HIGH);
	delay(100);
	digitalWrite(LD1_pin, LOW);
	digitalWrite(LD2_pin, LOW);
	digitalWrite(LD3_pin, LOW);
	digitalWrite(LD4_pin, LOW);
	delay(900);

  // powerON channels 00-15 @ G1
  powerOn(LD4_pin,(byte)0b11111110);//254
	delay(2000);

	// powerON channels 16-31 @ G1
  powerOn(LD3_pin,(byte)0b11111100);//252
  /* powerOn((byte)0b11111100); */
	delay(2000);

	// powerON channels 00-15 @ G2
  powerOn(LD2_pin,(byte)0b11111000);//248
	delay(2000);


	// powerON channels 16-31 @ G2
  powerOn(LD1_pin,(byte)0b11110000);//240
  delay(2000);

	digitalWrite(LD1_pin, LOW);
  digitalWrite(LD2_pin, LOW);
  digitalWrite(LD3_pin, LOW);
  digitalWrite(LD4_pin, LOW);
 	delay(500);

	// start power ON channels 32-63
	for(byte i=1; i<=2; i++) {
		digitalWrite(LD1_pin, HIGH);
		digitalWrite(LD2_pin, HIGH);
		digitalWrite(LD3_pin, HIGH);
		digitalWrite(LD4_pin, HIGH);
		delay(500);
		digitalWrite(LD1_pin, LOW);
		digitalWrite(LD2_pin, LOW);
		digitalWrite(LD3_pin, LOW);
		digitalWrite(LD4_pin, LOW);
		delay(500);
	}

	// powerON channels 00-15 @ G3
  powerOn(LD4_pin,(byte)0b11100000);//224
	delay(2000);

	// powerON channels 16-31 @ G3
  powerOn(LD3_pin,(byte)0b11000000);//192
	delay(2000);

	// powerON channels 00-15 @ G4
  powerOn(LD2_pin,(byte)0b10000000);//128

  delay(2000);

	// powerON channels 16-31 @ G4
  powerOn(LD1_pin,(byte)0b00000000); //0
	delay(2000);

  digitalWrite(LD1_pin, LOW);
  digitalWrite(LD2_pin, LOW);
  digitalWrite(LD3_pin, LOW);
  digitalWrite(LD4_pin, LOW);

}

void loop() {
	digitalWrite(LD5_pin, HIGH);
	delay(50);
	digitalWrite(LD5_pin, LOW);
	delay(1950);
}
