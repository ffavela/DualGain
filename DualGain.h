/*
  DualGain.h library for the dual gain module.
*/

#ifndef DualGain_h
#define DualGain_h
#endif

#include "Arduino.h"
#include <EEPROM.h>
#include<math.h>

#define SHIFT 2 //EEPROM shift first 2 bytes are for the version

int myAwesomeFunction(int);
int myAwesomeFunction2(int,int);
int myAwesomeFunction3(int,int);
int myAwesomeFunction4(int);

void myAwesomeWrite(int, int);

void setPwmFrequency(int pin, int divisor);

//Writting functions
void G1gainSetup(byte G1code);
void G2gainSetup(byte G2code);
void G1_VosSetup(float G1_Vos);
void G2_VosSetup(float G2_Vos);
void VclampPosSetup(unsigned int VclampPos);
void VclampNegSet(unsigned int VclampNeg);

//Communication functions
void serialEvent(void);


//...more writting functions
void setShdn(void);

void releaseBlink(byte ledPin, byte *releaseArr);


//EEPROM memory functions
struct SlaveStruct {
  byte slaveNumber;
  unsigned int VclampPos;
  unsigned int VclampNeg;
  float G1_Vref;
  float G2_Vref;
};

void getEEPROMVersion(byte releaseArray[2]);
void writeEEPROMSetting( SlaveStruct );
SlaveStruct getEEPROMSetting(byte slaveNumber);

void getEEPROMVclampPos(byte slaveNumber, unsigned int VclampPos);

//Direct functions, no need to read entire struct

//This ones for getting the address
/* int getVclampPosAddr(byte slaveNum); */
/* int getVclampNegAddr(byte slaveNum); */
/* int getG1_VrefAddr(byte slaveNum); */
/* int getG2_VrefAddr(byte slaveNum); */

/* //This ones for getting the values */
/* int getVclampPos(byte slaveNum); */
/* int getVclampNeg(byte slaveNum); */
/* float getG1_Vref(byte slaveNum); */
/* float getG2_Vref(byte slaveNum); */
