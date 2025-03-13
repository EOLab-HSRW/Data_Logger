#include <Arduino.h>
#include "sdcard.h"
#include "bme680_sensor.h"
#include "eeprom.h"
#include "rtc.h"

// Global Variables 

unsigned long timestamp;
int eeprom_address = 0;
const int measurement_interval = 300000; // 5 minutes

// Global Buffer to read 32 Bits at once
byte buffer[32];

// ------------------------------------------------------------------
// Only do changes here

// There are two needed changes to reuse this sketch for your purpose

// 1) Calculate the total amount of values that needs to be collected
//    do changes in the code below accordingly (resize the global Variables )

// 2) Write a Getter Function for reading the new added Sensor Type
//    and use it here

// Generat an Array with the size of the amount of Sensor Values

// Environment Data Storage
int environmentValues[4];


// Function for Getting all the Data from all the Sensors
void get_Values(){

// Get the Values of the Environment Sensor
  get_Environment(environmentValues);

// Append here other Sensors ....

}

// -----------------------------------------------------------

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

  // write it to the EEPROM and onto the SD-Card

  // Use for that: get_Environment()
  // Get also the Timestamp from RTC

  // Get them into 32 Bit Format if necessary
  
  // Storing Data in the Buffer

  // Split up the 32 Bit int into 4 pieces of 8 Bit to store them in 4 seperated addresses ( just for EEPROM)

  // Functions that can be used
  //readData(addr, buffer, 32);
  //writeFile("/Test.txt", );
  // void readData(unsigned long address, byte *buffer, unsigned int size);
  // void writeData(unsigned long address,unsigned long data);
  // void readFile(const char *path);
  // void writeFile(const char *path, const char *message);
  // void deleteFile(const char *path);
  // int[] get_Environment();


  // Data
  unsigned char data = 0;

  // --------------- Hier noch bearbeiten fehler 
  // writing values to EEPROM
    //writeData(eeprom_address, data);
    
    // writing the values to the sdcard
    //char* log_entry = String(environmentValues[0]) + "," + String(environmentValues[1]) + "," + String(environmentValues[2]) + "," + String(environmentValues[3])+","+ String(timestamp)+",";
    // writeFile("datalog.csv", log_entry);


    // delay until next measurement time
    delay(measurement_interval);

  }



