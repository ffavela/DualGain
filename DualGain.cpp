/*
  DualGain.cpp library for the dual gain module.
*/

#include "Arduino.h"
#include "DualGain.h"
#include<math.h>

// sull pin imposta la freq. del PWM a 31250Hz
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

// writting functions
void G1gainSetup(byte G1code) {
  float G1_PGAgain     = 0;

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
  float G2_PGAgain;

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

float GgainSetup(float G_PGAgain, byte G2code) {
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

	switch (G2code) {
		case 0:
			G_PGAgain = 0.08;  // serve per il calcolo di Vref=G1_Vos/(1+G2_PGAgain)
			// G2_VosSetup(G2_Vos);
			digitalWrite(G2b2_pin, LOW); digitalWrite(G2b1_pin, LOW); digitalWrite(G2b0_pin, LOW);
			break;
		case 1:
			G_PGAgain = 0.16;
			// G2_VosSetup(G2_Vos);
			digitalWrite(G2b2_pin, LOW); digitalWrite(G2b1_pin, LOW); digitalWrite(G2b0_pin, HIGH);
			break;
		case 2:
			G_PGAgain = 0.32;
			// G2_VosSetup(G2_Vos);
			digitalWrite(G2b2_pin, LOW); digitalWrite(G2b1_pin, HIGH); digitalWrite(G2b0_pin, LOW);
			break;
		case 3:
			G_PGAgain = 0.63;
			// G2_VosSetup(G2_Vos);
			digitalWrite(G2b2_pin, LOW); digitalWrite(G2b1_pin, HIGH); digitalWrite(G2b0_pin, HIGH);
			break;
		case 4:
			G_PGAgain = 1.26;
			// G2_VosSetup(G2_Vos);
			digitalWrite(G2b2_pin, HIGH); digitalWrite(G2b1_pin, LOW); digitalWrite(G2b0_pin, LOW);
			break;
		case 5:
			G_PGAgain = 2.52;
			// G2_VosSetup(G2_Vos);
			digitalWrite(G2b2_pin, HIGH); digitalWrite(G2b1_pin, LOW); digitalWrite(G2b0_pin, HIGH);
			break;
		case 6:
			G_PGAgain = 5.01;
			// G2_VosSetup(G2_Vos);
			digitalWrite(G2b2_pin, HIGH); digitalWrite(G2b1_pin, HIGH); digitalWrite(G2b0_pin, LOW);
			break;
		case 7:
			G_PGAgain = 10;
			// G2_VosSetup(G2_Vos);
			digitalWrite(G2b2_pin, HIGH); digitalWrite(G2b1_pin, HIGH); digitalWrite(G2b0_pin, HIGH);
			break;
		default:
			G_PGAgain = 0.08;
			// G2_VosSetup(G2_Vos);
			digitalWrite(G2b2_pin, LOW); digitalWrite(G2b1_pin, LOW); digitalWrite(G2b0_pin, LOW);
	}
	// EEPROM.write(G2code_addr, G2code);
	// Serial.print("memorizzazione di G2code = ");
	// Serial.println(G2code);
	return G_PGAgain;
}

// void G1_VosSetup(float G1_Vos) {
// 	G1_Vref = G1_Vos/(1+G1_PGAgain);
// 	G1_VrefCode = G1_Vref/K_VrefSet;
// 	analogWrite(G1VrefPwm_pin, G1_VrefCode);
// 	EEPROM.write(G1_VrefCode_addr, G1_VrefCode);
// 	Serial.print ("memorizzazione di G1_VrefCode = ");
// 	Serial.println(G1_VrefCode);
// }


// void G2_VosSetup(float G2_Vos) {
// 	G2_Vref = G2_Vos/(1+G2_PGAgain);
// 	G2_VrefCode = G2_Vref/K_VrefSet;
// 	analogWrite(G2VrefPwm_pin, G2_VrefCode);
// 	EEPROM.write(G2_VrefCode_addr, G2_VrefCode);
// 	Serial.print ("memorizzazione di G2_VrefCode = ");
// 	Serial.println(G1_VrefCode);
// }


// void VclampPosSetup(unsigned int VclampPos) {
// 	VclampPos_codeNew = VclampPos/K_VclampPosSetup;
// 	analogWrite(VclampPosPwm_pin, VclampPos_code);
// 	EEPROM.write(VclampPos_code_addr, VclampPos_codeNew);
// 	Serial.print ("memorizzazione di VclampPos_code = ");
// 	Serial.println(VclampPos_code);
// }


// void VclampNegSet(unsigned int VclampNeg) {
// 	VclampNeg_code = VclampNeg/K_VclampNegSet;
// 	analogWrite(VclampNegPwm_pin, VclampNeg_code);
// 	EEPROM.write(VclampNeg_code_addr, VclampNeg_code);
// 	Serial.print ("memorizzazione di VclampNeg_code = ");
// 	Serial.println(VclampNeg_code);
// }


//funzioni per la comunicazione
// void serialEvent() {
// 	if (Serial.available() > 0) {
// 		command[0] = Serial.read();
// 		Serial.print(command[0], HEX);
// 		Serial.print(" ");
// 		delay(5);
// 		command[1] = Serial.read();
// 		Serial.print(command[1], HEX);
// 		Serial.print(" ");
// 		delay(5);
// 		command[2] = Serial.read();
// 		Serial.print(command[2], HEX);
// 		Serial.print(" ");
// 		delay(5);
// 		if (command[1] == 0x57) {
// 			command[3] = Serial.read();
// 			Serial.print(command[3], HEX);
// 			delay(5);
// 		}
// 		Serial.println();
// 		stringComplete = true;
// 	}
// }

// funzioni di SCRITTURA
// void setShdn() {
//   Serial.println("comando_scrittura_1: in esecuzione");
// 	if      (command[3] == 0x30) {digitalWrite(serviceLed, LOW);}
// 	else if (command[3] == 0x31) {digitalWrite(serviceLed, HIGH);}
// 	else if (command[3] == 0x32) {digitalWrite(shutDW1_pin, LOW);}
// 	else if (command[3] == 0x33) {digitalWrite(shutDW1_pin, HIGH);}
// 	else {Serial.println("comando_scrittura_1: invalid data");}
// 	stringComplete = false;
// 	Serial.println();
// }

//Blinks the release version
void releaseBlink(byte ledPin, byte *releaseArr){
  byte majorRel=releaseArr[0];
  byte minorRel=releaseArr[1];

  byte i=0;
  digitalWrite(ledPin,LOW);
  delay(5);

  //Blinking the major release
  for (i=0;i<majorRel;i++){
    digitalWrite(ledPin, HIGH);
    delay(400);
    digitalWrite(ledPin, LOW);
    delay(400);
  }

  // delay(400);
  //Blinking the minor release
  for (i=0;i<minorRel;i++){
    digitalWrite(ledPin, HIGH);
    delay(200);
    digitalWrite(ledPin, LOW);
    delay(400);
  }
}

//EEPROM functions
void getEEPROMStructID(IDStruct *idStruct){
  byte eeAddr= 0;
  EEPROM.get(eeAddr,*idStruct);
}

void writeEEPROMStructID(IDStruct *idStruct){
  byte eeAddr=0;
  //put will only write if the value is different from the already
  //present in memory
  EEPROM.put(eeAddr,*idStruct);
}

//Slave number starts from 1 THIS ONE SHOULD BE USED
void writeEEPROMSetting(SlaveStruct *slaveSettings){
  byte slaveNumber = slaveSettings->slaveNumber;
  int eeAddr=SHIFT-1;
  eeAddr += (slaveNumber - 1)*sizeof(SlaveStruct);
  // EEPROM.put(eeAddr,slaveSettings); //Old way

  //Updating each variable, put() only writes if there was a change
  EEPROM.put(eeAddr,slaveSettings->slaveNumber);
  eeAddr += sizeof(slaveSettings->slaveNumber);

  EEPROM.put(eeAddr,slaveSettings->VclampPos);
  eeAddr += sizeof(slaveSettings->VclampPos);

  EEPROM.put(eeAddr,slaveSettings->VclampNeg);
  eeAddr += sizeof(slaveSettings->VclampNeg);

  EEPROM.put(eeAddr,slaveSettings->G1_Vref);
  eeAddr += sizeof(slaveSettings->G1_Vref);

  EEPROM.put(eeAddr,slaveSettings->G2_Vref);
  eeAddr += sizeof(slaveSettings->G2_Vref);//No more vars but I'll
                                          //leave it
}
//This one should be used
SlaveStruct getEEPROMSetting(byte slaveNumber){
  SlaveStruct mySlaveSetting;
  int eeAddr=SHIFT-1;//addresses start from 0...
  eeAddr += (slaveNumber - 1)*sizeof(SlaveStruct);
  EEPROM.get(eeAddr,mySlaveSetting);
  return mySlaveSetting;
}

//Direct functions, deprecated
void getEEPROMVclampPos(byte slaveNumber, unsigned int VclampPos){
  int eeAddr=SHIFT;
  int interval=0; //To jump over blocks of slave data
  interval+=sizeof(byte);//a byte that represents slave number
  interval+=sizeof(int);//the VclampPos integer
  interval+=sizeof(int);//the VclampNeg integer
  interval+=sizeof(float);//the G1_Vref float
  interval+=sizeof(float);//the G2_Vref float

  eeAddr+=(slaveNumber - 1)*interval;
  //Now getting the local VclampPos address
  eeAddr+=sizeof(byte);//Finally at VclampPos

}

// int getVclampPosAddr(byte slaveNum){
//   int eeAddr=SHIFT; //First 2 bytes are for the version
//   eeAddr += (slaveNumber - 1)*sizeof(SlaveStruct);
//   eeAddr += sizeof(byte);
//   int VclampPos;
//   EEPROM.put(eeAddr,VclampPos);
//   return VclampPos;
// }

// int getVclampPos(byte slaveNum){
//   int eeAddr=getVclampPosAddr(slaveNum);
//   EEPROM.get(eeAddr,mySlaveSetting);
// }

//powerOn and powerOff the channels
void powerOff(void){
  Wire.beginTransmission(0x20);
  // "0x20 because the chip is of type "PCF8574" it starts the
  // transmission with the first PCF8574 coded with 0x38, the second
  // will be...?
  Wire.write((byte)0b11111111);
  //sends a byte - the PGA is in powerOFF if the level is high
  Wire.endTransmission();
}

void powerOn(byte ledPin, byte chanInfo){
  //Negate the bytes so we get the PCF8574 convention where on is 0
  //and on is one
  chanInfo= (byte) ~chanInfo; //the byte cast is for making sure
			      //nothing weird happens during the
			      //negation
  Wire.beginTransmission(0x20);
  // "0x20 because the chip is of type "PCF8574" it starts the
  // transmission with the first PCF8574 coded with 0x38, the second
  // will be...?
  Wire.write(chanInfo);
  digitalWrite(ledPin, HIGH);
  // turnOnOffLeds(ledInfo);
  Wire.endTransmission();
}

byte powerOnGroup(byte powerByte){
  //Getting back the led pins
  const byte LD1_pin =  7;
  const byte LD2_pin =  8;
  const byte LD3_pin =  9;
  const byte LD4_pin = 10;
  const byte LD5_pin = 13;

  const byte LD_pins[8] = {LD4_pin,LD3_pin,LD2_pin,
			   LD1_pin,LD4_pin,LD3_pin,
			   LD2_pin,LD1_pin};

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

  // powerON channels
  // i=0; 00-15 @ G1
  // i=1; 16-31 @ G1
  // i=2; 00-15 @ G2
  // i=3; 16-31 @ G2
  for (byte i = 0; i < 4; i++){
    powerByte=turnOnK(powerByte, i);
    powerOn(LD_pins[i], powerByte);
    //Check current here
    //If current not ok ==> powerByte=turnOffK(powerByte, i);
    delay(2000);
  }

  for (byte i = 0; i < 4; i++){
    digitalWrite(LD_pins[i],LOW);
    delay(500);
  }

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

  // powerON channels
  // i=4; 00-15 @ G3
  // i=5; 16-31 @ G3
  // i=6; 00-15 @ G4
  // i=7; 16-31 @ G4
  for (byte i = 4; i < 8; i++){
    powerByte=turnOnK(powerByte, i);
    powerOn(LD_pins[i], powerByte);
    //Check current here
    //If current not ok ==> powerByte=turnOffK(powerByte, i);
    delay(2000);
  }

  for (byte i = 4; i < 8; i++){
    digitalWrite(LD_pins[i],LOW);
    delay(500);
  }
}

// Returns a number that has all bits same as n
// except the k'th bit which is made 0
byte turnOffK(byte n, byte k) {
    // k must be positive and less than 8
    if (k < 0 || k >= 9)
      return n;

    // Do & of n with a number with all set bits except
    // the k'th bit
    return (byte) (n & ~((byte)BIT_0 << k));
    /* return (byte) (n ^ (1 << k)); //this one toggles */
}

// Returns a number that has all bits same as n
// except the k'th bit which is made 1
byte turnOnK(byte n, byte k) {
    // k must be positive 0 and less than 8
    if (k < 0 || k >= 9)
      return n;

    // Do & of n with a number with all set bits except
    // the k'th bit
    return (byte) (n | ((byte)BIT_0 << k));
}

byte checkBitK(byte n, byte k){
    if (k < 0 || k >= 9)
      return (byte) 0; //False

    if ( (n & ((byte)BIT_0 << k)) != 0)
      return (byte) 1; //True
}

//Values have to be integers between 0 and 100
byte getAnalogValue(byte percentage){
  if (percentage > 100)
    percentage=100;
  float frac = (float)percentage/100.0;
  return (byte) (frac*255);
}

void setDutyCycle(byte G_pin, byte percentage){
  byte analogVal=getAnalogValue(percentage);
  analogWrite(G_pin, analogVal);
}
