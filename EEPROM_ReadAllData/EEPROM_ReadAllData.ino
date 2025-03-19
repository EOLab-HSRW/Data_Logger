#include "sdcard.h"
#include "eeprom.h"

#define MAXADDRESS 512
#define METADATABYTES 8



void setup() {

  // Initialising Serial
  Serial.begin(115200);
  while (!Serial && millis() < 5000) { delay(100); }

  // Instantiate SD-Card and EEPROM
  eeprom_init();
  sdcard_init();

  // Decoder ---------------------------------------------------------------------
  // For writing an optimum amount of Bytes at once and reduce over usage
  // converting them accordingly to the scheme of Meta Data and Sensor Data


  // Cofiguration

  // amount of needed Bytes
  const unsigned long bytesAtOnce = 256;

  // Array for the Meta Data
  char arr[METADATABYTES];

  // Meta Data (First 8 Bytes)

  for (int i = 0; i < METADATABYTES; i++) {
    arr[i] = readData(i);
  }

  // Calculate Total Counter

  // 16 - 4 = 12 | 8 - 4 = 4 | 0 - 4 = -4

  long totalCounter = ((long)arr[0] << 12);
  totalCounter = totalCounter + ((long)arr[1] << 4);
  totalCounter = totalCounter + ((long)arr[2] >> 4);

  // Calculate Address

  unsigned char firstByte = arr[2] << 4;
  firstByte = firstByte >> 4;

  // 16-2  = 14 |  8-2 = 6 | 0 - 2 = -2 ;
  long address = ((long)firstByte << 14);
  address = address + ((long)arr[3] << 6);
  address = address + ((long)arr[4] >> 2);

  // Calculate Free Space  (Only if necessary for stored further data)

  unsigned char lastByte = arr[4] << 6;
  lastByte = lastByte >> 6;


  long freespace = ((long)lastByte << 24);
  freespace = freespace + ((long)arr[5] << 16);
  freespace = freespace + ((long)arr[6] << 8);
  freespace = freespace + ((long)arr[7]);


  // Convert to String and float and divide by 100
  String counter = String(totalCounter);
  String addressString = String(address);
  String free = String(freespace);

  String meta = counter + "," + addressString + "," + free + ",";


  String sensorData;

  // Sensor Data (divided into 4 Bytes each as long (Format Big Endian))

  String results = "";

  for(long i = 8; i < MAXADDRESS; i+=4) {

    // Limit the Writing Size to SD-Card to save cycles optimum 512 Bytes
  if (results.length() >= 512) {

    // Read 4 Bytes
    char one = readData(i);
    char two = readData(i + 1);
    char three = readData(i + 2);
    char four = readData(i + 3);

    // Combine to long
    long value = ((unsigned long)(one << 24)) + ((unsigned long)(two << 16)) + ((unsigned long)(three << 8)) + (unsigned long)four;

    // Reverse the float saving multiplication
    float val = (float)value / 100;

    // Combine the results of each value until it gets 512 Values seperated with comma
    results = results + String(val) + ",";

    // Write to Sd Card
    writeFile("/Eeprom.csv", results.c_str());

    // Clear results to avoid writing the same values again
    results = "";
  }

  // Read 4 Bytes
  char one = readData(i);
  char two = readData(i + 1);
  char three = readData(i + 2);
  char four = readData(i + 3);

  // Combine to long
  long value = ((long)(one << 24)) + ((long)(two << 16)) + ((long)(three << 8)) + (long)four;

  // Reverse the float saving multiplication
  float val = (float)value / 100;

  // Combine the results of each value until it gets 512 Values seperated with comma
  results = results + String(val) + ",";
  }

  // Serial Print Success
  Serial.println("Writing Successful!");
}

void loop() {
}