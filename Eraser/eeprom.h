#ifndef EEPROM_H
#define EEPROM_H

void eeprom_init();
void readData(unsigned long address, byte *buffer, unsigned int size);
void reset(long size);
void configAddress();

#endif