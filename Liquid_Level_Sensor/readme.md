# Data Logger Modification

## RS485 Liquid Level Sensor (S-YW-01B)

### Overview
The **RS485 Liquid Level Sensor (S-YW-01B)** is a high-precision sensor designed for measuring liquid levels. It communicates using the **Modbus-RTU protocol** and is suitable for various applications, including:

- Reservoir and deep well monitoring  
- Wastewater treatment  
- River and marine monitoring  
- Tank level measurement  

### Features
**Anti-corrosion material** – Durable and resistant  
**Modbus-RTU communication** – Compatible with PLCs, displays, and data loggers  
**High-precision sensor** – ±0.25% accuracy  
**Wide operating voltage** – 11–30V DC  
**Fast response time** – ≤ 5 ms  

## Technical Specifications

| Parameter                   | Value                          |
|-----------------------------|--------------------------------|
| **Measurement Range**       | 0 ~ 5 meters                   |
| **Output**                  | RS485 (Modbus-RTU)             |
| **Accuracy**                | ±0.25% F.S.                    |
| **Temperature Range**       | -40°C to +85°C                 |
| **Material**                | 304/316L Stainless Steel       |
| **Power Supply**            | 11–30V DC                      |
| **Weight**                  | 670 g                          |

## Wiring
The sensor is connected via an **Aviation Connector** interface. The pin configuration is:

| Pin | Description        |
|-----|-------------------|
| 1   | 12V Power Supply  |
| 2   | 5V Power Supply   |
| 3   | RS485 A (-)       |
| 4   | RS485 B (+)       |
| 5   | GND (Ground)      |

## Modbus-RTU Communication
### Default Communication Settings:
- **Baud Rate**: 9600 bps (supports 1200–115200 bps)
  **Note:** Changes to baud rate and slave address take effect immediately. If not, restart the sensor.


- **Data Bits**: 8
- **Parity**: None
- **Stop Bits**: 1
- **Default Slave Address**: `0x1A`

### Example Command (Read Slave Address)
| Address | Function | Start Address | Number of Registers | CRC16 (L) | CRC16 (H) |
|---------|---------|---------------|---------------------|-----------|-----------|
| `0x1A`  | `0x03`  | `0x0000`      | `0x0001`           | `0x87`    | `0xE1`    |

### Response Format
| Address | Function | Data Length | Value (H) | Value (L) | CRC16 (L) | CRC16 (H) |
|---------|---------|-------------|-----------|-----------|-----------|-----------|
| `0x1A`  | `0x03`  | `0x02`      | `0x00`    | `0x01`    | `0x1D`    | `0x86`    |


## RAK5801 Sensor Module

### Overview
The **RAK5801** is a high-performance sensor module designed for industrial and environmental monitoring applications. 
Part of the WisBlock ecosystem, it offers robust data acquisition and is engineered for reliable performance even in harsh conditions.

### Features
- **High-Precision Measurement** – accurate data collection.
- **Rugged Design** –  reliably in industrial environments.
- **Seamless Integration** – Easily integrates.
- **Versatile Interfaces** – Supports standard communication protocols.

## RAK19002 Sensor Module

### Overview
The **RAK19002** is a sensor module developed for versatile IoT applications within the WisBlock ecosystem.
It is designed to provide reliable, accurate measurements for various environmental and application-specific parameters.

### Features
- **Compact & Low Power** – Optimized for energy-efficiency.
- **High Accuracy** – Ensures precise measurement data.
- **Plug-and-Play Integration** – interfaces with WisBlock.
- **Robust Performance** – Suitable for operating conditions.

