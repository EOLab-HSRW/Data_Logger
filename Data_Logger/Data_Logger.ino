
#include <Arduino.h>
#include "sdcard.h"
#include "bme680_sensor.h"
#include "eeprom.h"
#include "rtc.h"

// Edit Here
#define AMOUNTOFVALUES 4

// There are two needed changes to reuse this sketch for your purpose
// 1) Calculate the total amount of values that needs to be collected
//    change the variable mountOfValues accordingly
// 2) Write a Getter Function for reading the new added Sensor Type
//    and use it here (Important the Return Value has to be long)

// Environment Data Storage
long environmentValues[AMOUNTOFVALUES];
unsigned long timestamp;  // Declaration for using it in the loop

// Checking Module Avalablity
bool sd_ok = false;
bool eeprom_ok = false;
bool bme_ok = false;
bool rtc_ok = false;



// Function for Getting all the Data from all the Sensors
void get_Values() {

  // Get the Values of the Environment Sensor
  get_Environment(environmentValues);

  // Append here other Sensors ....
}

void setup() {

  if (esp_sleep_get_wakeup_cause() == ESP_SLEEP_WAKEUP_TIMER) {
    Serial.println("woke up from deep sleep!");
  } else {
    Serial.println("normal start!");
  }

  Serial.begin(115200);
 
  delay(100);  // wait until serial communication established

  Serial.println("ESP32 startet...");

  //  initialise sd card module
  for (int i = 0; i < 3; i++) {  // try 3 times
    if (sdcard_init()) {
      sd_ok = true;
      break;
    }
    Serial.println("⚠️ sd-card-init failed, please retry...");
    delay(500);
  }

  // initialise eeprom
  for (int i = 0; i < 3; i++) {
    if (eeprom_init()) {
      eeprom_ok = true;
      break;
    }
    Serial.println("⚠️ EEPROM-Init failed, please retry...");
    delay(500);
  }

  // initialise bme680 module
  for (int i = 0; i < 3; i++) {
    if (bme680_init()) {
      bme_ok = true;
      break;
    }
    Serial.println("⚠️ BME680-Init failed, please retry...");
    delay(500);
  }

  // initialise rtc module
  for (int i = 0; i < 3; i++) {
    if (rtc_init()) {
      rtc_ok = true;
      break;
    }
    Serial.println("⚠️ RTC-Init failed, please retry...");
    delay(500);
  }

  if (!sd_ok || !eeprom_ok || !bme_ok || !rtc_ok) {
    Serial.println("🚨 Failed to initialising one ore more modules ! restarting...");
    delay(5000);
    ESP.restart();
  }

  Serial.println("✅ Successfully initialised all modules !");
}

void loop() {

  // get current timestamp
  timestamp = rtcGetTimeLong();
  Serial.print("Timestamp: ");
  Serial.println(timestamp);
  // get current values of the sensor
  get_Values();

  // combine timestamp and current values

  long data[AMOUNTOFVALUES + 1];
  memcpy(data, environmentValues, AMOUNTOFVALUES * sizeof(long));
  memcpy(data + AMOUNTOFVALUES, &timestamp, sizeof(long));


  // get the length of the sensor value array
  size_t size = AMOUNTOFVALUES + 1;

  // write the data to the EEPROM
  writeData(data, size);

  String log_entry = combineToString(data, size);

  // Write the log into the sd card
  writeFile("/data.csv", log_entry.c_str());


  Serial.println("Sleeping for 30 seconds !");
  // Deep Sleep
  esp_sleep_enable_timer_wakeup(30 * 1000000);  // 5 Min = 5 * 60 = 300 seconds * 1 000 000 mikroseconds = 300 000 000 microseconds
  esp_deep_sleep_start();
}
