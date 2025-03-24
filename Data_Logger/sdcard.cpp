#include <Arduino.h>
#include "sdcard.h"



bool sdcard_init() {
  if (!SD.begin()) {
    Serial.println("Card Mount Failed! Please make sure the card is inserted!");
    return false;
  }
  return true;
}

String combineToString(long* data, size_t size) {
  String result = "";
  for (size_t i = 0; i < size; i++) {

    	// Checking for every 5.th Value (Timestamp)
    if(i != 0 && (i+1) % 5 == 0){
      result += String(data[i])+",";
    }
    else{
      float division = (float)data[i]/100;
      result += String(division)+",";
    }

  }
  result += "\n";  // new line
  return result;
}


void readFile(const char *path) {
  Serial.printf("Reading file: %s\n", path);
  File file = SD.open(path, FILE_READ);
  if (file) {
    Serial.println("Read from file: ");
    while (file.available()) {
      Serial.write(file.read());
    }
    file.close();
  } else {
    Serial.println("Failed to open file for reading.");
    return;
  }
}

void writeFile(const char *path, const char *message) {
  Serial.printf("Writing file: %s\n", path);
  File file = SD.open(path, FILE_APPEND);
  if (file) {

    if (file.print(message)) {
      Serial.println("File written.");
    } else {
      Serial.println("Write failed.");
    }
    file.close();
  } else {
    Serial.println("Failed to open file for writing.");
    return;
  }
}

void deleteFile(const char *path) {
  Serial.printf("Deleting file: %s\n", path);
  if (SD.remove(path)) {
    Serial.println("File deleted.");
  } else {
    Serial.println("Delete failed.");
  }
}