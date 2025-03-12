#include <Arduino.h>
#include "sdcard.h"
#include "bme680_sensor.h"
#include "eeprom.h"
// include also the RTC File


// Global Buffer  

// Generat an Array in size of the number of Sensor Values
// int[4] + 1 timestamp

int environmentValues[4];
byte buffer[32];



// Function for Getting all the Data from all the Sensors
void get_Values(){

// Get the Values of the Environment Sensor
get_Environment(environmentValues);

  Serial.print("Temperature: ");
  Serial.println(environmentValues[0] / 100.0);

  Serial.print("Pressure: ");
  Serial.println(environmentValues[1] / 100.0);

  Serial.print("Humidity: ");
  Serial.println(environmentValues[2] / 100.0);

  Serial.print("Gas Resisstance: ");
  Serial.println(environmentValues[3] / 100.0);

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


  // Initialising Modules (RTC, EEPROM, BME)

  if (!SD.begin()) {
    Serial.println("Card Mount Failed! Please make sure the card is inserted!");
    return;
  }
  eeprom_init();
  bme680_init();


  // Configure the Instances

  // Set the Date and time 

  // Set EEPROM Counter ( First 20 Bits)

  // Set the Environment Counter ( 18 Bits )

  // Set the Rest Meta ( 26 Bits)
  


}

void loop() {

  // Read every 5.th Minute the Sensor data and 
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

  }



