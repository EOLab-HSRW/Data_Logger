#include <Arduino.h>
String formatToUTC(int year, int month, int day, int hour, int minute, int second) {
  // UTC-FORMAT  (YEAR-MONTH-DAY T HOURS : MINUTES : SECONDS Z)
  char utcString[25];
  
  // Store the Formatted Value in char Buffer
  snprintf(utcString, sizeof(utcString), "%04d-%02d-%02dT%02d:%02d:%02dZ",year, month, day, hour, minute, second);

  return String(utcString);
}