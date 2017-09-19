/*
  DualGain.h library for the dual gain module.
*/

#ifndef DualGain_h
#define DualGain_h

#include "Arduino.h"
#include <EEPROM.h>
#include<math.h>



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

#endif
