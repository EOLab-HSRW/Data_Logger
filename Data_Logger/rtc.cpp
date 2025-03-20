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
  
  // Set Time Format from 12 to 24 Hours
  rtc.set24HourMode();

  // Set the date and time
  // year, month, weekday, date, hour, minute, second
  // Note: time is always set in 24h format
  // Note: month value ranges from 1 (Jan) to 12 (Dec)
  // Note: date value ranges from 1 to 31
  rtc.setTime(2025, 3, 4,20, 16, 45, 0);
  
} 

unsigned long rtcGetTimeLong(){

uint32_t unixtime = rtc.getUnixTime();

return unixtime;
}

