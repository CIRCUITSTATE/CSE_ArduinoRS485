
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
// Last modified: +05:30 21:11:24 PM 30-06-2024, Sunday
// Source: https://github.com/CIRCUITSTATE/CSE_ArduinoRS485

//===================================================================================//

#include "CSE_RS485.h"

//===================================================================================//

#if SOFTWARE_SERIAL_REQUIRED
  /**
   * @brief Constructor for SoftwareSerial RS485. The RE pin is optional. If not defined,
   * it is set to -1 and only the DE pin will be used for read/write control. The TX pin
   * is also optional. If not defined, it is set to -1. If defined, it will be used to
   * assert break condition on the RS-485 bus.
   * 
   * @param swSerial Software serial port. You must create one first.
   * @param dePin DE pin of the RS485 transceiver.
   * @param rePin RE pin of the RS485 transceiver. Optional. Defaults to -1.
   * @param txPin The TX pins of the serial port. Optional. Defaults to -1.
   * @return RS485Class:: 
   */
  RS485Class:: RS485Class (SoftwareSerial& swSerial, int dePin, int rePin, int txPin) :
    _serial (&swSerial),
    _dePin (dePin),
    _rePin (rePin),
    _txPin (txPin),
    _transmisionBegun (false) {
  }
#else
  /**
   * @brief Constructor for HardwareSerial RS485. The RE pin is optional. If not defined,
   * it is set to -1 and only the DE pin will be used for read/write control. The TX pin
   * is also optional. If not defined, it is set to -1. If defined, it will be used to
   * assert break condition on the RS-485 bus.
   * 
   * @param hwSerial Hardware serial port. You must have a free hardware serial port.
   * @param dePin DE pin of the RS485 transceiver.
   * @param rePin RE pin of the RS485 transceiver. Optional. Defaults to -1.
   * @param txPin The TX pins of the serial port. Optional. Defaults to -1.
   * @return RS485Class:: 
   */
  RS485Class:: RS485Class (HardwareSerial& hwSerial, int dePin, int rePin, int txPin) :
    _serial (&hwSerial),
    _dePin (dePin),
    _rePin (rePin),
    _txPin (txPin),
    _transmisionBegun (false) {
  }
#endif

//===================================================================================//
/**
 * @brief This is the plain begin() method. It will set the baudrate to 0 and won't
 * initialize the serial port. You must initialize the serial port yourself before
 * calling this method.
 * 
 */
void RS485Class:: begin() {
  begin (0, SERIAL_8N1, RS485_DEFAULT_PRE_DELAY, RS485_DEFAULT_POST_DELAY);
}

//===================================================================================//
/**
 * @brief Initializes the serial port with the specified baudrate. Other settings are
 * set to default values.
 * 
 * @param baudrate In bps.
 */
void RS485Class:: begin (unsigned long baudrate) {
  begin (baudrate, SERIAL_8N1, RS485_DEFAULT_PRE_DELAY, RS485_DEFAULT_POST_DELAY);
}

//===================================================================================//
/**
 * @brief Initializes the serial port with the specified baudrate and configuration.
 * 
 * @param baudrate In bps.
 * @param predelay In microseconds.
 * @param postdelay In microseconds.
 */
void RS485Class:: begin (unsigned long baudrate, int predelay, int postdelay) {
  begin (baudrate, SERIAL_8N1, predelay, postdelay);
}

//===================================================================================//
/**
 * @brief Initializes the serial port with the specified baudrate and configuration.
 * 
 * @param baudrate In bps.
 * @param config Example SERIAL_8N1.
 */
void RS485Class::begin (unsigned long baudrate, uint16_t config) {
  begin (baudrate, config, RS485_DEFAULT_PRE_DELAY, RS485_DEFAULT_POST_DELAY);
}

//===================================================================================//
/**
 * @brief Initializes the serial port with the specified baudrate, configuration.
 * 
 * @param baudrate In bps.
 * @param config Example SERIAL_8N1.
 * @param predelay In microseconds.
 * @param postdelay In microseconds.
 */
