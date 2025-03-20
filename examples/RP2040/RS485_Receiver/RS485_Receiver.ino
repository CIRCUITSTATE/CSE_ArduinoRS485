
//===================================================================================//
/*
  Filename: RS485_Receiver.ino [RP2040]
  Description: Example Arduino program from the CSE_ArduinoRS485 Arduino library.
  Receives data from the RS485 port and sends it to the default serial port.

  This example was written for and tested with the Raspberry Pi Pico (RP2040). 
  
  Framework: Arduino, PlatformIO
  Author: Vishnu Mohanan (@vishnumaiea, @vizmohanan)
  Maintainer: CIRCUITSTATE Electronics (@circuitstate)
  Version: 1.0.14
  License: MIT
  Source: https://github.com/CIRCUITSTATE/CSE_ArduinoRS485
  Last Modified: +05:30 21:55:35 PM 20-03-2025, Thursday
 */
//===================================================================================//

#include <CSE_ArduinoRS485.h>

//===================================================================================//
// Macros and constants

// You can define the serial port pins here.
#define   PIN_RS485_DE        2
#define   PIN_RS485_RE        3
#define   PIN_RS485_RX        1
#define   PIN_RS485_TX        0

//===================================================================================//
// Globals

// Declare the RS485 interface here with a hardware serial port.
RS485Class RS485 (Serial1, PIN_RS485_DE, PIN_RS485_RE, PIN_RS485_TX); // DE, RE, TX

/* // If you want to use a software serial port, declare it here,
// comment out the previous declaration, and uncomment this section.
#include <SoftwareSerial.h>

SoftwareSerial mySerial (PIN_RS485_RX, PIN_RS485_TX); // RX, TX
RS485Class RS485 (mySerial, PIN_RS485_DE, PIN_RS485_RE, PIN_RS485_TX); // DE, RE, TX */

//===================================================================================//

void setup() {
  Serial.begin (9600);
  while (!Serial); // Wait for the USB to be connected
  
  // // Optional for RP2040. Set the serial port pins here.
  // Serial1.setRX (PIN_RS485_RX);
  // Serial1.setTX (PIN_RS485_TX);

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
