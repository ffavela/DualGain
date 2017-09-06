/* Flashing LD1 */
/* 06/09/2017 */



#include"DualGain.h"


int LD1_pin = 7;
int LD2_pin = 8;
int LD3_pin = 9;
int LD4_pin = 10;


void setup() {
  pinMode(LD1_pin, OUTPUT);
  pinMode(LD2_pin, OUTPUT);
  pinMode(LD3_pin, OUTPUT);
  pinMode(LD4_pin, OUTPUT);
}

void loop() {
  digitalWrite(LD1_pin, HIGH);
  delay(100);
  digitalWrite(LD1_pin, LOW);
  delay(900);

  digitalWrite(LD2_pin, HIGH);
  delay(100);
  digitalWrite(LD2_pin, LOW);
  delay(900);

  digitalWrite(LD3_pin, HIGH);
  delay(100);
  digitalWrite(LD3_pin, LOW);
  delay(900);

  digitalWrite(LD4_pin, HIGH);
  delay(100);
  digitalWrite(LD4_pin, LOW);
  delay(900);
}

