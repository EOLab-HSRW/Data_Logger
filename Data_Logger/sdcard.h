#ifndef SDCARD_H
#define SDCARD_H

#include <SPI.h>
#include <SD.h>
#include <Arduino.h> // Notwendig für Serial.println

void readFile(const char *path);
void writeFile(const char *path, const char *message);
void deleteFile(const char *path);

#endif