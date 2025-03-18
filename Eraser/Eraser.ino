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

// function for reading from the EEPROM
void readData(unsigned long address, byte *buffer, unsigned int size) {
  i2ceeprom.read(address, buffer, size);
}


void setup() {
  Serial.begin(115200);
  while (!Serial && millis() < 5000) { delay(100); }

  // Instantiate
  eeprom_init();

  // Step 1 :  Overwrite the first 200 Bytes with the default Value 0xFF
  for (int i = 0; i < 200; i++) {
    i2ceeprom.write(i, 0xFF);
  }
  Serial.println("Overwritten First 200 Bytes completed.");

  // Step 2 : Setting the default Value for the Address Counter 
  // (36 = 0010 0100 = 1001 = 9 .th Byte next free Address)

  i2ceeprom.write(4, 0x24); 
  
  Serial.println("Metadata was set.");
}

void loop() {
}
