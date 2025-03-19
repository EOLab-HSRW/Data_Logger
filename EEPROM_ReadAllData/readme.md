# EEPROM Data Reader

This project provides a simple library for using I2C EEPROMs with Arduino. 
The library allows initializing the EEPROM, resetting data, and configuring addresses.

## Functions

### `eeprom_init()`
Initializes the connection to the EEPROM via I2C and checks the connection.

### `readData(address, buffer, size)`
Reads data from the EEPROM at a specified address and stores it in a buffer.

### `reset(size)`
Overwrites the first `size` bytes of the EEPROM with the value `0xFF`.

### `configAddress()`
Configures the EEPROM address to ensure correct memory management.

## Hardware Requirements

- ESP32  RAK11200
- EEPROM RAK15000 

## Used Libraries

- [Adafruit EEPROM I2C](https://github.com/adafruit/Adafruit_EEPROM_I2C)
