#include <Arduino.h>
#include "sdcard.h"
#include "bme680_sensor.h"

#define SEALEVELPRESSURE_HPA (1010.0)

// Set the size equal to the amount of Values available
int[10] values;

// Get all Sensor Data
void get_Values(){

// Get the Values of the Environment Sensor
int[] environment = get_Environment();

// Append here other Sensors ....


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

// Checking the Connection to the SD-Card Module
  if (!SD.begin()) {
    Serial.println("Card Mount Failed! Please make sure the card is inserted!");
    return;
  }

// Initialise the Environment Sensor
  bme680_init();

// Clear the Last entry File
  deleteFile("/Test.txt");
}

void loop() {
  if (!bme.performReading()) {
    Serial.println("Failed to perform reading :(");
  }

 // ACTIVE --------------------------------------------
  int[] values = get_Va();

  writeFile("/Test.txt", values);

  delay(5000);
}