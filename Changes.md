
# Changes

Changelog for the `CSE_ArduinoRS485` library. Latest entries are at the top.


#
### **+05:30 10:40:59 PM 06-07-2024, Saturday**

  * Added support for generic boards with more than two serial ports. The previous code was not compiling for boards like Raspberry Pi Pico.

#
### **+05:30 08:31:31 PM 30-06-2024, Sunday**

  * Added new platform/board checking preprocessor section to enable the SoftrwareSerial library. Some AVR boards like Mega 2560 have multiple harware serial ports and therefore shouldn't be using the SoftwareSerial library. The new changes fix this issue.
  * The examples are compiling for Uno, Mega 2560 and ESP32 DevKit.
  * New Revision `v1.0.13`.

#
### **+05:30 12:34:00 AM 21-05-2024, Tuesday**

  * Fixed typo in `RS485_Passthrough` example folder name.

#
### **+05:30 03:04:59 PM 28-01-2024, Sunday**

  * Added fix for SoftwareSerial port not supporting custom serial frame configuration on AVR platform.
  * Added `ARDUINO_ARCH_AVR` platform check.
  * Added Changes.md file.
  * Updated API.md.
  * Updated Readme.md.
  * New version 🆕 `v1.0.12`

