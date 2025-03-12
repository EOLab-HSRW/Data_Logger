#include "eeprom.h"

Adafruit_EEPROM_I2C i2ceeprom;

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

unsigned long address;

// Reading data
void readData(){
  i2ceeprom.read(g_random_addr);
}

// Writing Data
void writeData(){
  i2ceeprom.write(g_random_addr,g_write_data);
}
