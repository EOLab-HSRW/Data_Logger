#include <Arduino.h>
#include "sdcard.h"
#include "bme680_sensor.h"

#define SEALEVELPRESSURE_HPA (1010.0)

void setup() {
  
  time_t timeout = millis();
  Serial.begin(115200);
  while (!Serial) {
    if ((millis() - timeout) < 5000) {
      delay(100);
    } else {
      break;
    }
  }

  if (!SD.begin()) {
    Serial.println("Card Mount Failed! Please make sure the card is inserted!");
    return;
  }

  bme680_init();

  deleteFile("/Test.txt");
}

void loop() {
  if (!bme.performReading()) {
    Serial.println("Failed to perform reading :(");
  }

  String bmeData = bme680_get();
  Serial.println(bmeData);

  writeFile("/Test.txt", bmeData.c_str());

  delay(5000);
}