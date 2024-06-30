/*
  RS-485 Receiver.

  This sketch prints any data received from the RS-485 interface to the Serial port.

  Originally created by Sandeep Mistry, on 4 July 2018.
  Modified by @vishnumaiea for CIRCUITSTATE Electronics (@circuitstate).

  Source: https://github.com/CIRCUITSTATE/CSE_ArduinoRS485
*/

#include <CSE_ArduinoRS485.h>

// If you want to use a software serial port, uncomment the following line.
// SoftwareSerial Serial1 (10, 11); // RX, TX

// For using Hardware serial ports, the following line is enough.
RS485Class RS485 (Serial1, 2, 3, 4); // DE, RE, TX

void setup() {
  Serial.begin (9600);
  while (!Serial);

  RS485.begin (9600);

  // Enable reception. Can be disabled with: RS485.noReceive();
  RS485.receive();
}

void loop() {
  if (RS485.available()) {
    Serial.write (RS485.read());
  }
}

