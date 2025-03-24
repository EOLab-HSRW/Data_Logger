#ifndef BME680_SENSOR_H
#define BME680_SENSOR_H

#define SEALEVELPRESSURE_HPA (1010.0)

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME680.h>
#include <Arduino.h> // required Serial

extern Adafruit_BME680 bme;
bool bme680_init();
void get_Environment(long values[]); 

#endif