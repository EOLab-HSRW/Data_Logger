#include <Arduino.h>
#include "sdcard.h"
#include "bme680_sensor.h"
#include "eeprom.h"
#include "rtc.h"

// Global Variables 

unsigned long timestamp;
const int measurement_interval = 5000; // 5 minutes / Test 10 Sec

// ------------------------------------------------------------------
// Only do changes here

// There are two needed changes to reuse this sketch for your purpose

// 1) Calculate the total amount of values that needs to be collected
//    do changes in the code below accordingly (resize the global Variables )

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

// ------------------------------------------------------------------

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


  // Configuration : 
  //                  - Set the Date and time (RTC)

  //                  - Set EEPROM Counter ( First 20 Bits) -> Set Fudnction() from eeprom
  //                  - Start Address at 65 because 64 Bit s of Meta Data
  //                  - Set the Environment Counter ( 18 Bits )
  //                  - Set the Rest Meta ( 26 Bits)
  


}

void loop() {

  // get current timestamp
  timestamp = millis(); // replace with rtc if available

  // get current values of the sensor
  get_Values();

  // combine timestamp and current values

    long data[5];
    memcpy(data, environmentValues, 4 * sizeof(long));
    memcpy(data +  4 , &timestamp, sizeof(long));

  // get the length of the sensor value array
  size_t size =  (sizeof(data) / sizeof(data[0])) ;

  // write the data to the EEPROM   
   writeData(data, size);


  // combine the values to a String for writing it to the sd card
  String log_entry = String(environmentValues[0]) + "," + String(environmentValues[1]) + "," + String(environmentValues[2]) + "," + String(environmentValues[3]) + "," + String(timestamp) + ",";
  
  // Write the log into the sd card
  writeFile("/data.csv", log_entry.c_str());

  // delay until next measurement time
  delay(measurement_interval);

  }



