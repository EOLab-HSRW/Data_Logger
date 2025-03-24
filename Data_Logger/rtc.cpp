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
  return true;
} 
unsigned long rtcGetTimeLong(){

// Setting the current value as timestamp to easily get easily the needed format

uint16_t year = rtc.getYear();
uint8_t month = rtc.getMonth();
uint8_t day = rtc.getDate();
uint8_t hour = rtc.getHour();
uint8_t minute = rtc.getMinute();
uint8_t second = rtc.getSecond();


// struct for setting the valuue
tmElements_t tm;
// year needs to be a vlue that is the result of the subtraction from current year and 1970
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


