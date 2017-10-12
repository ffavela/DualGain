// 14.09.2017
// aggiunta sequenza dopo scheda funzionante


// 11.09.2017
// aggiunta una sequenza di powerOn dei gruppi di PGAs

// 03.10.2017
// Added release blink function, still need to test on DG


#include <Wire.h>
#include "DualGain.h"
byte release = 3;
byte releaseArr[2]={1,0};

byte LD1_pin =  7;
byte LD2_pin =  8;
byte LD3_pin =  9;
byte LD4_pin = 10;
byte LD5_pin = 13;


void setup() {
	Wire.begin();
	delay(5);

	pinMode(LD1_pin, OUTPUT);
	pinMode(LD2_pin, OUTPUT);
	pinMode(LD3_pin, OUTPUT);
	pinMode(LD4_pin, OUTPUT);
	pinMode(LD5_pin, OUTPUT);

	// powerOFF all channels
	Wire.beginTransmission(0x20);	// "0x20 perche il chip è di tipo "PCF8574" comincia la trasmissione con il PRIMO PCF8574 codificato con 0x38, il secondo sarà.....?
	Wire.write((byte)0b11111111);	// invio un byte - il PGA è in powerOFF se il livello è alto
	Wire.endTransmission();

	/* for(byte i=1; i<=release; i++) { */
	/* 	digitalWrite(LD5_pin, HIGH); */
	/* 	delay(100); */
	/* 	digitalWrite(LD5_pin, LOW); */
	/* 	delay(500); */
	/* } */

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
	Wire.beginTransmission(0x20);	// "0x20 perche il chip è di tipo "PCF8574" comincia la trasmissione con il PRIMO PCF8574 codificato con 0x38, il secondo sarà.....?
	Wire.write((byte)0b11111110);	// invio un byte - il PGA è in powerOFF se il livello è alto
	Wire.endTransmission();
	digitalWrite(LD4_pin, HIGH);
	delay(2000);

	// powerON channels 16-31 @ G1
	Wire.beginTransmission(0x20);	// "0x20 perche il chip è di tipo "PCF8574" comincia la trasmissione con il PRIMO PCF8574 codificato con 0x38, il secondo sarà.....?
	Wire.write((byte)0b11111100);	// invio un byte - il PGA è in powerOFF se il livello è alto
	Wire.endTransmission();
	digitalWrite(LD3_pin, HIGH);
	delay(2000);

	// powerON channels 00-15 @ G2
	Wire.beginTransmission(0x20);	// "0x20 perche il chip è di tipo "PCF8574" comincia la trasmissione con il PRIMO PCF8574 codificato con 0x38, il secondo sarà.....?
	Wire.write((byte)0b11111000);	// invio un byte - il PGA è in powerOFF se il livello è alto
	Wire.endTransmission();
	digitalWrite(LD2_pin, HIGH);
	delay(2000);

	// powerON channels 16-31 @ G2
	Wire.beginTransmission(0x20);	// "0x20 perche il chip è di tipo "PCF8574" comincia la trasmissione con il PRIMO PCF8574 codificato con 0x38, il secondo sarà.....?
	Wire.write((byte)0b11110000);	// invio un byte - il PGA è in powerOFF se il livello è alto
	Wire.endTransmission();
	digitalWrite(LD1_pin, HIGH);
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
	Wire.beginTransmission(0x20);	// "0x20 perche il chip è di tipo "PCF8574" comincia la trasmissione con il PRIMO PCF8574 codificato con 0x38, il secondo sarà.....?
	Wire.write((byte)0b11100000);	// invio un byte - il PGA è in powerOFF se il livello è alto
	Wire.endTransmission();
	digitalWrite(LD4_pin, HIGH);
	delay(2000);

	// powerON channels 16-31 @ G3
	Wire.beginTransmission(0x20);	// "0x20 perche il chip è di tipo "PCF8574" comincia la trasmissione con il PRIMO PCF8574 codificato con 0x38, il secondo sarà.....?
	Wire.write((byte)0b11000000);	// invio un byte - il PGA è in powerOFF se il livello è alto
	Wire.endTransmission();
	digitalWrite(LD3_pin, HIGH);
	delay(2000);

	// powerON channels 00-15 @ G4
	Wire.beginTransmission(0x20);	// "0x20 perche il chip è di tipo "PCF8574" comincia la trasmissione con il PRIMO PCF8574 codificato con 0x38, il secondo sarà.....?
	Wire.write((byte)0b10000000);	// invio un byte - il PGA è in powerOFF se il livello è alto
	Wire.endTransmission();
	digitalWrite(LD2_pin, HIGH);
	delay(2000);

	// powerON channels 16-31 @ G4
	Wire.beginTransmission(0x20);	// "0x20 perche il chip è di tipo "PCF8574" comincia la trasmissione con il PRIMO PCF8574 codificato con 0x38, il secondo sarà.....?
	Wire.write((byte)0b00000000);	// invio un byte - il PGA è in powerOFF se il livello è alto
	Wire.endTransmission();
	digitalWrite(LD1_pin, HIGH);
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


/*
void turnON(byte SHDNcode) {		// SHDNcode: 1 to 8 - "1" for CHs 00-15 @gain 1, "2" for CHs 16-31 @ gain1, "3" for CHs 00-15 @gain2, "4" for CHs 16-31 @ gain2, "5" for CHs 00-15 @ gain3 .......
	Wire.beginTransmission(0x38);	//comincia la trasmissione
	switch (SHDNcode) {
		case 0:
			Wire.write((byte)0b111111110);
			break;
		case 1:
			digitalWrite(SHDN1_pin, LOW);  // il THS7001 si "accende" quando il senale è LOW
			digitalWrite(SHDN2_pin, HIGH);      // sostituisci con funzione tipo G1gainSetup()
			break;
		case 2:
			digitalWrite(SHDN1_pin, HIGH);  // il THS7001 si "accende" quando il senale è LOW
			digitalWrite(SHDN2_pin, LOW);      // sostituisci con funzione tipo G1gainSetup()
			break;
		case 3:
	Wire.write((byte)0b11111111);	//invio un byte
	Wire.endTransmission();			//fine trasmissione
	delay(1000);
	}






// Avendo espresso il valore in forma binaria riusciamo facilmente ad accendere o spegnere ogni led cambiando il valore di ogni singolo bit. Ad esempio questo codice accende e spegne solo il led sulla porta P0:


#include <Wire.h>

void setup()
{
Wire.begin();
delay(1000);
}
void loop()
{
//imposto il pin P0 al livello
//logico alto
Wire.beginTransmission(0x38);
//invio un byte
Wire.write((byte)0b00000001);
//fine trasmissione
Wire.endTransmission();
delay(1000);
//imposto il pin P0 al livello
//logico basso
Wire.beginTransmission(0x38);
//invio un byte
Wire.write((byte)0b00000000);
//fine trasmissione
Wire.endTransmission();
delay(1000);
}

*/
