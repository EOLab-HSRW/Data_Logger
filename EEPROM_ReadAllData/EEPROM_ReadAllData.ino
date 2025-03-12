#define EEPROM_ADDR 0x50  // The I2C-Address from EEPROM
#define MAXADD 262143     // Max Address in EEPROM (for 256 KB)

#include <Wire.h>
#include "Adafruit_EEPROM_I2C.h"
#include <SPI.h>
#include <SD.h>

// Generating Instance of I2C-EEPROM
Adafruit_EEPROM_I2C i2ceeprom;


// Initialising Function for EEPROM
void eeprom_init() {

  // Turning Power Supply on for EEPROM 
  pinMode(WB_IO2, OUTPUT);
  digitalWrite(WB_IO2, HIGH);
  // Waitin 0.3s
  delay(300);
  Serial.println("Power on.............");

  // Checking the Connection to EEPROM
  if (i2ceeprom.begin(EEPROM_ADDR)) {  
    Serial.println("Found I2C EEPROM");
  } else {      
    while (1) {
      Serial.println("I2C EEPROM not identified ... check your connections?");
      delay(10);
    }     
  }
}

// Reading Data from EEPROM
void readData(unsigned long address, byte *buffer, unsigned int size) {
  i2ceeprom.read(address, buffer, size);
}

// Writing to the SD-Card
void writeFile(const char *path, const char *message) {
  Serial.printf("Writing file: %s\n", path);
  File file = SD.open(path, FILE_APPEND);
  if (file) {
    file.print(", "); // Seperation
    if (file.print(message)) {
      Serial.println("File written.");
    } else {
      Serial.println("Write failed.");
    }
    file.println();
    file.close();
  } else {
    Serial.println("Failed to open file for writing.");
    return;
  }
}

// Deleting existing File (Refresh)
void deleteFile(const char *path) {
  Serial.printf("Deleting file: %s\n", path);
  if (SD.remove(path)) {
    Serial.println("File deleted.");
  } else {
    Serial.println("Delete failed.");
  }
}

void setup() {
  // Set Timeout for Serial Connection Check
  time_t timeout = millis();
  Serial.begin(115200);
  while (!Serial) {
    if ((millis() - timeout) < 5000) {
      delay(100);
    } else {
      break;
    }
  }
  // Initialising EEPROM and SD-Card
  eeprom_init();

  if (!SD.begin()) { 
    Serial.println("SD Card initialization failed!");
    return;
  }
  Serial.println("SD Card initialized.");

  // Read Data 32 Bytes From EEPROM and Writing it to the SD Card from the Buffer with Sizeof 32 Bytes
  byte buffer[32];
  unsigned long addr = 0;
  unsigned long eepromSize = MAXADD;

  // Storing Data in the Buffer
  while (addr < eepromSize) {
    readData(addr, buffer, 32);
    String message = "";
    for (int i = 0; i < 32; i++) {
      // Conversion to Hexadecimal
      message += String(buffer[i], HEX) + " "; 
    }
    // Writing the Data to the File
    writeFile("/Test.txt", message.c_str()); 
    // Increase the Counter to the Next 32 Bytes
    addr += 32; 
  }

  Serial.println("Successfully written on the SD-Card.");
}

void loop() {
}
