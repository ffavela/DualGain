// Gxcode 0 -> GAIN = 0.029 @ 50ohm / 0.058 @ HZ
// Gxcode 1 -> GAIN = 0.058 @ 50ohm / 0.116 @ HZ
// Gxcode 2 -> GAIN = 0.116 @ 50ohm / 0.228 @ HZ
// Gxcode 3 -> GAIN = 0.228 @ 50ohm / 0.456 @ HZ
// Gxcode 4 -> GAIN = 0.456 @ 50ohm / 0.913 @ HZ
// Gxcode 5 -> GAIN = 0.913 @ 50ohm / 1.816 @ HZ
// Gxcode 6 -> GAIN = 1.816 @ 50ohm / 3.625 @ HZ
// Gxcode 7 -> GAIN = 3.625 @ 50ohm


// 22 giu
// misura del problema di corrente ipotizzato legato ai bit di Gain set

byte release = 3;


#include <EEPROM.h>


// connessioni hardware digitali
byte G1b0_pin 		  = 2;
byte G1b1_pin		  = 4;
byte G1b2_pin 		  = 5;
byte G2b0_pin 		  = 6;
byte G2b1_pin 		  = 7;
byte G2b2_pin 		  = 8;
byte G1VrefPwm_pin    = 3;
byte G2VrefPwm_pin	  = 9;
byte G1G2_VHpwm_pin   = 10;
byte G1G2_VLpwm_pin   = 11;
byte LD6_pin		  = 13;


// connessioni hardware analogiche
byte temp1_pin		  = A0;
byte G1_VrefMon_pin	  = A1;
byte G2_VrefMon_pin	  = A2;
byte G1G2_VHmon_pin   = A3;
byte G1G2_VLmon_pin   = A4;
byte G2Vref_pin 	  = A5;


// definisco variabili per slow control
boolean Zload_50ohm = false;  // servirà per ......?? FORSE A BASSO LIVELLO NON SERVE!!
unsigned int VmonPos = 0;     // valore in bit per il segnale corrispondente due byte up to 1023
unsigned int ImonPos = 0;     // valore in bit per il segnale corrispondente 1023
unsigned int VmonNeg = 0;     // valore in bit per il segnale corrispondente
unsigned int ImonNeg = 0;     // valore in bit per il segnale corrispondente
unsigned int G1_Vos = 0;      // max 2000 - valore in mV della G1_Vos di uscita serve per  calcolo Vref(mV)
unsigned int G2_Vos = 0;
unsigned int VclampPos = 0;   // valore in bit per il segnale corrispondente
unsigned int VclampNeg = 0;   // valore in bit per il segnale corrispondente
unsigned int Temp = 0;        // valore in bit
float G1_Vref        = 0;     // valore in mV per il segnale corrispondente DIPENDE DAL GAIN IMPOSTATO!!
float G2_Vref        = 0;
float G1_PGAgain     = 0;
float G2_PGAgain     = 0;

byte SHDNcodeOld       = 0;
byte SHDNcodeNew       = 0;
byte G1codeOld         = 0;              // codice compreso tra 0 e 7
byte G1codeNew         = 0;
byte G2codeOld         = 0;
byte G2codeNew         = 0;
byte G1_VrefCodeOld    = 0;     // codice in bit da scrivere sul pin di uscita
byte G1_VrefCodeNew    = 0;
byte G2_VrefCodeOld    = 0;
byte G2_VrefCodeNew    = 0;
byte VclampPos_codeOld = 0;     // codice in bit da scrivere sul pin di uscita
byte VclampPos_codeNew = 0;
byte VclampNeg_codeOld = 0;     // codice in bit da scrivere sul pin di uscita
byte VclampNeg_codeNew = 0;



// definisco costanti calibrazione degli ADC e DAC
const float K_VrefSet        = 19.6;       // era 6 // costante per conversione PWM-Analog
const float K_VclampPosSetup = 30.6;       // K_VclampPosSetup = VclampMAX/255      VclampCODE masssimo = 255 @ 8000mV
const float K_VclampNegSet   = 34.9;
const byte  K_VmonPos        = 24;       // VmonPos = VmonPosCODE*K_VmonPos_pin_VALUE         VmonPos massimo = 2500mV @ 1023
const byte  K_VmonNeg        = 24;
const byte  K_VrefMon        = 24;


