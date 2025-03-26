#ifndef EEPROM_H
#define EEPROM_H

#include <Arduino.h>
#include <stdint.h>
#include <Wire.h>
#include "Adafruit_EEPROM_I2C.h"

#define EEPROM_ADDR 0x50  // I2C Address
#define MAXADD 262143     // Maximum Addresses



void eeprom_init();
void readData(unsigned long address, byte *buffer, unsigned int size);
void reset(long size);
void configAddress();

#endif