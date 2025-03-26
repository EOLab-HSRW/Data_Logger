#ifndef RTC_H
#define RTC_H


#include "esp32-hal.h"
#include "Melopero_RV3028.h" //http://librarymanager/All#Melopero_RV3028
#include <Wire.h>
#include <Arduino.h>
#include <stdint.h> 
#include "rtc.h"
#include <TimeLib.h>


bool rtc_init();
unsigned long rtcGetTimeLong();
String formatToUTC(time_t time);

#endif