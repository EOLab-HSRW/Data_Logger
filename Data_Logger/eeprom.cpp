#include "eeprom.h"

Adafruit_EEPROM_I2C i2ceeprom;

unsigned long addr = 0;
unsigned long eepromSize = MAXADD;

void eeprom_init() {

  // Turning Power Supply On for EEPROM 
  pinMode(WB_IO2, OUTPUT);
  digitalWrite(WB_IO2, HIGH);
   
  delay(300);
  Serial.println("Power on.............");

  // Checking the Connection Access Status
  if (i2ceeprom.begin(EEPROM_ADDR))
    {  
      Serial.println("Found I2C EEPROM");
    }
   else 
    {      
      while (1)
      {
        Serial.println("I2C EEPROM not identified ... check your connections?\r\n");
        delay(10);
      }     
    }
}

// ------------------------------------------------------------------------------
// In Progress
unsigned long address;

// Reading Data from EEPROM
void readData(unsigned long address, byte *buffer, unsigned int size) {
  i2ceeprom.read(address, buffer, size);
  // Hex Conversion if needed when decode String(buffer[i], HEX)
}

// Writing Data
void writeData(unsigned long address,unsigned long data){
  i2ceeprom.write(address,data);
  // Increase The Address Counter for the next Entry
    addr += 32; 
}
// --------------------------------------------------------------------------------