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
- 1x 16 Bit (Temprature)
- 1x 32 Bit (Pressure)
- 1x 16 Bit (Humidity)
- 1x 32 Bit (Gas)
- 1x 32 Bit (Water Pressure / Liquid Level)
- 1x 16 Bit (Voltage Level)

Total : 144 Bits

2^20 * 2 / 144 = 14563.5555556


### Result

There exists a difference between the two options of an amount of 5201 Iterations.