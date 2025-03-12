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

The Arduino IDE is used.
Files are included in the Projectfolder.

## Data Types
    1) Timestamp
    2) Environment Sensor:
    * Temprature
    * Pressure
    * Humidity
    * Gas

    3) Liquid Level Sensor:
    * Liquid Level
    * Water Pressure


## Datastoring Simulation for EEPROM

### Property's:
- 1 Million Writing Cycles (until it gets unreliable)
- 2Mb (2^20 (2.097.152)) Bits orginized as 262.144 Words (in 8 Bit Format).
- Standby Current (3 micro Ampere)
- 256 Bytes Page Write Mode (in one step (for reducing rapid wear))
- 3.3V Input (Can be controlled from the Core (On/Off))

### Restriction's: 
- 2MB
- at least 2-3 Month endurance

### Calculation :
Assuming that 7 Values has to be stored at each iteration, the folllowing result occurs:

2^20 * 2 = 2.097.152 Bits

Two Options are available:

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

This Module has a size of 2Mb (2 * 2^20) = 2.097.152 Bits.
The Storage is linear sequential.
The Addresses contain 1 Byte at each Address.
In total 262.144 Addresses are available.

### EEPROM RAK11200 (internal)

This Module has an internal EEPROM which has a size of 64Kb (524.288 Bits).
It is also linear sequential.
It is possible that it has already configuration data on it at the purchase to ease the Connection Process for LoRaWan.
The Addresses are 16 Bit from 0x0000 to 0xFFFF.

### Data Storage Management

We will use the first 8 Bytes (64 Bits) as Meta Data to keep track of the Process Status.

Included are these Data as follows: 

        1) Writing Counter for Total Writing Amount (20 Bit) 
        2) Storage Position Counter for keep tracking the next Writable Address (18 Bit)

        --------------
        Total: 38 Bit
        Rest:  26 Bit (Free for more Data if needed in the future) 


The Writing Counter needs to be capeable of storing the maximum possible Writing Cycle (1 Million).
Storing this amount requires at least 20 Bits. (1 Million = 0xF4240).
So the Starting first 20 Bits are reserved for the Total Amount Counter.

The Storage Position Counter needs to be at least 18 Bits, because the maximum Address is 262.144.

So in total the least needed amount is 38 Bits.
But it is a better Idea and a more efficient way to increase the size of the Meta Data from 4 to 8 Bytes to avoid Problems that maybe can occure in the future like if more counters for different purposes are needed.

### EEPROM Data Reader

A Seperate Sketch can be found in the Projectfolder.


### EEPROM Decoder

After every Switch of Context or Sensor Change, the Data has to be decoded.
A Seperate Sketch will be included in the Projectfolder soon.



### Erasing Data before switching Context / Sensors

After every Switch of Context or Sensor Change, the Data has to ereased to avoid Data conflicts.
A Seperate Sketch will be included in the Projectfolder soon.

