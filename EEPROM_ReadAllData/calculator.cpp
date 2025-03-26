#include <Arduino.h>
#include <stdint.h> 
#include "rtc.h"
#include "eeprom.h"
#define METADATABYTES 8
#define SENSORDATABYTES 4

// Array for the Meta Data
uint8_t arr[METADATABYTES];
uint16_t start = 0;
uint16_t num = 8;

// Variables for Getting Sensor Data
uint8_t buffer[SENSORDATABYTES];
uint16_t byteAmount = SENSORDATABYTES;


String getMetaData() {
  readBuffer(start, arr, num);

  // Calculate Total Counter
  // 16 - 4 = 12 | 8 - 4 = 4 | 0 - 4 = -4
  unsigned long totalCounter = ((unsigned long)arr[0] << 12);
  totalCounter = totalCounter + ((unsigned long)arr[1] << 4);
  totalCounter = totalCounter + ((unsigned long)arr[2] >> 4);

  // Calculate Address
  unsigned char firstByte = arr[2] << 4;
  firstByte = firstByte >> 4;

  // 16-2  = 14 |  8-2 = 6 | 0 - 2 = -2 ;
  unsigned long address = ((unsigned long)firstByte << 14);
  address = address + ((unsigned long)arr[3] << 6);
  address = address + ((unsigned long)arr[4] >> 2);

  // Calculate Free Space  (Only if necessary for stored further data)
  unsigned char lastByte = arr[4] << 6;
  lastByte = lastByte >> 6;

  unsigned long freespace = ((unsigned long)lastByte << 24);
  freespace = freespace + ((unsigned long)arr[5] << 16);
  freespace = freespace + ((unsigned long)arr[6] << 8);
  freespace = freespace + ((unsigned long)arr[7]);


  // Convert to String and float and divide by 100
  String counter = String(totalCounter);
  String addressString = String(address);
  String free = String(freespace);

  String meta = counter + "," + addressString + "," + free +"\n";

  return meta;
}

String getSensorData(uint16_t counterAddress, int i,int size) {

  readBuffer(counterAddress, buffer, byteAmount);

  // Read 4 Bytes
  char one = buffer[0];
  char two = buffer[1];
  char three = buffer[2];
  char four = buffer[3];

  // Combine to long
  unsigned long value = ((unsigned long)(one << 24)) + ((unsigned long)(two << 16)) + ((unsigned long)(three << 8)) + (unsigned long)four;

  //  (i+1) % 5 because of index starting by 0 

  if(i != 0 && (i + 1) % 6 == 0) {
    // if the next value is the timestamp than don t divide it by 100
    // Use Timelib for Converting the unsigned long to UTC (because of same length) 
    time_t time = (time_t) value;
    String times = formatToUTC(value);  // format
    return times + "\n";
  } 
  else{
    // Divide to get float values
    float val = (float)value / 100;
    return String(val) + ",";
  }
}
