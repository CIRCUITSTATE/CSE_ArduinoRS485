
//===================================================================================//
/*
  Filename: RS485_Receiver.ino [ESP8266]
  Description: Example Arduino program from the CSE_ArduinoRS485 Arduino library.
  Receives data from the RS485 port and sends it to the default serial port.

  This example was written for and tested with the NodeMCU-ESP12E (ESP8266).
  
  Framework: Arduino, PlatformIO
  Author: Vishnu Mohanan (@vishnumaiea, @vizmohanan)
  Maintainer: CIRCUITSTATE Electronics (@circuitstate)
  Version: 1.0.14
  License: MIT
  Source: https://github.com/CIRCUITSTATE/CSE_ArduinoRS485
  Last Modified: +05:30 22:38:53 PM 20-03-2025, Thursday
 */
//===================================================================================//

#include <CSE_ArduinoRS485.h>

//===================================================================================//
// Macros and constants

// You can define the serial port pins here.
// #define   PIN_RS485_DE        16
// #define   PIN_RS485_RE        17
#define   PIN_RS485_RX        14
#define   PIN_RS485_TX        12

//===================================================================================//

// Use the software serial port for the RS485 interface and the hardware serial port for
// the debugging output.
SoftwareSerial softSerial (PIN_RS485_RX, PIN_RS485_TX, false); // RX, TX

// Use the software serial port to create a new RS485 object.
RS485Class RS485 (softSerial, -1, -1, PIN_RS485_TX); // DE, RE, TX

//===================================================================================//

void setup() {
  Serial.begin (9600);
  RS485.begin (9600);

  // Enable transmission. Can be disabled with: RS485.endTransmission();
  RS485.beginTransmission();

  // Enable reception. Can be disabled with: RS485.noReceive();
  RS485.receive();
}

//===================================================================================//

void loop() {
  // Read from the RS485 port and send the data to the default serial port.
  if (RS485.available()) {
    Serial.write (RS485.read());
  }
}

//===================================================================================//
