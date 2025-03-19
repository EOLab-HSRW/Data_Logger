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
| `get_Values()`       | datalogger.ino     | Retrieves sensor data and prints it via serial. |
| `bme680_init()`      | bme680_sensor.cpp  | Initializes the BME680 sensor. |
| `get_Environment()`  | bme680_sensor.cpp  | Reads sensor values and converts them to integers. |
| `eeprom_init()`      | eeprom.cpp         | Initializes and verifies EEPROM availability. |
| `readData()`         | eeprom.cpp         | Reads data from EEPROM. |
| `writeData()`        | eeprom.cpp         | Writes data to EEPROM and increments the address counter. |
| `readFile()`         | sdcard.cpp         | Reads a file from the SD card and prints its content. |
| `writeFile()`        | sdcard.cpp         | Appends data to an SD card file with CSV formatting. |
| `deleteFile()`       | sdcard.cpp         | Deletes a specified file from the SD card. |

## **5. Isolation of Counter and Storage Data**

### **64 Bit Meta Data**

```
0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000  0000 0000 0000 0000
------------------------                                                         Total (20)
                         ----------------------                                  Address (18)
                                               --------------------------------- Free (26)
```

---

### **Total Counter Calculation**
| Step | Description |
|------|------------|
| **1** | Take **Byte 1-3** |
| **2** | Convert and concatenate: `0000 0000 + 0000 0000 + 0000 0000` |
| **3** | Typecast to long: `0000 0000 0000 0000 0000 0000 = 0` |
| **4** | Increment by 1: `0000 0000 0000 0000 0000 0000 + 1 = 1` |
| **5** | Convert to string: `0000 0000 0000 0000 0000 0001` |
| **6** | Write to the first **20 Bits** |

---

### **Address Counter Calculation**
| Step | Description |
|------|------------|
| **1** | Take **Byte 3-5** |
| **2** | Convert and concatenate: `0000 0000 + 0000 0000 + 0000 0000` |
| **3** | Typecast to long: `0000 0000 0000 0000 0000 0000 = 0` |
| **4** | Increment by **sensor value amount (28)**: `0000 0000 0000 0000 0000 0000 + 28 = 28` *(7 Values × 4 (8 Bit to 32 Bit format))* |
| **5** | Convert to string: `0000 0000 0000 0000 0001 1100` |
| **6** | Write to **Bit 21 to 38** |

---

### ** Example of Byte Concatenation to Long**

```c
// Concatenate 4 Bytes to a Long
char a = 1;
char b = 1;
char c = 1;
char d = 1;

long aa = (long) a;
long bb = (long) b << 8;
long cc = (long) c << 16;
long dd = (long) d << 24;

printf("Byte 4: %d Byte 3 : %d Byte 2: %d Byte 1: %d ", dd, cc, bb, aa);
```

---

### **Example of Splitting a Long into 4 Bytes**

```c
// Split a long into 4 Bytes
long test = 5000000;

long mask1 = 4278190080; // 1111 1111 0000 0000 0000 0000 0000 0000
long mask2 = 16711680;  // 0000 0000 1111 1111 0000 0000 0000 0000
long mask3 = 65280;     // 0000 0000 0000 0000 1111 1111 0000 0000
long mask4 = 255;       // 0000 0000 0000 0000 0000 0000 1111 1111

long a = test & mask1;
long b = test & mask2;
long c = test & mask3;
long d = test & mask4;

char aa = a >> 24;
char bb = b >> 16;
char cc = c >> 8;
char dd = d;

printf("Long: %ld Byte1: %d Byte2: %d Byte3: %d Byte4: %d ", test, aa, bb, cc, dd);
```

## **6. Future Enhancements**
- **RTC Integration:** Implement timestamp retrieval for data logging.
- **Dynamic Sensor Expansion:** Add support for multiple sensors with flexible data structures.
- **Error Handling Improvements:** Implement retry mechanisms for failed sensor readings.

This documentation provides an overview of the system’s architecture and functionalities.

