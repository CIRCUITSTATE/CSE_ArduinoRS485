# CSE_ArduinoRS485 library

Version 1.0.12, +05:30 03:16:49 PM 28-01-2024, Sunday, Monday

### Index

- [CSE\_ArduinoRS485 library](#cse_arduinors485-library)
    - [Index](#index)
    - [`RS485Class()`](#rs485class)
    - [`begin()`](#begin)
    - [`end()`](#end)
    - [`available()`](#available)
    - [`peek()`](#peek)
    - [`read()`](#read)
    - [`write()`](#write)
    - [`flush()`](#flush)
    - [`beginTransmission()`](#begintransmission)
    - [`endTransmission()`](#endtransmission)
    - [`receive()`](#receive)
    - [`noReceive()`](#noreceive)
    - [`sendBreak()`](#sendbreak)
    - [`sendBreakMicroseconds()`](#sendbreakmicroseconds)
    - [`setPins()`](#setpins)
    - [`setDelays()`](#setdelays)
    - [`assertDE()`](#assertde)
    - [`deassertDE()`](#deassertde)
    - [`assertRE()`](#assertre)
    - [`deassertRE()`](#deassertre)


### `RS485Class()`

Creates a new `RS485Class` object. If you are using a hardware serial port, you can simply send its name as a parameter. If you are using software serial, you must include the SoftwareSerial library first and create a new object of that type. Then send the name of the object as a parameter.

Currently, software serial is supported only on AVR (Arduino Uno, Nano, etc.) and ESP8266 boards. The macro `SOFTWARE_SERIAL_REQUIRED` is used to check if a software serial port to be used. You can update the board support by adding the board name to the macro in the `CSE_RS485.h` file. 
#### Syntax 

```cpp
RS485Class RS485 (auto serial, int dePin, int rePin, int txPin);
```

#### Parameters

* _`serial`_: Name of the serial port to use. Can be hardware serial (`HardwareSerial`) or software serial (`SoftwareSerial`).
* _`dePin`_: Drive enable pin.
* _`rePin`_: Receive enable pin. Optional. Default: `-1`.
* _`txPin`_: Serial transmit pin (used to send break signals). Optional. Default: `-1`.

### `begin()`

Initializes the RS485 object. The baudrate can be left empty to make it `0`. This will prevent the serial port from being initialized by the RS485 library. You have to then manually initialize the serial port before calling any RS485 library functions. If the baudrate is non-zero, the user can also specify the UART configuration, for example `SERIAL_8N1`. Custom UART configurations are not supported by all platforms, especially when using Software Serial ports. Currently, custom UART frame configurations are ignored when using software serial ports on the AVR platform. It is also possible to set pre and post delays in milliseconds for each communication.

#### Syntax 

There are 5 overloads of this function:

```cpp
RS485.begin()
RS485.begin (baudrate)
RS485.begin (unsigned long baudrate, uint16_t config)
RS485.begin (unsigned long baudrate, int predelay, int postdelay)
RS485.begin (unsigned long baudrate, uint16_t config, int predelay, int postdelay)
```

#### Parameters

* _`baudrate`_: Communication speed in bits per second (baud). Optional. Default: `0`. If `0`, the serial port will not be initialized.
* _`config`_: Serial port configuration. Example, `SERIAL_8N1`.
* _`predelay`_: Delay in milliseconds before sending data. Optional. Default: `0`.
* _`postdelay`_: Delay in milliseconds after sending data. Optional. Default: `0`.

#### Returns

None.

### `end()`

Disables RS485 communication. This will close the serial port and reset the DE and RE pins to `INPUT` mode. The serial port will be closed regardless of whether it was initialized by the RS485 library or not.

#### Syntax 

```cpp
RS485.end()
```

#### Parameters

None. 

#### Returns

None.

### `available()`

Returns the number of bytes (characters) available for reading from the RS485 port. This is data that already arrived and is stored in the serial receive buffer.

#### Syntax 

```cpp
RS485.available()
```

#### Parameters

None. 

#### Returns

* _`int`_: The number of bytes available to read.

### `peek()`

Returns the next byte (character) of the incoming serial data without removing it from the internal serial buffer. That is, successive calls to `peek()` will return the same character, as will the next call to `read()`. The original Arduino serial `peek()` function returns an `int` type. So this library also does the same.

#### Syntax 

```cpp
RS485.peek()
```

#### Parameters

None. 

#### Returns

* _`int`_: The first byte of incoming serial data available or `-1` if no data is available. 

### `read()`

Returns a single byte from the serial read buffer. Return `-1` if no data is available. Each read operation will remove the byte from the buffer.

#### Syntax 

```cpp
RS485.read()
```

#### Parameters

None. 

#### Returns

* _`int`_: The first byte of incoming serial data available or `-1` if no data is available. 

### `write()`

Writes binary data to the serial port. This data is sent as a byte or series of bytes.

#### Syntax 

```cpp
RS485.write (uint8_t b)
```

#### Parameters

* _`b`_: unsigned char.

#### Returns

* _`size_t`_: The number of bytes written.

### `flush()`

Waits for the transmission of outgoing serial data to complete.

#### Syntax 

```cpp
RS485.flush()
```

#### Parameters

None.

#### Returns

None.

### `beginTransmission()`

Starts RS-485 transmission. This will assert the DE pin and wait for a pre-delay if it is set. The DE pin has priority over the RE pin. That means, if both DE and RE are actively asserted, the transceiver will be in transmission mode.

You must call this function before any write operations.

#### Syntax 

```cpp
RS485.beginTransmission()
```

#### Parameters

None.

#### Returns

None.

### `endTransmission()`

Ends the RS-485 transmission. This deasserts the DE pin and the RE pin is not modified (since DE has priority over RE). If the post-delay is non-zero, the function wait for the specified duration before deasserting the DE pin.

#### Syntax 

```cpp
RS485.endTransmission()
```

#### Parameters

None.

#### Returns

None.

### `receive()`

Puts the transceiver in receive mode by asserting the RE pin. If the DE pin is currently being asserted, this has no effect, because DE has precedence over RE. Call the `endTransmission()` function to deassert the DE pin to free the bus.

#### Syntax 

```cpp
RS485.receive()
```

#### Parameters

None.

#### Returns

None.

### `noReceive()`

Puts the transceiver in a no receive mode by deasserting the RE pin. If the DE pin is also deasserted, then the transceiver is in a high impedance state.

#### Syntax 

```cpp
RS485.noReceive()
```

#### Parameters

None.

#### Returns

None.

### `sendBreak()`

Sends a serial break signal for the specified duration in milliseconds. This is done by closing the serial port, holding the TX pin of the serial port `LOW` for a specified duration in milliseconds, and then reinitializing the serial port. If the TX pins is not set, this function has no effect. The serial port will be reinitialized only if the baudrate is greater than `0`. If the baudrate is `0`, then you have to manually initialize the serial port in your main code, just after calling this function.

#### Syntax 

```cpp
RS485.sendBreak (unsigned int duration)
```

#### Parameters

* _`duration`_: Duration of the break signal in milliseconds.

#### Returns

None.

### `sendBreakMicroseconds()`

Same as `sendBreak()` but the duration is specified in microseconds.

#### Syntax 

```cpp
RS485.sendBreak (unsigned int duration)
```

#### Parameters

* _`duration`_: Duration of the break signal in microseconds.

#### Returns

None.

### `setPins()`

Modify the pins used to communicate with the RS-485 transceiver.

#### Syntax 

```cpp
RS485.setPins (int dePin, int rePin, int txPin)
```

#### Parameters

* _`dePin`_: Drive output enable pin.
* _`rePin`_: Receiver output enable pin.
* _`txPin`_: Transmission pin (used to send break signals).

#### Returns

None.
### `setDelays()`

Sets the pre and post delays in milliseconds.

#### Syntax 

```cpp
RS485.setDelays (int predelay, int postdelay)
```

#### Parameters

* _`predelay`_: The delay before sending data.
* _`postdelay`_: The delay after sending data.

#### Returns

None.

### `assertDE()`

Asserts (set to `HIGH`) the DE pin if the pin is defined. The function returns `true` if the assertion was successful. If the DE pin is not defined, the function returns `false`.

#### Syntax 

```cpp
RS485.assertDE()
```

#### Parameters

None.

#### Returns

* _`bool`_: `true` if the DE pin was asserted, `false` otherwise.

### `deassertDE()`

Deasserts (set to `LOW`) the DE pin if the pin is defined. The function returns `true` if the deassertion was successful. If the DE pin is not defined, the function returns `false`.

#### Syntax 

```cpp
RS485.deassertDE()
```

#### Parameters

None.

#### Returns

* _`bool`_: `true` if the DE pin was deasserted, `false` otherwise.

### `assertRE()`

Asserts (set to `LOW`) the RE pin if the pin is defined. The function returns `true` if the assertion was successful. If the RE pin is not defined, the function returns `false`.

#### Syntax 

```cpp
RS485.assertRE()
```

#### Parameters

None.

#### Returns

* _`bool`_: `true` if the RE pin was asserted, `false` otherwise.

### `deassertRE()`

Deasserts (set to `HIGH`) the RE pin if the pin is defined. The function returns `true` if the deassertion was successful. If the RE pin is not defined, the function returns `false`.

#### Syntax 

```cpp
RS485.deassertRE()
```

#### Parameters

None.

#### Returns

* _`bool`_: `true` if the RE pin was deasserted, `false` otherwise.

