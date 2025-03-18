#include <Wire.h>
#include "Adafruit_EEPROM_I2C.h"
#include <SPI.h>
#include <SD.h>

#define EEPROM_ADDR 0x50  // the I2C Address
#define MAXADD 262143     // Maximum Addresses 

// Instantiate I2C
Adafruit_EEPROM_I2C i2ceeprom;

// Instantiate Function
void eeprom_init() {
  // Power on
  pinMode(WB_IO2, OUTPUT);
  digitalWrite(WB_IO2, HIGH);
  delay(300); // wait for 0.3 Sec
  Serial.println("Power on !");

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
void readData(unsigned long address, byte *buffer, unsigned int size) {
  i2ceeprom.read(address, buffer, size);
}

// function for writing on the sd card
void writeFile(const char *path, const char *message) {
  Serial.printf("Schreibe Datei: %s\n", path);
  File file = SD.open(path, FILE_APPEND);
  if (file) {
    if (file.print(message)) {
      Serial.println("file written !");
    } else {
      Serial.println("writing failed !");
    }
    file.println();
    file.close();
  } else {
    Serial.println("opening file failed !");
  }
}

void setup() {
  Serial.begin(115200);
  while (!Serial && millis() < 5000) { delay(100); }

  // Instantiate
  eeprom_init();

  if (!SD.begin()) { 
    Serial.println("failed!");
    return;
  }
  Serial.println("success ! ");

  // data to write on the sd card
  byte buffer[32]; // buffer for writing at once
  unsigned long addr = 0;
  const unsigned long eepromSize = 256; // only read 100 Bytes
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