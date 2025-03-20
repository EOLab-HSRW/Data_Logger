#ifndef EEPROM_H
#define EEPROM_H


void eeprom_init();
char readData(unsigned long address);
void readBuffer(uint16_t addr, uint8_t *buffer, uint16_t num);
#endif