

//===================================================================================//
/**
  * @file RS485_Receiver.ino
  * @brief RS-485 Receiver for ESP8266 series boards.
  * 
  * This sketch prints any data received from the RS-485 interface to the default
  * serial port.
  * 
  * @date +05:30 08:56:08 PM 27-10-2024, Sunday
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
SoftwareSerial softSerial (PIN_RS485_RX, PIN_RS485_TX); // RX, TX

// Use the software serial port to create a new RS485 object.
RS485Class RS485 (softSerial, -1, -1, PIN_RS485_TX); // DE, RE, TX

void setup() {
  Serial.begin (9600);
  while (!Serial);

  RS485.begin (9600, SWSERIAL_8N1, PIN_RS485_RX, PIN_RS485_TX);

  // Enable reception. Can be disabled with: RS485.noReceive();
  RS485.receive();
}

void loop() {
  if (RS485.available()) {
    Serial.write (RS485.read());
  }
}

