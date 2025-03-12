# **Software Documentation: Arduino Data Logger**

## **1. Overview**
This project implements a data logging system using an Arduino-compatible microcontroller. The system reads environmental sensor data, stores it in EEPROM, and writes it to an SD card. Additionally, it integrates a Real-Time Clock (RTC) for timestamping logged values.

## **2. File Structure**
The project consists of several modules:

### **2.1 datalogger.ino**
- **Purpose:** Main entry point of the application.
- **Functionality:**
  - Initializes required components (SD card, EEPROM, BME680 sensor, and RTC).
  - Collects environmental sensor data.
  - Manages data storage in EEPROM and SD card.
  - Ensures proper communication and handling of time-sensitive operations.

### **2.2 bme680_sensor.h / bme680_sensor.cpp**
- **Purpose:** Interface for the BME680 environmental sensor.
- **Functionality:**
  - Initializes the BME680 sensor and configures its settings.
  - Reads temperature, pressure, humidity, and gas resistance values.
  - Ensures data consistency by converting floating values to integers (x100 scaling).
  - Provides both static and dynamic memory allocation options for sensor data retrieval.

### **2.3 eeprom.h / eeprom.cpp**
- **Purpose:** EEPROM memory management.
- **Functionality:**
  - Initializes EEPROM communication over I2C.
  - Provides functions for reading and writing data to EEPROM.
  - Implements memory addressing logic to ensure sequential data storage.
  - Includes power control for EEPROM.

### **2.4 sdcard.h / sdcard.cpp**
- **Purpose:** SD card file management.
- **Functionality:**
  - Provides functions to read, write, and delete files on an SD card.
  - Uses SPI communication for SD card access.
  - Supports CSV-style data logging with automatic separation.
  - Implements error handling for file operations.

## **3. System Workflow**
1. **Initialization:**
   - The system starts by initializing serial communication, EEPROM, SD card, RTC, and the BME680 sensor.
   - It checks the presence and accessibility of each module.

2. **Data Collection:**
   - The main loop collects sensor readings every 5 minutes using `get_Environment()`.
   - The retrieved data is formatted and prepared for storage.

3. **Data Storage:**
   - Data is split into 8-bit chunks and stored in EEPROM sequentially.
   - The same data is written to the SD card for long-term storage.

4. **Error Handling:**
   - The system checks for sensor availability and EEPROM communication before reading or writing data.
   - Serial messages indicate any failures, such as missing EEPROM or SD card issues.

## **4. Functions Summary**
| Function Name         | File               | Description |
|----------------------|-------------------|-------------|
| `get_Values()`       | datalogger.ino     | Retrieves sensor data and prints it via serial. |
| `bme680_init()`      | bme680_sensor.cpp  | Initializes the BME680 sensor. |
| `get_Environment()`  | bme680_sensor.cpp  | Reads sensor values and converts them to integers. |
| `eeprom_init()`      | eeprom.cpp         | Initializes and verifies EEPROM availability. |
| `readData()`         | eeprom.cpp         | Reads data from EEPROM. |
| `writeData()`        | eeprom.cpp         | Writes data to EEPROM and increments the address counter. |
| `readFile()`         | sdcard.cpp         | Reads a file from the SD card and prints its content. |
| `writeFile()`        | sdcard.cpp         | Appends data to an SD card file with CSV formatting. |
| `deleteFile()`       | sdcard.cpp         | Deletes a specified file from the SD card. |

## **5. Future Enhancements**
- **RTC Integration:** Implement timestamp retrieval for data logging.
- **Dynamic Sensor Expansion:** Add support for multiple sensors with flexible data structures.
- **Error Handling Improvements:** Implement retry mechanisms for failed sensor readings.

This documentation provides an overview of the system’s architecture and functionalities.
