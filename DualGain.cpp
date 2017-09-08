/*
  DualGain.cpp library for the dual gain module.
*/

#include "Arduino.h"
#include "DualGain.h"
#include<math.h>

int myAwesomeFunction(int myValue)
{
  return 2*myValue;
}

int myAwesomeFunction2(int myValue,int inc)
{
  return (int) 2*myValue*sin(0.4*inc);
}

int myAwesomeFunction3(int myValue,int inc)
{
  return (int) 2*myValue*abs(sin(0.4*inc));
}

int myAwesomeFunction4(int myValue)
{
  if (myValue < 128){
    return 5;
  } else {
    return 0;
  }
}

void myAwesomeWrite(int ledPin, int awesomeValue){
  if (awesomeValue > 0){
    digitalWrite(ledPin, HIGH);
  } else {
    digitalWrite(ledPin, LOW);
  }
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


void G1_VosSetup(float G1_Vos) {
	G1_Vref = G1_Vos/(1+G1_PGAgain);
	G1_VrefCode = G1_Vref/K_VrefSet;
	analogWrite(G1VrefPwm_pin, G1_VrefCode);
	EEPROM.write(G1_VrefCode_addr, G1_VrefCode);
	Serial.print ("memorizzazione di G1_VrefCode = ");
	Serial.println(G1_VrefCode);
}


void G2_VosSetup(float G2_Vos) {
	G2_Vref = G2_Vos/(1+G2_PGAgain);
	G2_VrefCode = G2_Vref/K_VrefSet;
	analogWrite(G2VrefPwm_pin, G2_VrefCode);
	EEPROM.write(G2_VrefCode_addr, G2_VrefCode);
	Serial.print ("memorizzazione di G2_VrefCode = ");
	Serial.println(G1_VrefCode);
}


void VclampPosSetup(unsigned int VclampPos) {
	VclampPos_codeNew = VclampPos/K_VclampPosSetup;
	analogWrite(VclampPosPwm_pin, VclampPos_code);
	EEPROM.write(VclampPos_code_addr, VclampPos_codeNew);
	Serial.print ("memorizzazione di VclampPos_code = ");
	Serial.println(VclampPos_code);
}


void VclampNegSet(unsigned int VclampNeg) {
	VclampNeg_code = VclampNeg/K_VclampNegSet;
	analogWrite(VclampNegPwm_pin, VclampNeg_code);
	EEPROM.write(VclampNeg_code_addr, VclampNeg_code);
	Serial.print ("memorizzazione di VclampNeg_code = ");
	Serial.println(VclampNeg_code);
}


//funzioni per la comunicazione
void serialEvent() {
	if (Serial.available() > 0) {
		command[0] = Serial.read();
		Serial.print(command[0], HEX);
		Serial.print(" ");
		delay(5);
		command[1] = Serial.read();
		Serial.print(command[1], HEX);
		Serial.print(" ");
		delay(5);
		command[2] = Serial.read();
		Serial.print(command[2], HEX);
		Serial.print(" ");
		delay(5);
		if (command[1] == 0x57) {
			command[3] = Serial.read();
			Serial.print(command[3], HEX);
			delay(5);
		}
		Serial.println();
		stringComplete = true;
	}
}

// funzioni di SCRITTURA
void setShdn() {
  Serial.println("comando_scrittura_1: in esecuzione");
	if      (command[3] == 0x30) {digitalWrite(serviceLed, LOW);}
	else if (command[3] == 0x31) {digitalWrite(serviceLed, HIGH);}
	else if (command[3] == 0x32) {digitalWrite(shutDW1_pin, LOW);}
	else if (command[3] == 0x33) {digitalWrite(shutDW1_pin, HIGH);}
	else {Serial.println("comando_scrittura_1: invalid data");}
	stringComplete = false;
	Serial.println();
}
