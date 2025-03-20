
//===================================================================================//
/*
  Filename: RS485_Sender.ino [ESP8266]
  Description: Example Arduino program from the CSE_ArduinoRS485 Arduino library.
  Periodically sends "Hello" string to the RS485 port.

  This example was written for and tested with the NodeMCU-ESP12E (ESP8266).
  
  Framework: Arduino, PlatformIO
  Author: Vishnu Mohanan (@vishnumaiea, @vizmohanan)
  Maintainer: CIRCUITSTATE Electronics (@circuitstate)
  Version: 1.0.14
  License: MIT
  Source: https://github.com/CIRCUITSTATE/CSE_ArduinoRS485
  Last Modified: +05:30 22:46:55 PM 20-03-2025, Thursday
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

int counter = 0;

//===================================================================================//

void setup() {
  Serial.begin (9600);
  RS485.begin (9600);
}

//===================================================================================//

void loop() {
  RS485.beginTransmission();
  RS485.print ("Hello ");
  RS485.println (counter);
  RS485.endTransmission();

  counter++;

  delay (1000);
}

//===================================================================================//
