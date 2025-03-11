#ifndef BME680_SENSOR_H
#define BME680_SENSOR_H

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME680.h>
#include <Arduino.h> // Notwendig für Serial.println

extern Adafruit_BME680 bme; // Deklaration von bme
void bme680_init();
String bme680_get();


#endif