void setup() {
	pinMode(G1b0_pin,       OUTPUT);
	pinMode(G1b1_pin, 	    OUTPUT);
	pinMode(G1b2_pin, 	    OUTPUT);
	pinMode(G2b0_pin, 	    OUTPUT);
	pinMode(G2b1_pin, 	    OUTPUT);
	pinMode(G2b2_pin, 	    OUTPUT);
	pinMode(G1VrefPwm_pin,  OUTPUT);
	pinMode(G2VrefPwm_pin,  OUTPUT);
	pinMode(G1G2_VHpwm_pin, OUTPUT);
	pinMode(G1G2_VHpwm_pin, OUTPUT);
	pinMode(LD6_pin,		OUTPUT);

	setPwmFrequency(G1VrefPwm_pin, 1);		// D3 imposta la freq. del PWM a 31250Hz
	setPwmFrequency(G2VrefPwm_pin, 1);		// D9 imposta la freq. del PWM a 31250Hz
	setPwmFrequency(G1G2_VHpwm_pin, 1);		// D10 imposta la freq. del PWM a 31250Hz
	setPwmFrequency(G1G2_VLpwm_pin, 1);	    // D11 imposta la freq. del PWM a 31250Hz

	delay(500);
	for(byte i=1; i<=release; i++) {
		digitalWrite(LD6_pin, HIGH);
		delay(100);
		digitalWrite(LD6_pin, LOW);
		delay(500);
	}


	G1gainSetup(7);
	G2gainSetup(5);

	analogWrite(G1VrefPwm_pin,  15);
	analogWrite(G2VrefPwm_pin,  49);
	analogWrite(G1G2_VHpwm_pin, 77);
	analogWrite(G1G2_VLpwm_pin, 77);

// setup per primo test della card - sarà sostituito con la lettura della EEPROM
	// Zload_50ohm = false;  // FORSE A BASSO LIVELLO NON SERVE
	// SHDNcodeOld  = 3;		// "0" tutti spenti "3" tutti accesi!
	// G1_Vos    = 400;     //(G1VrefPwm_pin) deve essere in mV (max 2000)e serve per il calcolo di Vref=G1_Vos/(1+PGAgain) dipende da Zload_50ohm
	// G2_Vos    = 400;	  //(G2VrefPwm_pin)
	// VclampPos = 4800;	  // max=7900mV - valore in mV della tensione di limitazione
	// VclampNeg = 4800;	  // max=8000mV
	// G1codeOld    = 4;   // G1 @ 50 ohm = 0.913
	// G2codeOld    = 2;   // G2 @ 50 ohm = 0.457

// richiama l'ultima configurazione
	// SHDNcodeOld       = EEPROM.read(SHDNcode_addr);
	// G1_VrefCodeOld    = EEPROM.read(G1_VrefCode_addr);
	// G2_VrefCodeOld    = EEPROM.read(G2_VrefCode_addr);
	// VclampPos_codeOld = EEPROM.read(VclampPos_code_addr);
	// VclampNeg_codeOld = EEPROM.read(VclampNeg_code_addr);
	// G1codeOld         = EEPROM.read(G1code_addr);
	// G2codeOld         = EEPROM.read(G2code_addr);

	// VclampPos = VclampPos_code * K_VclampPosSetup;
	// VclampNeg = VclampNeg_code * K_VclampNegSet;
	// G1_Vos =
	// G2_Vos =


// è importante la SEQUENZA per la prima impostazione!!
	// VclampPosSetup (VclampPos);
	// VclampNegSet   (VclampNeg);
	// G1gainSetup    (G1codeOld);         // aggiorna anche Vref!!
	// G2gainSetup    (G2codeOld);
	// SHDNsetUp      (SHDNcodeOld);

	// VmonPos = (analogRead(VmonPos_pin))*K_VmonPos;
	// VmonNeg = (analogRead(VmonNeg_pin))*K_VmonNeg;
	// Vref = (analogRead(G1Vref_pin))*K_VrefMon;


}

void loop() {

	if (analogRead(temp1_pin) > 300) {
		digitalWrite(LD6_pin, HIGH);
		} else {
		digitalWrite(LD6_pin, LOW);
		}
	delay(5);

}


void setPwmFrequency(int pin, int divisor) {
	byte mode;
	if(pin == 5 || pin == 6 || pin == 9 || pin == 10) {
		switch(divisor) {
			case 1: mode = 0x01; break;
			case 8: mode = 0x02; break;
			case 64: mode = 0x03; break;
			case 256: mode = 0x04; break;
			case 1024: mode = 0x05; break;
			default: return;
		}
		if(pin == 5 || pin == 6) {
			TCCR0B = TCCR0B & 0b11111000 | mode;
		}
		else {
			TCCR1B = TCCR1B & 0b11111000 | mode;
		}
	}
	else if(pin == 3 || pin == 11) {
		switch(divisor) {
			case 1: mode = 0x01; break;
			case 8: mode = 0x02; break;
			case 32: mode = 0x03; break;
			case 64: mode = 0x04; break;
			case 128: mode = 0x05; break;
			case 256: mode = 0x06; break;
			case 1024: mode = 0x7; break;
			default: return;
		}
		TCCR2B = TCCR2B & 0b11111000 | mode;
	}
}



