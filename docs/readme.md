# Arduino RS485 library


This Arduino library allows you to send and receive data using the **RS-485** interface standard. Supported by all Arduino-compatible boards such as ESP32, STM32, RP2040, AVR, SAMD, ESP8266, etc. You can use both hardware and software serial ports. This library supports the Maxim Integrated MAX485 and equivalent chipsets.

Three examples are included with this library:

  * **RS485_Sender** - Sends data to a receiver.
  * **RS485_Receiver** - Receives data from a sender.
  * **RS485_Passthrough** - Sends and receives data between the RS-485 port and the default serial port.

To use this library, include the following line at the top of your sketch:

```
#include <CSE_ArduinoRS485.h>
```
