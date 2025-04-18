
//===================================================================================//
/*
  Filename: RS485_Sender.ino [ESP32]
  Description: Example Arduino program from the CSE_ArduinoRS485 Arduino library.
  Periodically sends "Hello" string to the RS485 port.

  This example was written for and tested with the FireBeetle-ESP32E (ESP32).
  
  Framework: Arduino, PlatformIO
  Author: Vishnu Mohanan (@vishnumaiea, @vizmohanan)
  Maintainer: CIRCUITSTATE Electronics (@circuitstate)
  Version: 1.0.14
  License: MIT
  Source: https://github.com/CIRCUITSTATE/CSE_ArduinoRS485
  Last Modified: +05:30 22:39:26 PM 20-03-2025, Thursday
 */
//===================================================================================//

#include <CSE_ArduinoRS485.h>

//===================================================================================//
// Macros and constants

// You can define the serial port pins here.
#define   PIN_RS485_DE        16
#define   PIN_RS485_RE        17
#define   PIN_RS485_RX        9
#define   PIN_RS485_TX        10

//===================================================================================//
// Globals

// Declare the RS485 interface here with a hardware serial port.
RS485Class RS485 (Serial1, PIN_RS485_DE, PIN_RS485_RE, PIN_RS485_TX); // DE, RE, TX

/* // If you want to use a software serial port, declare it here,
// comment out the previous declaration, and uncomment this section.
#include <SoftwareSerial.h>

SoftwareSerial mySerial (PIN_RS485_RX, PIN_RS485_TX); // RX, TX
RS485Class RS485 (mySerial, PIN_RS485_DE, PIN_RS485_RE, PIN_RS485_TX); // DE, RE, TX */

int counter = 0;

//===================================================================================//

void setup() {
  Serial.begin (9600);
  RS485.begin (9600);

    // // Optional for ESP32. Set the serial port pins here.
  // // SetPins can be called after or before begin() for ESP32.
  // Serial1.setPins (PIN_RS485_RX, PIN_RS485_TX);
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
