# Data_Logger

## Description

This Project aims to ease the Process of logging Data on an external Storage (SD-Card / EEPROM).

## Used Hardware

- RawWireless Wisblock:
    - RAK11200 (ESP32 based inkl. WiFi,BLE)
    - RAK11310 (Raspberry Pi based inkl. Lora Transceiver)
    - RAK19002 (Power Slot Module e.g (Li-Ionen, USB-C, Solar))
    - RAK15000 (EEPROM Module)
    - RAK15002 (SD-Card Module)
    - RAK19011
    - RAK19012
    - RAK5802
    - RAK1906  (Environment Sensor Module)
    - RS485    (Liquid Level Sensor + Connector)

For Data Sheets, Quick Guides and Description : docs.RawWireless.com

## Used Software

The Arduino IDE was used.
Files included in the Projectfolder.

## Data Types

- Timestamp

- Environment Sensor:
        - Temprature
        - Pressure
        - Humidity
        - Gas

- Liquid Level Sensor:
        - Liquid Level
        - Water Pressure


## Datastoring Simulation for EEPROM

Propertys:
- 1 Million Writing Cycles (until it gets unreliable)
- 2Mb (2^20 (2.097.152)) Bits orginized as 262.144 Words (in 8 Bit Format).
- Standby Current (3 micro Ampere)
- 256 Bytes Page Write Mode (in one step (for reducing to much cycles for efficiency))
- 3.3V Input (Can be controlled from the Core (On/Off))

Restriction : 

- 2MB
- at least 2-3 Month endurance

Assuming that 7 Values has to be stored at each iteration, the folllowing result occurs:

2^20 * 2 = 2.097.152 Bits

2 Options are available:

1) No Efficiency:

- 1x 32 Bit (Unix Timestamp)
- 1x 32 Bit (Temprature)
- 1x 32 Bit (Pressure)
- 1x 32 Bit (Humidity)
- 1x 32 Bit (Gas)
- 1x 32 Bit (Water Pressure / Liquid Level)
- 1x 32 Bit (Voltage Level)

Total : 224 Bits

2^20 * 2 / 224 = 9362.28571429


2) With Efficiency

- 1x 32 Bit (Unix Timestamp)
- 1x 16 Bit (Temprature -40°C - 100°C)
- 1x 32 Bit (Pressure)
- 1x 16 Bit (Humidity 0%-100%)
- 1x 32 Bit (Gas)
- 1x 32 Bit (Water Pressure / Liquid Level 0-5000)
- 1x 16 Bit (Voltage Level 0-24)

Total : 144 Bits

2^20 * 2 / 144 = 14563.5555556


### Result

There exists a difference between the two options of an amount of 5201 Iterations.

### EEPROM RAK15000 

This module orginizes the Storage as 4x 64Kb Blocks .
To choose between these Blocks the I2C Communication is used.
The Storage is linear sequential but with a structered format of 8 Bits -> 1 Byte at each Address.
The Address Schema is as follows:

3 Bit Address (For I2C) : 

        1) 000 -> Block 0 (0x00000 - 0x0FFFF)
        2) 001 -> Block 1 (0x10000 - 0x1FFFF)
        3) 010 -> Block 2 (0x20000 - 0x2FFFF)
        4) 011 -> Block 3 (0x30000 - 0x3FFFF)

### EEPROM RAK11200 (internal)

This Module has an internal EEPROM which has a size of 64Kb (524.288 Bits).
So it doesn't need a Block Switch Control.
It is also linear sequential but has no special format structure like the RAK15000.
It is possible that it has already configuration data on it at the purchase to ease the Connection Process for LoRaWan.

The Addres Schema:
        
        1) 0x0000 - 0xFFFF 


### Data Storage Management

For this Project we will use the first 5 Bytes to save two Counters to keep track of the Process Status.

Included are these two Data: 

        1) Writing Counter for Total Writing Amount (20 Bit) 
        2) Storage Position Counter for keep tracking the next Writable Address (20 Bit)


The Writing Counter has to be stored globally once and seperatly because the possible cycle of writing is exactly 1 Million Times until it gets unreliable.
Storing this amount requires at least 20 Bits for the Value 1 Million (0xF4240).
So the Starting first 20 Bits are reserved for the Total Amount Counter.


Storage Position Counter needs to be also 16 Bits.
Because of 65536 possible entrys, we can determine the needed amount of Bits to at least 16 Bit for the Writing Counter for each Block. 
Thats the maximum amount of entrys we can get into our EEPROM if we divide the Meta Data in the several Blocks.


### EEPROM Data Reader

A Seperate Sketch can be found in the Projectfolder.


### EEPROM Decoder

After every Switch of Context or Sensor Change, the Data has to be decoded.
A Seperate Sketch will be included in the Projectfolder soon.



### Erasing Data before switching Context / Sensors

After every Switch of Context or Sensor Change, the Data has to ereased to avoid Data conflicts.
A Seperate Sketch will be included in the Projectfolder soon.

