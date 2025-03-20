
![CSE_ArduinoRS485](https://socialify.git.ci/CIRCUITSTATE/CSE_ArduinoRS485/image?description=1&font=KoHo&forks=1&issues=1&logo=https%3A%2F%2Fwww.circuitstate.com%2Fwp-content%2Fuploads%2F2024%2F05%2FCIRCUITSTATE-R-Emblem-20052024-2.svg&name=1&pattern=Circuit%20Board&pulls=1&stargazers=1&theme=Auto)

# CSE_ArduinoRS485

**CSE_ArduinoRS485** is an Arduino library from [*CIRCUITSTATE Electronics*](https://www.circuitstate.com/). This Arduino library allows you to send and receive data using the **RS-485** interface standard. Supported by all Arduino-compatible boards such as ESP32, STM32, RP2040, AVR, SAMD, ESP8266, etc. You can use both hardware and software serial ports for communication. This library supports the Maxim Integrated **MAX485** and equivalent external transceivers.

This library is a fork of the [**ArduinoRS485**](https://github.com/arduino-libraries/ArduinoRS485) library by Arduino, and is maintained by [**CIRCUITSTATE Electronics**](https://www.circuitstate.com).

## Installation

This library is available from the official **Arduino Library Manager**. Open the Arduino IDE, search for "CSE_ArduinoRS485" and install the latest version of the library.

Additionally, you can download the latest release package from the GitHub repository and install it manually. To do so, open the Arduino IDE, go to `Sketch > Include Library > Add .ZIP Library…` and select the downloaded file.

Another method is to clone the GitHub repository directly into your `libraries` folder. The development branch will have the latest features, bug fixes and other changes. To do so, navigate to your `libraries` folder (usually located at `Documents/Arduino/libraries` on Windows and `~/Documents/Arduino/libraries` on macOS) and execute the following command:

```
git clone https://github.com/CIRCUITSTATE/CSE_ArduinoRS485.git
```

[**Git**](https://git-scm.com) should be installed on your computer.

The library can also be installed via [**PlatformIO**](https://platformio.org). All officially listed Arduino listed libraries are automatically fetched by PlatformIO. Use the [`lib_deps`](https://docs.platformio.org/en/latest/projectconf/sections/env/options/library/lib_deps.html) search option to install the library.

## Dependencies

If your board require the SoftwareSerial library, it needs to be included.

  - [**SoftwareSerial**](https://docs.arduino.cc/learn/built-in-libraries/software-serial/)

## Examples

Three examples are included with this library:

  - **RS485_Sender** - Sends data to a connected receiver.
  - **RS485_Receiver** - Receives data from a connected sender.
  - **RS485_Passthrough** - Sends and receives data between the RS-485 port and the default serial port.

The examples are categorized for three different target boards.

  - [**ESP32**](/examples/ESP32/) (Uses hardware serial port)
  - [**RP2040**](/examples/RP2040/) (Uses hardware serial port)
  - [**ESP8266**](/examples/ESP8266/) (Uses software serial port)

## API Reference

Please see the [API.md](/docs/API.md) file for the API reference.

## References

- [ArduinoRS485 Library by Arduino](https://github.com/arduino-libraries/ArduinoRS485)
- [ArduinoRS485 documentation by Arduino](https://www.arduino.cc/reference/en/libraries/arduinors485/)
- [RS-485 tutorial by CIRCUITSTATE](https://www.circuitstate.com/tutorials/what-is-rs-485-how-to-use-max485-with-arduino-for-reliable-long-distance-serial-communication/)
- [MAX485+CD4069 Module Pinout by CIRCUITSTATE](https://www.circuitstate.com/pinouts/max485-cd4069-rs-485-module-with-auto-data-direction-control-pinout-diagram-and-pin-reference/)
- [Modbus RTU tutorial by CIRCUITSTATE](https://www.circuitstate.com/tutorials/what-is-modbus-communication-protocol-and-how-to-implement-modbus-rtu-with-arduino/)