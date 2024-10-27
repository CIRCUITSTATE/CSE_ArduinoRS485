
//===================================================================================//
/**
  * @file RS485_Passthrough.ino
  * @brief RS-485 Passthrough for ESP8266 series boards.
  * 
  * This sketch relays data sent and received between the default Serial port and
  * the RS-485 interface.
  * 
  * @date +05:30 08:58:44 PM 27-10-2024, Sunday
  * @author Vishnu Mohanan (@vishnumaiea)
  * @par GitHub Repository: https://github.com/CIRCUITSTATE/CSE_ArduinoRS485
  * @par MIT License
  * 
  */
//===================================================================================//

#include <CSE_ArduinoRS485.h>

// You can define the serial port pins here.
#define   PIN_RS485_RX        14
#define   PIN_RS485_TX        12

// Use the software serial port for the RS485 interface and the hardware serial port for
// the debugging output.
SoftwareSerial softSerial (PIN_RS485_RX, PIN_RS485_TX, false); // RX, TX

// Use the software serial port to create a new RS485 object.
RS485Class RS485 (softSerial, -1, -1, PIN_RS485_TX); // DE, RE, TX

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
