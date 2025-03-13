#include <Arduino.h>
#include "sdcard.h"
#include "bme680_sensor.h"
#include "eeprom.h"
#include "rtc.h"

// Global Variables 

unsigned long timestamp;
const int measurement_interval = 300000; // 5 minutes

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
  //                  - Set EEPROM Counter ( First 20 Bits) -> Set Function() from eeprom
  //                  - Set the Environment Counter ( 18 Bits )
  //                  - Set the Rest Meta ( 26 Bits)
  


}

void loop() {

  // get current timestamp
  timestamp = millis(); // replace with rtc if available

  // get current values of the sensor

  get_Values();


  // Data
  unsigned char data = 0;

  // --------------- Stopped Here--------------------------------------------
  // writing values to EEPROM
    //writeData(eeprom_address, data);
    
    // writing the values to the sdcard
    //char* log_entry = String(environmentValues[0]) + "," + String(environmentValues[1]) + "," + String(environmentValues[2]) + "," + String(environmentValues[3])+","+ String(timestamp)+",";
    // writeFile("datalog.csv", log_entry);


    // delay until next measurement time
    delay(measurement_interval);

  }



