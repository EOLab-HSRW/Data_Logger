// Serial.printf("%d:%d:%d %d/%d/%d \n",rtc.getHour(),rtc.getMinute(),rtc.getSecond(),rtc.getYear(),rtc.getMonth(),rtc.getDate());
#include "Melopero_RV3028.h" //http://librarymanager/All#Melopero_RV3028
#include <Arduino.h>
#include <stdint.h> 
#include "eeprom.h"
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
  rtc.setTime(2025, 3, 20, 30, 0, 0, 0);
  
}