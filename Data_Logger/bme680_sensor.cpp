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

// Get Values and Multiply with 100 to ensure the floating values
int[] get_Environment(){
  int[] values = {(int)bme.temperature*100,(int)bme.pressure*100,(int)bme.humidity*100,(int)bme.gas_resistance*100};
}