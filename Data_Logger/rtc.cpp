#include "esp32-hal.h"
#include "Melopero_RV3028.h" //http://librarymanager/All#Melopero_RV3028
#include <Wire.h>
#include <Arduino.h>
#include <stdint.h> 
#include "rtc.h"
#include <TimeLib.h>


Melopero_RV3028 rtc;

bool rtc_init() {
  Wire.begin();
  rtc.initI2C();
  Serial.println( String( rtc.getYear() ) );
  return true;
} 
unsigned long rtcGetTimeLong(){

uint16_t year = rtc.getYear();
uint8_t month = rtc.getMonth();
uint8_t day = rtc.getDate();
uint8_t hour = rtc.getHour();
uint8_t minute = rtc.getMinute();
uint8_t second = rtc.getSecond();

tmElements_t tm;
tm.Year = year - 1970 ;   
tm.Month = month;
tm.Day = day;
tm.Hour = hour;
tm.Minute = minute;
tm.Second = second;

String serial = String(rtc.getYear()) +"///"+ String(year)+"-"+String(month)+"-"+String(day)+"T"+" "+String(hour)+":"+String(minute)+":"+String(second)+"Z"; 

Serial.println(serial.c_str());

time_t unixtime = makeTime(tm);
Serial.println("Timestamp"+String(unixtime));
unsigned long tim = (unsigned long) unixtime;  

return tim;
}


