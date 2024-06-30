
//===================================================================================//
/*
  This file is part of the ArduinoRS485 library.
  Copyright (c) 2018 Arduino SA. All rights reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/
//===================================================================================//

// Version: 1.0.13
// Last modified: +05:30 21:11:21 PM 30-06-2024, Sunday
// Source: https://github.com/CIRCUITSTATE/CSE_ArduinoRS485

//===================================================================================//

#ifndef _CSE_RS485_H_INCLUDED
#define _CSE_RS485_H_INCLUDED

//===================================================================================//

#include <Arduino.h>

//===================================================================================//

#define RS485_DEFAULT_PRE_DELAY     50  // In microseconds
#define RS485_DEFAULT_POST_DELAY    50  // In microseconds

// You can expand the software serial support here.
// SoftwareSerial is required by boards like Arduino Uno and Nano which don't have a
// dedicated secondary hardware serial port.
// #define SOFTWARE_SERIAL_REQUIRED defined(__AVR__) || defined(ARDUINO_ARCH_AVR) || defined(ESP8266) 

// #if !defined(HAVE_HWSERIAL1) && !defined(HAVE_HWSERIAL2) && !defined(HAVE_HWSERIAL3) && !defined(HAVE_HWSERIAL4)
//   #define SOFTWARE_SERIAL_REQUIRED 1
// #endif

// // Check if the user has defined the macro to control SoftwareSerial inclusion
// #ifdef DISABLE_SOFTWARE_SERIAL
//   #define SOFTWARE_SERIAL_REQUIRED 0
// #else
//   #define SOFTWARE_SERIAL_REQUIRED 1
// #endif

// Define default values
#define _HAVE_HWSERIAL1

// Check for specific architectures and boards
#if defined(ARDUINO_AVR_UNO) || defined(ARDUINO_AVR_NANO)
  // Arduino Uno and Nano have only one hardware serial port
  #define _HAVE_HWSERIAL1
#elif defined(ARDUINO_AVR_MEGA2560)
  // Arduino Mega has four hardware serial ports
  #define _HAVE_HWSERIAL1
  #define _HAVE_HWSERIAL2
  #define _HAVE_HWSERIAL3
  #define _HAVE_HWSERIAL4
#elif defined(ARDUINO_ARCH_ESP32)
  // ESP32 typically has three hardware serial ports
  #define _HAVE_HWSERIAL1
  #define _HAVE_HWSERIAL2
  #define _HAVE_HWSERIAL3
#endif

// Define a flag to include SoftwareSerial if no additional UARTs are available
#if !defined(_HAVE_HWSERIAL2) && !defined(_HAVE_HWSERIAL3) && !defined(_HAVE_HWSERIAL4)
  #define SOFTWARE_SERIAL_REQUIRED 1
#endif

// The SoftwareSerial is loaded automatically when required.
#ifdef SOFTWARE_SERIAL_REQUIRED
  #include <SoftwareSerial.h>
#endif

//===================================================================================//
/**
 * @brief RS485 class. Creates a dedicated serial port for RS485 communication. This
 * makes use of the Steam class.
 * 
 * API documentation can be found in the .cpp file.
 * 
 */
class RS485Class : public Stream {
  public:
    // Adapt the constructor to the type of serial port being used.
    #if SOFTWARE_SERIAL_REQUIRED
      RS485Class (SoftwareSerial& swSerial, int dePin, int rePin = -1, int txPin = -1);
    #else
      RS485Class (HardwareSerial& hwSerial, int dePin, int rePin = -1, int txPin = -1);
    #endif

    void begin();
    virtual void begin (unsigned long baudrate);
    virtual void begin (unsigned long baudrate, uint16_t config);
    virtual void begin (unsigned long baudrate, int predelay, int postdelay);
    virtual void begin (unsigned long baudrate, uint16_t config, int predelay, int postdelay);
    virtual void end();
    virtual int available();
    virtual int peek();
    virtual int read (void);
    virtual void flush();
    virtual size_t write (uint8_t b);
    using Print:: write; // pull in write(str) and write(buf, size) from Print
    virtual operator bool();

    void beginTransmission();
    void endTransmission();
    void receive();
    void noReceive();

    void sendBreak (unsigned int duration);
    void sendBreakMicroseconds (unsigned int duration);

    void setPins (int dePin, int rePin = -1, int txPin = -1);
    void setDelays (int predelay, int postdelay);

    bool assertDE();
    bool deassertDE();
    bool assertRE();
    bool deassertRE();

  private:
    // Create the suitable type of serial port
    #if SOFTWARE_SERIAL_REQUIRED
      SoftwareSerial* _serial;  // Software serial port
    #else
      HardwareSerial* _serial; // Hardware serial port
    #endif

    int _dePin; // DE pin of the RS485 transceiver
    int _rePin; // RE pin of the RS485 transceiver
    int _txPin; // TX pin can be optionally used to send break condition
    int _predelay = 0;  // The delay in microseconds before sending the data
    int _postdelay = 0; // The delay in microseconds after sending the data

    bool _transmisionBegun; // True if transmission has begun
    unsigned long _baudrate; // Baudrate of the serial port
    uint16_t _config; // Config of the serial port
};

#endif

//===================================================================================//
