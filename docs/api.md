# Arduino RS485 library

## Methods

### `RS485Class()`

Creates a new CSE_ArduinoRS485 object. If you are using a hardware serial port, you can simply send its name as a parameter. If you are using software serial, you must include the SoftwareSerial library first and create a new object of that type. Then send the name of the object as a parameter.

#### Syntax 

```cpp
RS485Class RS485 (serial, dePin, rePin, txPin);
```

#### Parameters

* _serial_: Name of the serial port to use. Can be hardware serial or software serial.
* _dePin_: Drive enable pin.
* _rePin_: Receive enable pin. Optional. Default: -1.
* _txPin_: Serial transmit pin (used to send break signals). Optional. Default: -1.

### `begin()`

Initializes the RS485 object communication speed. The baudrate can be left empty to make it 0. This will prevent the serial port from being initialized by the RS485 library. But then you have to manually initialize the serial port before calling any RS485 library function.

#### Syntax 

```cpp
RS485.begin (baudrate)
```

#### Parameters

* _baudrate_: communication speed in bits per second (baud).

#### Returns

None.

#### See also

* [end()](#end)
* [available()](#available)
* [peek()](#peek)
* [read()](#read)
* [write()](#write)
* [flush()](#flush)
* [beginTransmission()](#begintransmission)
* [endTransmission()](#endtransmission)
* [receive()](#receive)
* [noReceive()](#noreceive)
* [sendBreak()](#sendbreak)
* [sendBreakMicroseconds()](#sendbreakmicroseconds)
* [setPins()](#setpins)

### `end()`

Disables RS485 communication. This will close the serial port and reset the DE and RE pins to INPUT mode.

#### Syntax 

```cpp
RS485.end()
```

#### Parameters

None. 

#### Returns

None.

### `available()`

Get the number of bytes (characters) available for reading from the RS485 port. This is data that already arrived and is stored in the serial receive buffer.

#### Syntax 

```cpp
RS485.available()
```

#### Parameters

None. 

#### Returns

The number of bytes available to read.

### `peek()`

Returns the next byte (character) of the incoming serial data without removing it from the internal serial buffer. That is, successive calls to peek() will return the same character, as will the next call to read().

#### Syntax 

```cpp
RS485.peek()
```

#### Parameters

None. 

#### Returns

The first byte of incoming serial data available or -1 if no data is available. 

### `read()`

Reads incoming serial data.

#### Syntax 

```cpp
RS485.read()
```

#### Parameters

None. 

#### Returns

The first byte of incoming serial data available or -1 if no data is available. 

### `write()`

Writes binary data to the serial port. This data is sent as a byte or series of bytes.

#### Syntax 

```cpp
RS485.write (uint8_t b)
```

#### Parameters

* _b_: unsigned char.

#### Returns

The number of bytes written.

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

Enables RS-485 transmission. This will assert the DE pin and the RE pin is not modified (since DE has priority over RE).

#### Syntax 

```cpp
RS485.beginTransmission()
```

#### Parameters

None.

#### Returns

None.

### `endTransmission()`

Disables RS-485 transmission. This deasserts the DE pin and the RE pin is not modified (since DE has priority over RE).

#### Syntax 

```cpp
RS485.endTransmission()
```

#### Parameters

None.

#### Returns

None.

### `receive()`

Enables reception. This asserts the RE pin. The state of the DE pins should be set to LOW before calling this function.

#### Syntax 

```cpp
RS485.receive()
```

#### Parameters

None.

#### Returns

None.

### `noReceive()`

Disables reception. This deasserts the RE pin. If the DE pin is also deasserted (LOW), then the transceiver enters a high-impedance state.

#### Syntax 

```cpp
RS485.noReceive()
```

#### Parameters

None.

#### Returns

None.

### `sendBreak()`

Sends a serial break signal for the specified duration in milliseconds. This function will only work if the TX pin is specified in the constructor. The serial port will be reinitialized only if the baudrate is greater than 0.

#### Syntax 

```cpp
RS485.sendBreak (unsigned int duration)
```

#### Parameters

* _duration_: Duration of the break signal in milliseconds.

#### Returns

None.

### `sendBreakMicroseconds()`

Sends a serial break signal for the specified duration in microseconds. This function will only work if the TX pin is specified in the constructor. The serial port will be reinitialized only if the baudrate is greater than 0.

#### Syntax 

```cpp
RS485.sendBreak (unsigned int duration)
```

#### Parameters

* _duration_: Duration of the break signal in microseconds.

#### Returns

None.

### `setPins()`

Modify the pins used to communicate with the RS-485 transceiver.

#### Syntax 

```cpp
RS485.setPins (int dePin, int rePin, int txPin)
```

#### Parameters

* _dePin_: drive output enable pin.
* _rePin_: receiver output enable pin.
* _txPin_: transmission pin (used to send break signals).

#### Returns

None.
