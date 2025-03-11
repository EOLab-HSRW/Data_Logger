#include "sdcard.h"

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
    file.print(millis()); // Zeitstempel hinzufügen
    file.print(", "); // Trennzeichen hinzufügen
    if (file.print(message)) {
      Serial.println("File written.");
    } else {
      Serial.println("Write failed.");
    }
    file.println();
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