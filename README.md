# Research of Bluetooth Low Energy Networks on ESP32

## About the project

This repository contains the software part of a bachelor's thesis devoted to the study of wireless networks based on Bluetooth Low Energy (BLE).

The project focuses on the primary access stage of BLE networks, including advertising, device discovery, the influence of the number of advertising channels, the number of peripheral devices, and external Wi-Fi load in the 2.4 GHz frequency range.

The practical part of the work includes experiments with an ESP32-based BLE peripheral and a simulation model for studying the primary access of multiple BLE devices to a central device.

## Research objectives

The main objectives of the project were:

- to study the architecture and operating modes of Bluetooth Low Energy;
- to investigate the primary access procedure and BLE advertising;
- to study the influence of advertising channels on device discovery;
- to evaluate the influence of Wi-Fi load on BLE communication;
- to develop an experimental BLE network based on ESP32;
- to measure RSSI and device discovery delay;
- to develop a simulation model of BLE primary access;
- to investigate the influence of the number of peripheral devices and advertising channels on discovery delay and probability of successful detection.

## Hardware

The experimental setup was based on:

- ESP32-WROOM-32D;
- two smartphones;
- LightBlue application;
- laptop for firmware development and uploading;
- Wi-Fi router for creating external load in the 2.4 GHz band.

The ESP32 was used as a BLE peripheral device. Smartphones were used as central devices for scanning, discovering and connecting to the ESP32.

## Technologies

### Embedded / BLE

- ESP32
- ESP-IDF
- Bluetooth Low Energy
- BLE Legacy Advertising
- GATT
- GAP
- RSSI
- Advertising channels 37, 38 and 39

### Simulation

- Python
- Random / Monte Carlo simulation
- Pandas
- Matplotlib

## ESP32 BLE implementation

The ESP32 operates as a BLE peripheral and periodically transmits advertising packets.

The advertising parameters used in the experiment include:

- advertising type: `ADV_IND`;
- advertising interval: 100 ms;
- advertising channels: 37, 38 and 39;
- configurable advertising channel map.


The advertising channel configuration can be changed to use one, two or three primary advertising channels.

Experimental scenarios
Experiment 1 — RSSI measurement

The first experiment investigated the influence of the set of primary advertising channels and Wi-Fi load on the received signal strength.

The following configurations were tested:

channels 37, 38 and 39;
channel 37;
channel 38;
channel 39;
channels 37 and 38;
channels 37 and 39;
channels 38 and 39.

Each configuration was tested both with and without additional Wi-Fi load.

The distance between the ESP32 and smartphone was approximately 1 meter.

The results showed that Wi-Fi load worsened the average RSSI in all tested configurations. Using several advertising channels provided more stable results than using a single channel.

Experiment 2 — Device rediscovery delay

The second experiment investigated the delay of repeated discovery of an ESP32 device.

Two smartphones were used:

Smartphone 1 established a connection with the ESP32;
Smartphone 2 remained in scanning mode.

After the connection with Smartphone 1 was terminated, the time required for the ESP32 to become visible again on Smartphone 2 was measured.

The measured rediscovery delay was approximately 1 second.

BLE primary access simulation

Because it is difficult to physically reproduce a BLE network containing tens or hundreds of peripheral devices, a simulation model was developed.

The model represents a central BLE device and a group of peripheral devices periodically transmitting advertising events.

A collision occurs when advertising events from different devices overlap in time and use the same advertising channel.

The model evaluates:

average primary access delay;
number of successfully discovered devices;
probability of successful discovery.
Simulation parameters

The main simulation parameters are:

Parameter	Value
Advertising interval	100 ms
Advertising delay	0–10 ms
Observation time	1 s
Number of trials	300
Number of peripheral devices	1–300
Advertising channels	1–3
Maximum packet duration	376 μs
Estimated busy time	1428 μs
Simulation algorithm

The simulation performs the following steps:

Set the number of peripheral devices.
Set the number of available advertising channels.
Generate initial random advertising times.
Generate subsequent advertising events using the advertising interval and random delay.
Assign an advertising channel to each event.
Detect collisions between advertising events.
Determine successfully discovered devices.
Calculate the primary access delay.
Calculate the probability of successful discovery.
Repeat the experiment using the Monte Carlo method.
Calculate average results.
Results

The simulation demonstrated that increasing the number of simultaneously operating BLE peripheral devices increases the probability of advertising packet collisions.

Using multiple advertising channels significantly improves the stability of primary access.

For example, with 300 peripheral devices:

using 1 advertising channel resulted in a successful discovery probability of approximately 0.5%;
using 2 advertising channels resulted in approximately 23.4%;
using 3 advertising channels resulted in approximately 85.2%.

The average primary access delay for 300 devices was:

Advertising channels	Average delay
1	997.2 ms
2	896.7 ms
3	594.9 ms

These results demonstrate the importance of using multiple primary advertising channels when a large number of BLE peripheral devices operate within the same area.

Project structure
esp32-ble-primary-access/
│
├── esp32/
│   └── BLE firmware
│
├── simulation/
│   └── BLE primary access simulation
│
├── results/
│   └── simulation results and plots
│
└── README.md

The repository structure may be adjusted depending on the source files included in the project.

Conclusions

The project demonstrates the practical implementation and investigation of BLE primary access using an ESP32-based experimental setup and a Python simulation model.

The experiments and simulation show that BLE primary access depends on:

the number of peripheral devices;
the number of primary advertising channels;
advertising timing parameters;
external load in the 2.4 GHz frequency range.

The use of all three primary advertising channels — 37, 38 and 39 — provides better stability of primary device discovery, especially when a large number of peripheral devices operate within the same area.

Future work

Possible directions for further research include:

experiments with a larger number of real BLE devices;
analysis of the 2.4 GHz spectrum using a spectrum analyzer;
more detailed investigation of BLE connection mode;
investigation of data exchange after establishing a connection;
comparison of simulation results with measurements obtained from larger experimental setups.

Author
Татьяна Спиридонова