void RS485Class:: begin (unsigned long baudrate, uint16_t config, int predelay, int postdelay) {
  _baudrate = baudrate;
  _config = config;

  // Set only if not already initialized with ::setDelays
  _predelay = _predelay == 0 ? predelay : _predelay;
  _postdelay = _postdelay == 0 ? postdelay : _postdelay;

  if (_dePin > -1) {
    pinMode (_dePin, OUTPUT);
    digitalWrite (_dePin, LOW);
  }

  if (_rePin > -1) {
    pinMode (_rePin, OUTPUT);
    digitalWrite (_rePin, HIGH);
  }

  _transmisionBegun = false;

  // Only initialize the serial port if the baudrate is greater than 0.
  // Making the baudrate 0 allows you to initialize the serial port manually in your main code.
  if (_baudrate > 0) {
    #if defined(ARDUINO_OPTA)
      auto _opta_uart = static_cast<UART *> (_serial);
      _opta_uart->begin (_baudrate, _config, true);
    #elif defined(SOFTWARE_SERIAL_REQUIRED)
      #if defined(ARDUINO_ARCH_AVR)
        _serial->begin (_baudrate); // AVR software serial doesn't support config
      #else
        _serial->begin (_baudrate, _config);
      #endif
    #else
      _serial->begin (_baudrate, _config);  // Default
    #endif
  }
}

//===================================================================================//
/**
 * @brief Closes the serial port. This will work even if the serial port was initialized
 * manually in your main code.
 * 
 */
void RS485Class:: end() {
  _serial->end();

  if (_dePin > -1) {
    digitalWrite (_dePin, LOW);
    pinMode (_dePin, INPUT);
  }
  
  if (_rePin > -1) {
    digitalWrite (_rePin, LOW);
    pinMode (_rePin, INPUT);
  }
}

//===================================================================================//
/**
 * @brief Returns the number of bytes available for reading.
 * 
 * @return int The number of bytes available for reading.
 */
int RS485Class:: available() {
  return _serial->available();
}

//===================================================================================//
/**
 * @brief Returns the next byte (character) of incoming serial data without removing it
 * from the buffer.
 * 
 * @return int The next single byte of data available in the serial buffer.
 */
int RS485Class:: peek() {
  return _serial->peek();
}

//===================================================================================//
/**
 * @brief Reads a single byte from the serial receive buffer.
 * 
 * @return int Data byte.
 */
int RS485Class:: read (void) {
  return _serial->read();
}

//===================================================================================//
/**
 * @brief Removes all data from the serial receive buffer.
 * 
 */
void RS485Class:: flush() {
  return _serial->flush();
}

//===================================================================================//
/**
 * @brief Writes a single byte of data to the transmit buffer.
 * 
 * @param b The data byte to write.
 * @return size_t Always 1.
 */
size_t RS485Class:: write (uint8_t b) {
  if (!_transmisionBegun) {
    setWriteError();
    return 0;
  }

  return _serial->write (b);
}

//===================================================================================//

RS485Class:: operator bool() {
  return true;
}

//===================================================================================//
/**
 * @brief Asserts the DE pin and waits for the predelay time. DE has precedence over RE.
 * That means, if both DE and RE are actively asserted, the transceiver will be in
 * transmit mode.
 * 
 * This function must be called before writing to the RS485 port.
 * 
 */
void RS485Class:: beginTransmission() {
  if (assertDE()) { // Can assert before delay
    if (_predelay) delayMicroseconds (_predelay);
  }

  _transmisionBegun = true;
}

//===================================================================================//
/**
 * @brief Ends the transmission by flushing the serial port and deasserting the DE pin.
 * 
 */
void RS485Class:: endTransmission() {
  _serial->flush();

  if (_dePin > -1) {
    if (_postdelay) delayMicroseconds (_postdelay);
    deassertDE(); // Only deassert after delay
  }

  _transmisionBegun = false;
}

//===================================================================================//
/**
 * @brief Puts the transceiver in receive mode by asserting the RE pin. If the DE pin
 * is currently being asserted, this has no effect, because DE has precedence over RE.
 * Call the endTransmission() function to deassert the DE pin to free the bus.
 * 
 */
void RS485Class:: receive() {
  assertRE();
}

//===================================================================================//
/**
 * @brief Puts the transceiver in a no-receive mode by deasserting the RE pin. If the DE
 * pin is also deasserted, then the transceiver will be in a high impedance state.
 * 
 */
void RS485Class:: noReceive() {
  deassertRE();
}

//===================================================================================//
/**
 * @brief Asserts a break condition on the RS-485 bus. This is done by holding the
 * TX pin of the serial port LOW for a specified duration. If the TX pins is not set,
 * this function has no effect. The serial port will be reinitialized only if the
 * baudrate is greater than 0. If the baudrate is 0, then you have to manually
 * initialize the serial port in your main code, just after calling this function.
 * 
 * @param duration The duration in milliseconds.
 */
