
#include "eeprom.h"
#include "rtc.h"


void setup() {

  // Initialising Serial 
  Serial.begin(115200);
  while (!Serial && millis() < 5000) { delay(100); }

  // Instantiate
  rtc_init();
  eeprom_init();
  

  // Reset EEPROM , Parameter: uint_16 size for amount of Bytes to overwrite
  // Example First 200 Bytes to 0xFF
  reset(512);

  // Configure the Address 
  configAddress();
}

void loop() {
}
