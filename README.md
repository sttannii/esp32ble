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

Example configuration:

```cpp
esp_ble_adv_params_t adv_params = {
    .adv_int_min = 0x00A0,
    .adv_int_max = 0x00A0,
    .adv_type = ADV_TYPE_IND,
    .own_addr_type = BLE_ADDR_TYPE_PUBLIC,
    .channel_map = ADV_CHNL_ALL,
    .adv_filter_policy = ADV_FILTER_ALLOW_SCAN_ANY_CON_ANY
};
