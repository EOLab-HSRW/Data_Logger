#include <SPI.h>
#include <SD.h>

void sdcard_init() {
   if (!SD.begin()) { 
    Serial.println("failed!");
    return;
  }
  Serial.println("success! ");
}

// function for writing on the sd card
void writeFile(const char *path, const char *message) {
  Serial.printf("Schreibe Datei: %s\n", path);
  File file = SD.open(path, FILE_APPEND);
  if (file) {
    if (file.print(message)) {
      Serial.println("file written !");
    } else {
      Serial.println("writing failed !");
    }
    file.println();
    file.close();
  } else {
    Serial.println("opening file failed !");
  }
}