/*
  RS-485 Passthrough.

  This sketch relays data sent and received between the Serial port and the RS-485 interface.

  Originally created by Sandeep Mistry, on 4 July 2018.
  Modified by @vishnumaiea for CIRCUITSTATE Electronics (@circuitstate).

  Source: https://github.com/CIRCUITSTATE/CSE_ArduinoRS485
*/

#include <CSE_ArduinoRS485.h>

// Declare the RS485 interface here with a hardware serial port.
RS485Class RS485 (Serial1, 2, 3, 4); // DE, RE, TX

/* // If you want to use a software serial port, declare it here,
// comment out the previous declaration, and uncomment this section.
#include <SoftwareSerial.h>

SoftwareSerial mySerial (10, 11); // RX, TX
RS485Class RS485 (mySerial, 2, 3, 4); // DE, RE, TX */

void setup() {
  Serial.begin (9600);
  RS485.begin (9600);

  // Enable transmission. Can be disabled with: RS485.endTransmission();
  RS485.beginTransmission();

  // Enable reception. Can be disabled with: RS485.noReceive();
  RS485.receive();
}

void loop() {
  if (Serial.available()) {
    RS485.write (Serial.read());
  }

  if (RS485.available()) {
    Serial.write (RS485.read());
  }
}
