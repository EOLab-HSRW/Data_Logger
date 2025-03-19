# Eraser

This project provides a simple library for working with I2C EEPROMs using Arduino. 
The library includes functions to initialize the EEPROM, reset data, and configure the address.

## Features

### `eeprom_init()`
Initializes the EEPROM connection via I2C and checks if the EEPROM is present.

### `readData(address, buffer, size)`
Reads data from the EEPROM at a specified address and stores it in the provided buffer.

### `reset(size)`
Overwrites the first `size` bytes of the EEPROM with the value `0xFF`.

### `configAddress()`
Sets the default value for the EEPROM address counter to manage the memory correctly.

## Hardware Requirements

- ESP32  RAK11200
- EEPROM RAK15000

## Used Libraries

- [Adafruit EEPROM I2C](https://github.com/adafruit/Adafruit_EEPROM_I2C)
