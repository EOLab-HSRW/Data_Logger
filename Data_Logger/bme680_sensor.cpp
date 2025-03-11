#include "bme680_sensor.h"

Adafruit_BME680 bme; // Definition von bme

bme

void bme680_init() {
  Wire.begin();
  if (!bme.begin(0x76)) {
    Serial.println("Could not find a valid BME680 sensor, check wiring!");
    return;
  }
  bme.setTemperatureOversampling(BME680_OS_8X);
  bme.setHumidityOversampling(BME680_OS_2X);
  bme.setPressureOversampling(BME680_OS_4X);
  bme.setIIRFilterSize(BME680_FILTER_SIZE_3);
  bme.setGasHeater(320, 150);
}

String bme680_get() {
  String result = String(bme.temperature) +"," +
                  String(bme.pressure) + " hPa\n" +
                  String(bme.humidity) + " %\n" +
                  String(bme.gas_resistance) + " KOhms\n";
  return result;
}