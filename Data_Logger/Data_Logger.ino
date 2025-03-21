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
unsigned long timestamp;               // Declaration for using it in the loop
const int measurement_interval = 5000; // 5 minutes



// Function for Getting all the Data from all the Sensors
void get_Values(){

  // Get the Values of the Environment Sensor
  get_Environment(environmentValues);

  // Append here other Sensors ....
}

void setup() {

  // Start by Initialising the Serial Communication
  time_t timeout = millis();
  Serial.begin(115200);
  while (!Serial) {
    if ((millis() - timeout) < 5000) {
      delay(100);
    } else {
      break;
    }
  }


  // Initialising Modules (SD,RTC, EEPROM, BME)

  sdcard_init();
  eeprom_init();
  bme680_init();
  rtc_init();

}

void loop() {

  // get current timestamp
  timestamp = rtcGetTimeLong();
  Serial.print("Timestamp: "); Serial.println(timestamp);
  // get current values of the sensor
  get_Values();

  // combine timestamp and current values

    long data[AMOUNTOFVALUES+1];
    memcpy(data, environmentValues, AMOUNTOFVALUES * sizeof(long));
    memcpy(data +  AMOUNTOFVALUES , &timestamp, sizeof(long));


  // get the length of the sensor value array
  size_t size = AMOUNTOFVALUES + 1;

  // write the data to the EEPROM   
  writeData(data, size);

  String log_entry = combineToString(data,size);
  
  // Write the log into the sd card
  writeFile("/data.csv", log_entry.c_str());

  // delay until next measurement time
  // delay(measurement_interval);

  // Deep Sleep
  esp_sleep_enable_timer_wakeup(5 * 60 * 1000000);  // 5 Min = 5 * 60 = 300 Sekunde * 1 000 000 Mikrosekunde = 300 000 000 Mikrosekunde 
  esp_deep_sleep_start();

  }



