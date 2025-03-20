# EEPROM Reader

This project demonstrates how to read data from an I2C EEPROM and write it to an SD card. The system is built with an ESP32, EEPROM module, and an SD card module. It features initialization functions for the EEPROM and SD card, as well as data retrieval functions to read from the EEPROM and write the data to a file on the SD card.

## Features

### `sdcard_init()`
Initializes the SD card module and checks for a successful connection. This function ensures that the SD card is properly mounted and ready for writing.

### `writeFile(path, message)`
Writes a message to a file on the SD card. If the file doesn't exist, it is created. This function is used to store the data read from the EEPROM to the SD card.

### `eeprom_init()`
Initializes the EEPROM module and verifies the connection over I2C. It ensures that the EEPROM is properly connected to the ESP32 and ready for data reading.

### `readData(address, buffer, size)`
Reads data from the EEPROM at a specified address and stores it in the provided buffer. This function is used to retrieve both metadata and sensor data from the EEPROM.

### `getMetaData()`
This function reads the first 8 bytes of the EEPROM (the metadata) and processes the information. It calculates the total counter, address, and available free space based on the EEPROM contents.

### `getSensorData(counterAddress, i)`
This function reads sensor data from the EEPROM at a specific address and converts the data into a float value. The values are divided by 100 to convert them into a human-readable format (unless the value represents a timestamp). This function is used to process sensor readings for logging.

## Hardware Requirements

- ESP32 RAK11200
- EEPROM RAK15000
- SD-Module RAK15002

## Used Libraries

- [Adafruit EEPROM I2C](https://github.com/adafruit/Adafruit_EEPROM_I2C)
- [SD](https://www.arduino.cc/en/Reference/SD)

## Code Walkthrough

### Setup Process

1. **Serial Initialization:**
   The code starts by initializing the Serial communication at a baud rate of 115200. This allows you to monitor the progress of the program in the Serial Monitor.

2. **Initializing EEPROM and SD Card:**
   The functions `eeprom_init()` and `sdcard_init()` are called to initialize both the EEPROM and the SD card. These functions ensure that both components are correctly connected and operational.

3. **Reading Meta Data:**
   The `getMetaData()` function is called to read the first 8 bytes of data from the EEPROM. This metadata provides useful information about the EEPROM's state, such as the total counter, address, and available space. This data is then written to a file on the SD card as `Eeprom.csv`.

4. **Reading Sensor Data:**
   The program then reads sensor data from the EEPROM. A loop is used to read the data in chunks (50 sensor readings in this example). It reads 4 bytes at a time (each value is 4 bytes), and the data is processed by the `getSensorData()` function, which converts the raw bytes into float values. These values are then written to the SD card.

5. **Writing to SD Card:**
   The `writeFile()` function is used to write the meta data and sensor data to the SD card. The sensor data is written in CSV format, where each sensor reading is followed by a comma, and new lines are added after every 8 sensor readings.

### Main Functions

#### `getMetaData()`
The `getMetaData()` function reads 8 bytes from the EEPROM (the metadata section). It extracts and calculates important values such as:

- **Total Counter:** The total number of data points in the EEPROM.
- **Address:** The starting address for the sensor data.
- **Free Space:** The available space left in the EEPROM.

This metadata is formatted into a CSV string and returned.

#### `getSensorData(counterAddress, i)`
This function reads sensor data from the EEPROM at the specified address. It extracts 4 bytes of data and combines them into a single long value. This value is then divided by 100 to convert it into a floating-point value (except for timestamps, which are left as raw values). The processed data is returned as a string, and if it is the last value in a set, a newline character is added.

### Code Structure

The code is organized into different files:

- **`calculator.h`**: Contains declarations for the `getMetaData()` and `getSensorData()` functions.
- **`eeprom.h`**: Contains the functions related to reading data from the EEPROM.
- **`sdcard.h`**: Contains the functions related to initializing and writing data to the SD card.

Each of these files is included in the main Arduino file for initialization and processing of data.
