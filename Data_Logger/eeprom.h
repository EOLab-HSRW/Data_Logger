#ifndef EEPROM_H
#define EEPROM_H

#define EEPROM_ADDR 0x50  // the default address
#define MAXADD 262143   // max address in byte

#include <Wire.h>
#include "Adafruit_EEPROM_I2C.h"  
#include <Arduino.h> // required for Serial

extern Adafruit_EEPROM_I2C i2ceeprom;
bool eeprom_init();
void readData(long address);
void writeData(long* data, size_t size);
long getCounter();
void setCounter(long counter);
long getAddress();
void setAddress(long address);

#endif