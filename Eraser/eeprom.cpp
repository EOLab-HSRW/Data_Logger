#include <Wire.h>
#include "Adafruit_EEPROM_I2C.h"

#define EEPROM_ADDR 0x50  // I2C Address
#define MAXADD 262143     // Maximum Addresses

// Instantiate I2C
Adafruit_EEPROM_I2C i2ceeprom;

// Initialising Function
void eeprom_init() {
  // Power On
  pinMode(WB_IO2, OUTPUT);
  digitalWrite(WB_IO2, HIGH);
  delay(300); // Wait 0.3 Sec
  Serial.println("Power On...");

  // Checking Connection to EEPROM
  if (i2ceeprom.begin(EEPROM_ADDR)) {  
    Serial.println("Found !");
  } else {      
    while (1) {
      Serial.println("I2C EEPROM couldn t be identified ... maybe check connections?");
      delay(10);
    }     
  }
}

void reset(long size){
  // Overwrite the Bytes by the amount of the size parameter 
  // default Value 0xFF for void
  for (int i = 0; i < size; i++) {
    i2ceeprom.write(i, 0x00);
  }
  Serial.println("Overwrite completed.");
}

void configAddress(){

  // Setting the default Value for the Address Counter 
  // (0x20 (16)  =  32 (10) = 0010 0000 (Shift by 2 to left for matching the position in meta data) = 1000 = 8 .th Byte next free Address  0-7 Meta)
  i2ceeprom.write(4, 0x20);
  Serial.println("Address Configuration successfull !");
}

// function for reading from the EEPROM
void readData(unsigned long address, byte *buffer, unsigned int size) {
  i2ceeprom.read(address, buffer, size);
}