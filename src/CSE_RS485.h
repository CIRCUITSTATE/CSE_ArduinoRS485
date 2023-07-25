
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

// Version: 1.0.9
// Last modified: +05:30 20:37:40 PM 25-07-2023, Tuesday
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
// SoftwareSerial is required by board like Arduino Uno and Nano which don't have a
// dedicated secondary hardware serial port.
#define SOFTWARE_SERIAL_REQUIRED defined(__AVR__) || defined(ESP8266)

#if SOFTWARE_SERIAL_REQUIRED
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
