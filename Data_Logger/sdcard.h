#ifndef SDCARD_H
#define SDCARD_H

#include <SPI.h>
#include <SD.h>
#include <Arduino.h> // required for Serial

void sdcard_init();
void readFile(const char *path);
void writeFile(const char *path, const char *message);
void deleteFile(const char *path);
String combineToString(long *data, size_t size);

#endif