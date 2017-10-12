///////////////////////////////////////////////////////
/* release version */
byte releaseArr[2]={1,1};
//////////////////////////////////////////////////////

// Gxcode 0 -> GAIN = 0.029 @ 50ohm / 0.058 @ HZ
// Gxcode 1 -> GAIN = 0.058 @ 50ohm / 0.116 @ HZ
// Gxcode 2 -> GAIN = 0.116 @ 50ohm / 0.228 @ HZ
// Gxcode 3 -> GAIN = 0.228 @ 50ohm / 0.456 @ HZ
// Gxcode 4 -> GAIN = 0.456 @ 50ohm / 0.913 @ HZ
// Gxcode 5 -> GAIN = 0.913 @ 50ohm / 1.816 @ HZ
// Gxcode 6 -> GAIN = 1.816 @ 50ohm / 3.625 @ HZ
// Gxcode 7 -> GAIN = 3.625 @ 50ohm

// 22.10.2017
// changed comments into english

// 22.06.2017
// misura del problema di corrente ipotizzato legato ai bit di Gain set


/* #include <EEPROM.h> */
#include "DualGain.h"

// hardware digital connections
const byte G1b0_pin 		  = 2;
const byte G1b1_pin		  = 4;
const byte G1b2_pin 		  = 5;
const byte G2b0_pin 		  = 6;
const byte G2b1_pin 		  = 7;
const byte G2b2_pin 		  = 8;
const byte G1VrefPwm_pin    = 3;
const byte G2VrefPwm_pin	  = 9;
const byte G1G2_VHpwm_pin   = 10;
const byte G1G2_VLpwm_pin   = 11;
const byte LD6_pin		  = 13;

// hardware analog connections
const byte temp1_pin		  = A0;
const byte G1_VrefMon_pin	  = A1;
const byte G2_VrefMon_pin	  = A2;
const byte G1G2_VHmon_pin   = A3;
const byte G1G2_VLmon_pin   = A4;
const byte G2Vref_pin 	  = A5;

// slow control variables
boolean Zload_50ohm = false;  // servirà per ......?? FORSE A BASSO LIVELLO NON SERVE!!
unsigned int VmonPos = 0;     // value in bits for the corresponding signal 2 bytes up to 1023
unsigned int ImonPos = 0;     // value in bits for the corresponding signal 1023
unsigned int VmonNeg = 0;     // value in bits for the corresponding signal
unsigned int ImonNeg = 0;     // value in bits for the corresponding signal
unsigned int G1_Vos = 0;      // max 2000 - value in mV of G1_Vos at exit, useful for the Vref(mV) calculation
unsigned int G2_Vos = 0;
unsigned int VclampPos = 0;   // value in bits for the corresponding signal
unsigned int VclampNeg = 0;   // value in bits for the corresponding signal
unsigned int Temp = 0;        // value in bis
float G1_Vref        = 0;     // value in mV for the corresponding signal IT DEPENDS ON THE GAIN SET!!
float G2_Vref        = 0;
float G1_PGAgain     = 0;
float G2_PGAgain     = 0;

byte SHDNcodeOld       = 0;
byte SHDNcodeNew       = 0;
byte G1codeOld         = 0;     // code compressed between 0 and 7
byte G1codeNew         = 0;
byte G2codeOld         = 0;
byte G2codeNew         = 0;
byte G1_VrefCodeOld    = 0;     // bit code to be written to the output pin
byte G1_VrefCodeNew    = 0;
byte G2_VrefCodeOld    = 0;
byte G2_VrefCodeNew    = 0;
byte VclampPos_codeOld = 0;     // bit code to be written to the output pin
byte VclampPos_codeNew = 0;
byte VclampNeg_codeOld = 0;     // bit code to be written to the output pin
byte VclampNeg_codeNew = 0;



// defining calibration constants of the ADC and DAC
const float K_VrefSet        = 19.6;// was 6 // conversion constant for PWM-Analog
const float K_VclampPosSetup = 30.6;// K_VclampPosSetup = VclampMAX/255 VclampCODE maximum = 255 @ 8000mV
const float K_VclampNegSet   = 34.9;
const byte  K_VmonPos        = 24;// VmonPos = VmonPosCODE*K_VmonPos_pin_VALUE  VmonPos maximum = 2500mV @ 1023
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

	setPwmFrequency(G1VrefPwm_pin, 1);// D3 sets the PWM freq. at 31250Hz
	setPwmFrequency(G2VrefPwm_pin, 1);// D9 sets the PWM freq. at 31250Hz
	setPwmFrequency(G1G2_VHpwm_pin, 1);// D10 sets the PWM freq. at 31250Hz
	setPwmFrequency(G1G2_VLpwm_pin, 1);// D11 sets the PWM freq. at 31250Hz

	delay(500);

	/* for(byte i=1; i<=release; i++) { */
	/* 	digitalWrite(LD6_pin, HIGH); */
	/* 	delay(100); */
	/* 	digitalWrite(LD6_pin, LOW); */
	/* 	delay(500); */
	/* } */

  //Blinking the release version
  releaseBlink(LD6_pin,releaseArr);

  //Still need to understand these functions for the wanted gains
	G1gainSetup(7);
	G2gainSetup(5);

	analogWrite(G1VrefPwm_pin,  15);
	analogWrite(G2VrefPwm_pin,  49);
	analogWrite(G1G2_VHpwm_pin, 77);
	analogWrite(G1G2_VLpwm_pin, 77);

}

void loop() {
	if (analogRead(temp1_pin) > 300) {
		digitalWrite(LD6_pin, HIGH);
		} else {
		digitalWrite(LD6_pin, LOW);
		}
	delay(5);
}
