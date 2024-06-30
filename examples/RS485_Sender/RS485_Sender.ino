/*
  RS-485 Sender

  This sketch periodically sends a string over the RS-485 interface

  Originally created by Sandeep Mistry, on 4 July 2018.
  Modified by @vishnumaiea for CIRCUITSTATE Electronics (@circuitstate).

  Source: https://github.com/CIRCUITSTATE/CSE_ArduinoRS485
*/

#include <CSE_ArduinoRS485.h>

int counter = 0;

// If you want to use a software serial port, uncomment the following line.
SoftwareSerial Serial1 (10, 11); // RX, TX

// For using Hardware serial ports, the following line is enough.
RS485Class RS485 (Serial1, 2, 3, 4); // DE, RE, TX

void setup() {
  // Initialize the RS485 interface
  RS485.begin (9600);
}

void loop() {
  RS485.beginTransmission();
  RS485.print ("Hello ");
  RS485.println (counter);
  RS485.endTransmission();

  counter++;

  delay (1000);
}
