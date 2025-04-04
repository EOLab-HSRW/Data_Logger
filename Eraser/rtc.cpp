#include "esp32-hal.h"
#include "Melopero_RV3028.h" //http://librarymanager/All#Melopero_RV3028
#include <Wire.h>
#include <Arduino.h>
#include <stdint.h> 
#include "rtc.h"


Melopero_RV3028 rtc;

void rtc_init() {
  Wire.begin();
  rtc.initI2C();
  // Setting Power Switching Config (in case of disconnection from power to activate directly to backup supply) 
  rtc.writeToRegister(0x35,0x00);  
  rtc.writeToRegister(0x37,0xB4);

  // Setting the Date for First time during Configuration
  uint16_t year = 2025;
  uint8_t month = 3;
  uint8_t weekday = 1;   
  uint8_t date = 24;
  uint8_t hour = 15;
  uint8_t minute = 17;
  uint8_t second = 1;

  Serial.println("Date:" + String(year));

  rtc.setTime(year, month, weekday, date, hour, minute, second);
} 

