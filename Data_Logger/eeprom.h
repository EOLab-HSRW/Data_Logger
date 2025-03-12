#ifndef EEPROM_H
#define EEPROM_H

#define EEPROM_ADDR 0x50  // the default address
#define MAXADD 262143   // max address in byte

#include <Wire.h>
#include "Adafruit_EEPROM_I2C.h"  
#include <Arduino.h> // required for Serial

extern Adafruit_EEPROM_I2C i2ceeprom;
void eeprom_init();
void readData(unsigned long address, byte *buffer, unsigned int size);
void writeData(unsigned long address,unsigned long data);

#endif