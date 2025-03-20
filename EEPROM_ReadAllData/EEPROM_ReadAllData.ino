#include <Arduino.h> // included for Type String
#include <stdint.h>  // included for Type uint16/8_t
#include "sdcard.h"
#include "eeprom.h"
#include "calculator.h"


void setup() {

  // Initialising Serial
  Serial.begin(115200);
  while (!Serial && millis() < 5000) { delay(100); }

  // Instantiate SD-Card and EEPROM
  eeprom_init();
  sdcard_init();

  // Get Meta Data
  String meta = getMetaData();
  
  // Write Meta Data to Sd Card
  writeFile("/Eeprom.csv", meta.c_str());
  Serial.print("Write Success");

  // Varaibales for getting Sensor Data
  String buffer = "";
  uint16_t readAmount = 50; // amount of how many values has to be read (if all possible values (262.144 - 8(Meta) = 262.136 / 4 (Bytes per Value) = 65.534))
  uint16_t counterAddress = 8;

  // Loop for Concate Sensor Values
  for (int i = 0; i < readAmount; i++) {

    // if it is not the first iteration and 32 Bytes (8 Values) are already in the Buffer (set the size of values to 32Bytes to avoid Stack Overflow)
    if ( counterAddress > 0 && (counterAddress - 8) % 32 == 0) {

      buffer = buffer + getSensorData(counterAddress,i);
      // Write to Sd Card
      writeFile("/Eeprom.csv", buffer.c_str());

      // empty the buffer string
      buffer = "";
    }
    // if it is the first iteration and no 32  Bytes are in the Buffer
    else {
      buffer = buffer + getSensorData(counterAddress,i);
    }
   

    // increase the counter by 4 (4Bytes for 1 value)
    counterAddress = counterAddress + 4;

  }

  // Serial Print Success
  Serial.println("Writing Successful!");
  }

void loop() {
}