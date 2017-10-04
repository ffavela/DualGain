#include "DualGain.h"

void setup(){
  Serial.begin(9600);
  while (!Serial){
    ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial.println("Hello World");
  /* byte majorRel; */
  byte releaseArray[2];
  getEEPROMVersion(releaseArray);
  Serial.print("major release: ");
  Serial.println(releaseArray[0]);
  Serial.print("minor release: ");
  Serial.println(releaseArray[1]);


  SlaveStruct slave1 {
    1, //byte slaveNumber
    40017, //unsigned int VclampPos
    58439, //unsigned int VclampNeg
    3.14f, // float G1_Vref
    62.31f // float G2_Vref
  };

  SlaveStruct slave2 {
    2, //byte slaveNumber
    20317, //unsigned int VclampPos
    11424, //unsigned int VclampNeg
    2.71f, // float G1_Vref
    42.3f // float G2_Vref
  };

  SlaveStruct slave3 {
    3, //byte slaveNumber
    10217, //unsigned int VclampPos
    2144, //unsigned int VclampNeg
    2.21f, // float G1_Vref
    22.8f // float G2_Vref
  };

  Serial.println("Writing slave struct");
  writeEEPROMSetting(slave1);
  writeEEPROMSetting(slave2);
  writeEEPROMSetting(slave3);

  Serial.println("Getting the slave struct");
  SlaveStruct s1EEPROMSet=getEEPROMSetting(1);
  SlaveStruct s2EEPROMSet=getEEPROMSetting(2);
  SlaveStruct s3EEPROMSet=getEEPROMSetting(3);

  Serial.println("Now printing the struct values");
  Serial.println("Slave 1");
  Serial.println(s1EEPROMSet.slaveNumber);
  Serial.println(s1EEPROMSet.VclampPos);
  Serial.println(s1EEPROMSet.VclampNeg);
  Serial.println(s1EEPROMSet.G1_Vref);
  Serial.println(s1EEPROMSet.G2_Vref);

  Serial.println();
  
  Serial.println("Slave 2");
  Serial.println(s2EEPROMSet.slaveNumber);
  Serial.println(s2EEPROMSet.VclampPos);
  Serial.println(s2EEPROMSet.VclampNeg);
  Serial.println(s2EEPROMSet.G1_Vref);
  Serial.println(s2EEPROMSet.G2_Vref);

  Serial.println();
  
  Serial.println("Slave 3");
  Serial.println(s3EEPROMSet.slaveNumber);
  Serial.println(s3EEPROMSet.VclampPos);
  Serial.println(s3EEPROMSet.VclampNeg);
  Serial.println(s3EEPROMSet.G1_Vref);
  Serial.println(s3EEPROMSet.G2_Vref);

  Serial.println("DONE!");

  unsigned int VclampPos1;
  unsigned int VclampPos2;

  getEEPROMVclampPos(1,VclampPos1);
  getEEPROMVclampPos(2,VclampPos2);

  /* Serial.println("Using new functions"); */

  /* Serial.print("VclampPos1 = "); */
  /* Serial.println(VclampPos1); */

  /* Serial.print("VclampPos2 = "); */
  /* Serial.println(VclampPos2); */

  Serial.print("sizeof(boolean): ");
  Serial.println(sizeof(boolean));

  Serial.print("sizeof(char): ");
  Serial.println(sizeof(char));

  Serial.print("sizeof(short): ");
  Serial.println(sizeof(short));

  Serial.print("sizeof(int): ");
  Serial.println(sizeof(int));

  Serial.print("sizeof(long): ");
  Serial.println(sizeof(long));

  Serial.print("sizeof(float): ");
  Serial.println(sizeof(float));

  Serial.print("sizeof(double): ");
  Serial.println(sizeof(double));

  Serial.print("sizeof(VclampPos1): ");
  Serial.println(sizeof(VclampPos1));

  Serial.print("sizeof(SlaveStruct): ");
  Serial.println(sizeof(SlaveStruct));

}

void loop(){
  /* nothing for now here */
}