// funzioni di SCRITTURA

void G1gainSetup(byte G1code) {
	switch (G1code) {
		case 0:
			G1_PGAgain = 0.08;  // serve per il calcolo di G1_Vref=G1_Vos/(1+G1_PGAgain)
			// G1_VosSetup(G1_Vos);
			digitalWrite(G1b2_pin, LOW); digitalWrite(G1b1_pin, LOW); digitalWrite(G1b0_pin, LOW);
			break;
		case 1:
			G1_PGAgain = 0.16;
			// G1_VosSetup(G1_Vos);
			digitalWrite(G1b2_pin, LOW); digitalWrite(G1b1_pin, LOW); digitalWrite(G1b0_pin, HIGH);
			break;
		case 2:
			G1_PGAgain = 0.32;
			// G1_VosSetup(G1_Vos);
			digitalWrite(G1b2_pin, LOW); digitalWrite(G1b1_pin, HIGH); digitalWrite(G1b0_pin, LOW);
			break;
		case 3:
			G1_PGAgain = 0.63;
			// G1_VosSetup(G1_Vos);
			digitalWrite(G1b2_pin, LOW); digitalWrite(G1b1_pin, HIGH); digitalWrite(G1b0_pin, HIGH);
			break;
		case 4:
			G1_PGAgain = 1.26;
			// G1_VosSetup(G1_Vos);
			digitalWrite(G1b2_pin, HIGH); digitalWrite(G1b1_pin, LOW); digitalWrite(G1b0_pin, LOW);
			break;
		case 5:
			G1_PGAgain = 2.52;  // gain totale = 2 ad 1Mohm
			// G1_VosSetup(G1_Vos);
			digitalWrite(G1b2_pin, HIGH); digitalWrite(G1b1_pin, LOW); digitalWrite(G1b0_pin, HIGH);
			break;
		case 6:
			G1_PGAgain = 5.01;
			// G1_VosSetup(G1_Vos);
			digitalWrite(G1b2_pin, HIGH); digitalWrite(G1b1_pin, HIGH); digitalWrite(G1b0_pin, LOW);
			break;
		case 7:
			G1_PGAgain = 10;
			// G1_VosSetup(G1_Vos);
			digitalWrite(G1b2_pin, HIGH); digitalWrite(G1b1_pin, HIGH); digitalWrite(G1b0_pin, HIGH);
			break;
		default:
			G1_PGAgain = 0.08;
			// G1_VosSetup(G1_Vos);
			digitalWrite(G1b2_pin, LOW); digitalWrite(G1b1_pin, LOW); digitalWrite(G1b0_pin, LOW);
	}
	// EEPROM.write(G1code_addr, G1code);
	// Serial.print("memorizzazione di G1code = ");
	// Serial.println(G1code);
}


