# EEPROM Reader

This project demonstrates how to read data from an I2C EEPROM and write it to an SD card. It includes functions for initializing both the EEPROM and the SD card, reading from the EEPROM, and writing the data to a file on the SD card.

## Features

### `sdcard_init()`
Initializes the SD card module and checks for successful connection.

### `writeFile(path, message)`
Writes a message to a file on the SD card. If the file doesn't exist, it is created.

### `eeprom_init()`
Initializes the EEPROM and verifies the connection over I2C.

### `readData(address, buffer, size)`
Reads data from the EEPROM at a specified address and stores it in the provided buffer.

## Hardware Requirements

- ESP32      RAK11200
- EEPROM     RAK15000
- SD-Module  RAK15002

## Used Libraries

- [Adafruit EEPROM I2C](https://github.com/adafruit/Adafruit_EEPROM_I2C)
- [SD](https://www.arduino.cc/en/Reference/SD)