void RS485Class:: sendBreak (unsigned int duration) {
  if (_txPin > -1) {
    _serial->flush(); // Clear the transmit buffer
    _serial->end(); // Close the serial port
    
    pinMode (_txPin, OUTPUT);
    digitalWrite (_txPin, LOW);

    delay (duration);

    // Serial port will be reinitialized only if the baudrate is greater than 0.
    if (_baudrate > 0) {
      #if defined(ARDUINO_OPTA)
        auto _opta_uart = static_cast<UART *> (_serial);
        _opta_uart->begin (_baudrate, _config, true);
      #elif defined(SOFTWARE_SERIAL_REQUIRED)
        #if defined(ARDUINO_ARCH_AVR)
          _serial->begin (_baudrate); // AVR software serial doesn't support config
        #else
          _serial->begin (_baudrate, _config);
        #endif
      #else
        _serial->begin (_baudrate, _config);  // Default
      #endif
    }
  }
}

//===================================================================================//
/**
 * @brief Same as sendBreak() but with a duration in microseconds.
 * 
 * @param duration The duration in microseconds.
 */
void RS485Class:: sendBreakMicroseconds (unsigned int duration) {
  if (_txPin > -1) {
    _serial->flush(); // Clear the transmit buffer
    _serial->end(); // Close the serial port

    pinMode (_txPin, OUTPUT);
    digitalWrite (_txPin, LOW);

    delayMicroseconds (duration);

    // Serial port will be reinitialized only if the baudrate is greater than 0.
    if (_baudrate > 0) {
      #if defined(ARDUINO_OPTA)
        auto _opta_uart = static_cast<UART *> (_serial);
        _opta_uart->begin (_baudrate, _config, true);
      #elif defined(SOFTWARE_SERIAL_REQUIRED)
        #if defined(ARDUINO_ARCH_AVR)
          _serial->begin (_baudrate); // AVR software serial doesn't support config
        #else
          _serial->begin (_baudrate, _config);
        #endif
      #else
        _serial->begin (_baudrate, _config);  // Default
      #endif
    }
  }
}

//===================================================================================//
/**
 * @brief Sets the pins of RS485 transceiver.
 * 
 * @param dePin The DE pin of the transceiver.
 * @param rePin The RE pin of the transceiver. Optional. Defaults to -1.
 * @param txPin The TX pin of the serial port. Optional. Defaults to -1.
 */
void RS485Class:: setPins (int dePin, int rePin, int txPin) {
  _txPin = txPin;
  _dePin = dePin;
  _rePin = rePin;
}

//===================================================================================//
/**
 * @brief Sets the predelay and postdelay times.
 * 
 * @param predelay Time in microseconds.
 * @param postdelay Time in microseconds.
 */
void RS485Class:: setDelays (int predelay, int postdelay) {
  _predelay = predelay;
  _postdelay = postdelay;
}

//===================================================================================//
/**
 * @brief Asserts (set to HIGH) the DE pin if the pin is defined.
 * 
 * @return true If the DE pin is defined; false otherwise.
 * 
 */
bool RS485Class:: assertDE() {
  if (_dePin > -1) {
    digitalWrite (_dePin, HIGH);
    return true;
  }
  return false;
}

//===================================================================================//
/**
 * @brief Deasserts (set to LOW) the DE pin if the pin is defined.
 * 
 * @return true If the DE pin is defined; false otherwise.
 * 
 */
bool RS485Class:: deassertDE() {
  if (_dePin > -1) {
    digitalWrite (_dePin, LOW);
    return true;
  }
  return false;
}

//===================================================================================//
/**
 * @brief Asserts (set to LOW) the RE pin if the pin is defined.
 * 
 * @return true If the RE pin is defined; false otherwise.
 * 
 */
bool RS485Class:: assertRE() {
  if (_rePin > -1) {
    digitalWrite (_rePin, LOW);
    return true;
  }
  return false;
}

//===================================================================================//
/**
 * @brief Deasserts (set to HIGH) the RE pin if the pin is defined.
 * 
 * @return true If the RE pin is defined; false otherwise.
 * 
 */
bool RS485Class:: deassertRE() {
  if (_rePin > -1) {
    digitalWrite (_rePin, HIGH);
    return true;
  }
  return false;
}

//===================================================================================//
