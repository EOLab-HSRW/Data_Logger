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


## Data Encryption for EEPROM