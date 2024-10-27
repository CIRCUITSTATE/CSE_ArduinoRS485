
//===================================================================================//
/**
  * @file RS485_Sender.ino
  * @brief RS-485 Sender for ESP8266 series boards.
  * 
  * This sketch prints any data received from the RS-485 interface to the Serial port.
  * 
  * @date +05:30 08:56:13 PM 27-10-2024, Sunday
  * @author Vishnu Mohanan (@vishnumaiea)
  * @par GitHub Repository: https://github.com/CIRCUITSTATE/CSE_ArduinoRS485
  * @par MIT License
  * 
  */
//===================================================================================//

#include <CSE_ArduinoRS485.h>

// You can define the serial port pins here.
#define   PIN_RS485_RX        16
#define   PIN_RS485_TX        17

// // Use the software serial port for the RS485 interface and the hardware serial port for
// // the debugging output.
// SoftwareSerial softSerial (PIN_RS485_RX, PIN_RS485_TX, false); // RX, TX

// Use the software serial port to create a new RS485 object.
RS485Class RS485 (Serial1, -1, -1, PIN_RS485_TX); // DE, RE, TX

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

