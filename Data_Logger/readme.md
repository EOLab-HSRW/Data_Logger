# **Software Documentation: Arduino Data Logger**

## Content

- [Overview](#1-overview)
- [File Structure](#2-file-structure)
- [System Workflow](#3-system-workflow)
- [Function Summary](#4-functions-summary)
- [Data Isolation / Storage](#5-isolation-of-counter-and-storage-data)
- [Future Enhancements](#6-future-enhancements)

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
| `void get_Values()`       | datalogger.ino     | Retrieves sensor data and prints it via serial. |
| `bool bme680_init()`      | bme680_sensor.cpp  | Initializes the BME680 sensor. |
| `void get_Environment()`  | bme680_sensor.cpp  | Reads sensor values and converts them to integers. |
| `bool eeprom_init()`      | eeprom.cpp         | Initializes and verifies EEPROM availability. |
| `void readData()`         | eeprom.cpp         | Reads data from EEPROM. |
| `void writeData()`        | eeprom.cpp         | Writes data to EEPROM and increments the address counter. |
| `long getCounter()`         | eeprom.cpp         | Returns the extracted Total Counter. |
| `void setCounter()`         | eeprom.cpp         | Sets the Total Counter.|
| `void getAddress()`         | eeprom.cpp         | Returns the extracted Address Counter. |
| `void setAddress()`         | eeprom.cpp         | Sets the Address Counter.|
| `void readFile()`         | sdcard.cpp         | Reads a file from the SD card and prints its content. |
| `void writeFile()`        | sdcard.cpp         | Appends data to an SD card file with CSV formatting. |
| `void deleteFile()`       | sdcard.cpp         | Deletes a specified file from the SD card. |
| `void rtc_init()`         | rtc.cpp            | Initializes and verifies RTC availability. |
| `unsigned long rtcGetTimeLong()`| rtc.cpp      |  Returns the current time.|

## **5. Isolation of Counter and Storage Data**

### **64 Bit Meta Data**

```
0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000  0000 0000 0000 0000
------------------------                                                         Total (20)
                         ----------------------                                  Address (18)
                                               --------------------------------- Free (26)
```

---

### **Total Counter Isolation**
| Step | Description |
|------|------------|
| **1** | Read **Byte 1-3** (Indexes 0-2) |
| **2** | Perform a Bit Shift by 4 to the right on the third byte |
| **3** | Perform a Bit Shift by 4 to the left to restore the original value |
| **4** | Convert to `long` to obtain the exact value from the bytes |
| **5** | Shift the first byte 16 bits to the left |
| **6** | Shift the second byte 8 bits to the left |
| **7** | Sum all values to get the final total |

### **Total Counter Reset**
| Step | Description |
|------|------------|
| **1** | Generate 3 masks to extract the 20 bits from the long parameter |
| **2** | Masks: `0xff0000`, `0x00ff00`, and `0x0000ff` |
| **3** | Set byte 1 and byte 2 with the extracted values |
| **4** | Read byte 3 again, perform a bit shift by 4 to the left and right to align with subsequent metadata |
| **5** | Perform an OR operation with the adjusted `val3` and set the third byte |

---

### **Address Counter Isolation**
| Step | Description |
|------|------------|
| **1** | Read **Byte 3-5** (Indexes 2-4) |
| **2** | Perform a Bit Shift by 4 to the right on the second byte |
| **3** | Perform a Bit Shift by 4 to the left to restore the original value |
| **4** | Convert to `long` to obtain the exact value from the bytes |
| **5** | Shift the first byte 16 bits to the left |
| **6** | Shift the third byte 8 bits to the left |
| **7** | Sum all values to get the final address |

### **Address Counter Reset**
| Step | Description |
|------|------------|
| **1** | Generate 3 masks to extract the 20 bits from the long parameter |
| **2** | Masks: `0xff0000`, `0x00ff00`, and `0x0000ff` |
| **3** | Set byte 2 with the extracted value |
| **4** | Read byte 1 and byte 3 again, perform a bit shift by 6 to the left and right for byte 3, and by 4 to the left and right for byte 1 to align with subsequent metadata |
| **5** | Perform an OR operation with `val1` and `val3` from behind and set the first and third bytes |

---

