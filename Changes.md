
# Changes

Changelog for the `CSE_ArduinoRS485` library. Latest entries are at the top.


#
### **+05:30 11:25:41 PM 20-03-2025, Thursday**

  - Bumped up the version in Arduino library specification files.
  - Updated project information and attribution in the source files.
  - New Version 🆕 `1.0.14`.

#
### **+05:30 10:41:11 PM 20-03-2025, Thursday**

  - Updated examples for ESP32, ESP8266 and RP2040.

#
### **+05:30 10:26:50 PM 27-10-2024, Sunday**

  - Updated ESP8266 examples.

#
### **+05:30 09:07:22 PM 27-10-2024, Sunday**

  - Limited the `Config` type creation to only ESP8266.
    - ESP32 has been removed since it has multiple hardware serial ports.

#
### **+05:30 08:59:47 PM 27-10-2024, Sunday**

  - Added support for `Config` serial configuration for ESP8266 software serial interfaces.
  - Added conversion between `uint16_t` and `Config` values.
  - Created target specific example folders for ESP32, ESP8266 and RP2040.
  - Updated the examples for ESP8266.
    - All examples use software serial ports for the RS485 interface and the default serial port for the debugging output.
  - Updated `Changes.md` styling.

#
### **+05:30 10:40:59 PM 06-07-2024, Saturday**

  - Added support for generic boards with more than two serial ports. The previous code was not compiling for boards like Raspberry Pi Pico.

#
### **+05:30 08:31:31 PM 30-06-2024, Sunday**

  - Added new platform/board checking pre-processor section to enable the SoftwareSerial library. Some AVR boards like Mega 2560 have multiple hardware serial ports and therefore shouldn't be using the SoftwareSerial library. The new changes fix this issue.
  - The examples are compiling for Uno, Mega 2560 and ESP32 DevKit.
  - New Revision 🆕 `v1.0.13`.

#
### **+05:30 12:34:00 AM 21-05-2024, Tuesday**

  - Fixed typo in `RS485_Passthrough` example folder name.

#
### **+05:30 03:04:59 PM 28-01-2024, Sunday**

  - Added fix for SoftwareSerial port not supporting custom serial frame configuration on AVR platform.
  - Added `ARDUINO_ARCH_AVR` platform check.
  - Added Changes.md file.
  - Updated API.md.
  - Updated Readme.md.
  - New version 🆕 `v1.0.12`

