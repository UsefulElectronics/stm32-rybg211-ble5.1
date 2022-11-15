[![Build Status](https://img.shields.io/badge/USEFUL%20ELECTRONICS-YOUTUBE-red)](https://www.youtube.com/user/wardzx1)

# Sponsors

### PCBWay
Tutorial Series Sponsor PCBWay Website. You can get extra free coupons using the link below:
[<img src="https://github.com/UsefulElectronics/esp32s3_la66_lorawan/blob/main/repo%20cover/banner320x100.gif">](https://www.pcbway.com/setinvite.aspx?inviteid=582640)

***
### REYAX
RYBG211 2.4GHz Bluetooth 5.1 High power long range module:
https://www.reyax.com/products/RYBG211_lite
***

# STM32 USB CDC RYBG211 BLE PC to Smartphone Messaging Application
***
### [Tutorial Link](https://youtu.be/dV8yROPrPJw) On [![Build Status](https://img.shields.io/badge/YouTube-FF0000?style=for-the-badge&logo=youtube&logoColor=white)](https://www.youtube.com/wardzx1) 
In this tutorial, RYBG211 Bluetooth Low Energy Module is interfaced by STM32F411 MCU using AT commands over UART and it is configured to have USB CDC interface. 

with such setup, smartphone to personal computer messaging firmware is build making it possible to send data from a smartphone over BLE GATT connection to RYBG211 module that sends the data to the MCU over UART. STM32F411 later on sends the received data over USB virtual COM port to the connected PC. a reversed communication rout is taken when the data source is the PC.

The advantage of such implementation is that PC does not worry about the connected MCU communication baud rate. The whole system is powered over the connected USB. 

![Circuit Diagram](https://github.com/UsefulElectronics/stm32-rybg211-ble5.1/blob/main/repo%20cover/circuit%20diagram.png)

