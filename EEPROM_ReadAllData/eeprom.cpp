#include <Wire.h>
#include "Adafruit_EEPROM_I2C.h"


#define EEPROM_ADDR 0x50  // the I2C Address
#define MAXADD 262143     // Maximum Addresses 

// Instantiate I2C
Adafruit_EEPROM_I2C i2ceeprom;


void eeprom_init() {
  // Power on
  pinMode(WB_IO2, OUTPUT);
  digitalWrite(WB_IO2, HIGH);
  delay(300); // wait for 0.3 Sec
  Serial.println("Power on!");

  // checck the connection to eeprom
  if (i2ceeprom.begin(EEPROM_ADDR)) {  
    Serial.println("I2C EEPROM was found !");
  } else {      
    while (1) {
      Serial.println("I2C EEPROM not identified ... maybe check the connections?");
      delay(10);
    }     
  }
}

// function for reading from eeprom
char readData(unsigned long address) {
  i2ceeprom.read(address);
}
