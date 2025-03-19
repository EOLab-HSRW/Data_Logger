#include "sdcard.h"
#include "eeprom.h"

void setup() {

  // Initialising Serial
  Serial.begin(115200);
  while (!Serial && millis() < 5000) { delay(100); }

  // Instantiate SD-Card and EEPROM
  eeprom_init();
  sdcard_init();
 

  // Writing 32 Bytes at once to the sd card

  // data to write on the sd card
  byte buffer[32]; // buffer for writing at once
  unsigned long addr = 0;
  const unsigned long eepromSize = 256; // only read 256 Bytes
  unsigned long bytesRead = 0;

  while (bytesRead < eepromSize) {
    unsigned int chunkSize = min((unsigned long)32, eepromSize - bytesRead);
    readData(addr, buffer, chunkSize);
    
    String message = "";
    for (int i = 0; i < chunkSize; i++) {
      message += String(buffer[i], HEX) + " ";
    }
    
    writeFile("/Test.txt", message.c_str());
    
    addr += chunkSize;
    bytesRead += chunkSize;
  }

  Serial.println("Writing Successfull !");
}

void loop() {
}