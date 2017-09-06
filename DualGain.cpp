/*
  Morse.cpp - Library for flashing Morse code.
  Created by David A. Mellis, November 2, 2007.
  Released into the public domain.
*/

// #include "WProgram.h"
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

