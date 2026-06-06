# Embedded Energy Management System Using NodeMCU

## Overview

This project implements an IoT-based Smart Energy Meter using the NodeMCU (ESP8266) microcontroller and ACS712 Current Sensor. The system continuously monitors electrical current consumption, processes sensor data, and transmits readings wirelessly through Wi-Fi for remote monitoring and analysis.

The project demonstrates embedded firmware development, sensor interfacing, real-time data acquisition, signal processing, and IoT communication.

---

## Features

* Real-time current monitoring using ACS712 Current Sensor
* Wireless data transmission via ESP8266 Wi-Fi module
* Continuous sensor data acquisition and processing
* Remote monitoring of energy consumption
* Embedded firmware for sensor interfacing and communication
* Low-cost and scalable IoT solution

---

## Hardware Components

| Component             | Description                   |
| --------------------- | ----------------------------- |
| NodeMCU ESP8266       | Wi-Fi enabled microcontroller |
| ACS712 Current Sensor | Current measurement sensor    |
| Breadboard            | Prototyping platform          |
| Jumper Wires          | Hardware connections          |
| Power Supply          | System power source           |

---

## System Architecture

Load → ACS712 Current Sensor → NodeMCU ESP8266 → Wi-Fi Network → Remote Monitoring Dashboard

---

## Working Principle

1. The ACS712 sensor measures the current drawn by the connected load.
2. The NodeMCU reads analog sensor values through its ADC.
3. Sensor data is processed and converted into current measurements.
4. The ESP8266 transmits the readings via Wi-Fi.
5. Users can monitor energy consumption remotely.

---

## Technologies Used

* Embedded C/C++
* Arduino IDE
* ESP8266 Platform
* IoT Systems
* Wi-Fi Communication
* Sensor Interfacing

---

## Repository Structure

```text
.
├── README.md
├── LICENSE
├── .gitignore
├── hardware/
├── firmware/
├── images/
├── docs/
└── data/
```

---

## Future Enhancements

* Voltage sensing integration
* Power and energy calculation (Watt, kWh)
* MQTT-based communication
* Cloud dashboard integration
* Mobile application support

---

## Author

Sahana

Embedded Systems Engineer | IoT Enthusiast
