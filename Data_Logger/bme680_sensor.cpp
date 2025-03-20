#include "bme680_sensor.h"

Adafruit_BME680 bme;

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

void get_Environment(long values[]) { 
  // Checking availability of the Sensor
  if (!bme.performReading()) {
    Serial.println("Failed to perform reading :(");
    return; 
  }

  // If available, read the Values and typecast it to long and multiply with 100,
  // for ensuring to keep the floating values
  values[0] = (long)(bme.temperature * 100);
  values[1] = (long)(bme.pressure * 100);
  values[2] = (long)(bme.humidity * 100);
  values[3] = (long)(bme.gas_resistance * 100);


}

