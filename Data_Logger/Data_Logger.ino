#include <Arduino.h>
#include "sdcard.h"
#include "bme680_sensor.h"
#include "eeprom.h"
#include "rtc.h"

// Global Variables 

unsigned long timestamp;               // Declaration for using it in the loop
const int measurement_interval = 500000; // 5 minutes


// There are two needed changes to reuse this sketch for your purpose
// 1) Calculate the total amount of values that needs to be collected
//    do changes in the code below accordingly (resize the global Variables)
// 2) Write a Getter Function for reading the new added Sensor Type
//    and use it here
// Generat an Array with the size of the amount of Sensor Values

// Environment Data Storage
long environmentValues[4];

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


  // Set the Date and time (RTC)
  


}

void loop() {

  // get current timestamp
  timestamp = millis(); // replace with rtc if available
  Serial.print("Timestamp: "); Serial.println(timestamp);

  // get current values of the sensor
  get_Values();

  Serial.println("Sensor Values:");
  Serial.print("Temperature: "); Serial.println(environmentValues[0]);
  Serial.print("Pressure: "); Serial.println(environmentValues[1]);
  Serial.print("Humidity: "); Serial.println(environmentValues[2]);
  Serial.print("Gas Resistance: "); Serial.println(environmentValues[3]);

  // combine timestamp and current values

    long data[5];
    memcpy(data, environmentValues, 4 * sizeof(long));
    memcpy(data +  4 , &timestamp, sizeof(long));
    Serial.println("Data to be written to EEPROM:");
    for (int i = 0; i < 5; i++) {
  Serial.print("Data["); Serial.print(i); Serial.print("]: ");
  Serial.println(data[i]);
  }

  // get the length of the sensor value array
  size_t size =  (sizeof(data) / sizeof(data[0])) ;
  Serial.print("Data size: "); Serial.println(size);

  // write the data to the EEPROM   
   writeData(data, size);

  // --------------------------------------------------------------------------- Refactor needed
  // combine the values to a String for writing it to the sd card
  String log_entry = String(environmentValues[0]) + "," + String(environmentValues[1]) + "," + String(environmentValues[2]) + "," + String(environmentValues[3]) + "," + String(timestamp) + ",";
  
  // Write the log into the sd card
  writeFile("/data.csv", log_entry.c_str());

  // delay until next measurement time
  delay(measurement_interval);

  }



