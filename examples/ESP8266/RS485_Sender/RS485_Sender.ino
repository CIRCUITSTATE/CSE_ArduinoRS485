
//===================================================================================//
/**
  * @file RS485_Sender.ino
  * @brief RS-485 Sender for ESP8266 series boards.
  * 
  * This sketch periodically sends a string over the RS-485 interface.
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
#define   PIN_RS485_RX        14
#define   PIN_RS485_TX        12

int counter = 0;

// If you want to use a software serial port, uncomment the following line.
SoftwareSerial softSerial (PIN_RS485_RX, PIN_RS485_TX, false); // RX, TX

// Use the software serial port to create a new RS485 object.
RS485Class RS485 (softSerial, -1, -1, PIN_RS485_TX); // DE, RE, TX

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
