#include "eeprom.h"


void setup() {

  // Initialising Serial
  Serial.begin(115200);
  while (!Serial && millis() < 5000) { delay(100); }

  // Instantiate
  eeprom_init();

  // Reset EEPROM , Parameter: uint_16 size for amount of Bytes to overwrite
  // Example First 200 Bytes to 0xFF
  reset(200);

  // Configure the Address 
  configAddress();
}

void loop() {
}