void G2gainSetup(byte G2code) {
	switch (G2code) {
		case 0:
			G2_PGAgain = 0.08;  // serve per il calcolo di Vref=G1_Vos/(1+G2_PGAgain)
			// G2_VosSetup(G2_Vos);
			digitalWrite(G2b2_pin, LOW); digitalWrite(G2b1_pin, LOW); digitalWrite(G2b0_pin, LOW);
			break;
		case 1:
			G2_PGAgain = 0.16;
			// G2_VosSetup(G2_Vos);
			digitalWrite(G2b2_pin, LOW); digitalWrite(G2b1_pin, LOW); digitalWrite(G2b0_pin, HIGH);
			break;
		case 2:
			G2_PGAgain = 0.32;
			// G2_VosSetup(G2_Vos);
			digitalWrite(G2b2_pin, LOW); digitalWrite(G2b1_pin, HIGH); digitalWrite(G2b0_pin, LOW);
			break;
		case 3:
			G2_PGAgain = 0.63;
			// G2_VosSetup(G2_Vos);
			digitalWrite(G2b2_pin, LOW); digitalWrite(G2b1_pin, HIGH); digitalWrite(G2b0_pin, HIGH);
			break;
		case 4:
			G2_PGAgain = 1.26;
			// G2_VosSetup(G2_Vos);
			digitalWrite(G2b2_pin, HIGH); digitalWrite(G2b1_pin, LOW); digitalWrite(G2b0_pin, LOW);
			break;
		case 5:
			G2_PGAgain = 2.52;
			// G2_VosSetup(G2_Vos);
			digitalWrite(G2b2_pin, HIGH); digitalWrite(G2b1_pin, LOW); digitalWrite(G2b0_pin, HIGH);
			break;
		case 6:
			G2_PGAgain = 5.01;
			// G2_VosSetup(G2_Vos);
			digitalWrite(G2b2_pin, HIGH); digitalWrite(G2b1_pin, HIGH); digitalWrite(G2b0_pin, LOW);
			break;
		case 7:
			G2_PGAgain = 10;
			// G2_VosSetup(G2_Vos);
			digitalWrite(G2b2_pin, HIGH); digitalWrite(G2b1_pin, HIGH); digitalWrite(G2b0_pin, HIGH);
			break;
		default:
			G2_PGAgain = 0.08;
			// G2_VosSetup(G2_Vos);
			digitalWrite(G2b2_pin, LOW); digitalWrite(G2b1_pin, LOW); digitalWrite(G2b0_pin, LOW);
	}
	// EEPROM.write(G2code_addr, G2code);
	// Serial.print("memorizzazione di G2code = ");
	// Serial.println(G2code);
}


// void G1_VosSetup(float G1_Vos) {
	// G1_Vref = G1_Vos/(1+G1_PGAgain);
	// G1_VrefCode = G1_Vref/K_VrefSet;
	// analogWrite(G1VrefPwm_pin, G1_VrefCode);
	// EEPROM.write(G1_VrefCode_addr, G1_VrefCode);
	// Serial.print ("memorizzazione di G1_VrefCode = ");
	// Serial.println(G1_VrefCode);
// }


// void G2_VosSetup(float G2_Vos) {
	// G2_Vref = G2_Vos/(1+G2_PGAgain);
	// G2_VrefCode = G2_Vref/K_VrefSet;
	// analogWrite(G2VrefPwm_pin, G2_VrefCode);
	// EEPROM.write(G2_VrefCode_addr, G2_VrefCode);
	// Serial.print ("memorizzazione di G2_VrefCode = ");
	// Serial.println(G1_VrefCode);
// }


// void VclampPosSetup(unsigned int VclampPos) {
	// VclampPos_codeNew = VclampPos/K_VclampPosSetup;
	// analogWrite(VclampPosPwm_pin, VclampPos_code);
	// EEPROM.write(VclampPos_code_addr, VclampPos_codeNew);
	// Serial.print ("memorizzazione di VclampPos_code = ");
	// Serial.println(VclampPos_code);
// }


// void VclampNegSet(unsigned int VclampNeg) {
	// VclampNeg_code = VclampNeg/K_VclampNegSet;
	// analogWrite(VclampNegPwm_pin, VclampNeg_code);
	// EEPROM.write(VclampNeg_code_addr, VclampNeg_code);
	// Serial.print ("memorizzazione di VclampNeg_code = ");
	// Serial.println(VclampNeg_code);
// }




//  funzioni per la comunicazione

// void serialEvent() {
	// if (Serial.available() > 0) {
		// command[0] = Serial.read();
		// Serial.print(command[0], HEX);
		// Serial.print(" ");
		// delay(5);
		// command[1] = Serial.read();
		// Serial.print(command[1], HEX);
		// Serial.print(" ");
		// delay(5);
		// command[2] = Serial.read();
		// Serial.print(command[2], HEX);
		// Serial.print(" ");
		// delay(5);
		// if (command[1] == 0x57) {
			// command[3] = Serial.read();
			// Serial.print(command[3], HEX);
			// delay(5);
		// }
		// Serial.println();
		// stringComplete = true;
	// }
// }

// funzioni di SCRITTURA
// void setShdn() {
  // Serial.println("comando_scrittura_1: in esecuzione");
	// if      (command[3] == 0x30) {digitalWrite(serviceLed, LOW);}
	// else if (command[3] == 0x31) {digitalWrite(serviceLed, HIGH);}
	// else if (command[3] == 0x32) {digitalWrite(shutDW1_pin, LOW);}
	// else if (command[3] == 0x33) {digitalWrite(shutDW1_pin, HIGH);}
	// else {Serial.println("comando_scrittura_1: invalid data");}
	// stringComplete = false;
	// Serial.println();
// }
