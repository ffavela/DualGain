#include <Wire.h>

void setup() {
	Wire.begin();
	delay(1000);
	}
void loop() {
	//imposto tutti i pin al livello logico alto
	Wire.beginTransmission(0x38);	//comincia la trasmissione con il PRIMO PCF8574 codificato con 0x38, il secondo sarà.....?
	Wire.write((byte)0b11111111);	//invio un byte
	Wire.endTransmission();			//fine trasmissione
	delay(1000);
	//imposto tutti i pin al livello logico basso
	Wire.beginTransmission(0x38);
	Wire.write((byte)0b00000000);
	Wire.endTransmission();
	delay(1000);
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