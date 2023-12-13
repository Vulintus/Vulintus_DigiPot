/*
    Vulintus_MCP4xxx_DigPot.cpp

    Copyright 2023, Vulintus, Inc.
    
    Arduino-compatible library for the Microchip MCP413X/415X/423X/425X series 
    single/dual digital potentiometers/rheostats using the SPI interface.

    Licensed under the Apache License, Version 2.0 (the "License"); you may not 
    use this file except in compliance with the License.

    You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS, WITHOUT 
    WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the 
    License for the specific language governing permissions and limitations 
    under the License.

    UPDATE LOG:
        2023-08-22 - Drew Sloan - Library first created.
*/


#include <Vulintus_MCP4xxx_DigPot.h>    // Vulintus MCP4xxx digital potentiometer library.     


// CLASS FUNCTIONS ***********************************************************// 

// Class constructor (default SPI with chip select).
Vulintus_MCP4xxx_DigPot::Vulintus_MCP4xxx_DigPot(uint8_t pin_cs)
    : _pin_cs(pin_cs)
{
    _spi_bus = &SPI;                    // Set the SPI bus to the default bus.
}


// Class constructor (specified SPI with chip select).
Vulintus_MCP4xxx_DigPot::Vulintus_MCP4xxx_DigPot(SPIClass *spi_bus, uint8_t pin_cs)
    : _pin_cs(pin_cs)
{
    _spi_bus = spi_bus;                 // Set the SPI bus to the specified bus.
}


// Initialization.
void Vulintus_MCP4xxx_DigPot::begin(void)
{
    _spi_bus->begin();                  // Initialize the SPI bus.
    pinMode(_pin_cs, OUTPUT);           // Set the CS pin mode to output.
    digitalWrite(_pin_cs, HIGH);        // Set the CS pin high.
}


// Read the Wiper 0 value.
uint16_t Vulintus_MCP4xxx_DigPot::read()
{
    return read((uint8_t) 0);           // Read the value from wiper 0.
}                         


// Read the specified wiper value.
uint16_t Vulintus_MCP4xxx_DigPot::read(uint8_t wiper_i)
{
    if (!wiper_i) {
        return send_cmd(MCP4XXX_REG_WIPER0, MCP4XXX_CMD_READ, (uint16_t) 255);
    }
    else {
        return send_cmd(MCP4XXX_REG_WIPER1, MCP4XXX_CMD_READ, (uint16_t) 255);
    }
}          


// Write the Wiper 0 value.
void Vulintus_MCP4xxx_DigPot::write(uint16_t value)
{
    write(value, (uint8_t) 0);          // Write the value to wiper 0.
}     


// Write the specified wiper value.
void Vulintus_MCP4xxx_DigPot::write(uint16_t value, uint8_t wiper_i)
{
    if (!wiper_i) {
        send_cmd(MCP4XXX_REG_WIPER0, MCP4XXX_CMD_WRITE, value);
    }
    else {
        send_cmd(MCP4XXX_REG_WIPER1, MCP4XXX_CMD_WRITE, value);
    }
}   


// Increment Wiper 0.MCP4XXX
void Vulintus_MCP4xxx_DigPot::increment()
{
    increment((uint8_t) 0);             // Increment wiper 0.
}           


// Increment the specified wiper.
void Vulintus_MCP4xxx_DigPot::increment(uint8_t wiper_i)
{
    if (!wiper_i) {
        send_cmd(MCP4XXX_REG_WIPER0, MCP4XXX_CMD_INCR);
    }
    else {
        send_cmd(MCP4XXX_REG_WIPER1, MCP4XXX_CMD_INCR);
    }
}            


// Increment Wiper 1.
void Vulintus_MCP4xxx_DigPot::decrement()
{
    decrement((uint8_t) 0);             // Decrement wiper 0.
}                         


// Increment the specified wiper.
void Vulintus_MCP4xxx_DigPot::decrement(uint8_t wiper_i)
{
    if (!wiper_i) {
        send_cmd(MCP4XXX_REG_WIPER0, MCP4XXX_CMD_DECR);
    }
    else {
        send_cmd(MCP4XXX_REG_WIPER1, MCP4XXX_CMD_DECR);
    }
}           


// Send a command with data.
uint16_t Vulintus_MCP4xxx_DigPot::send_cmd(uint8_t addr, uint8_t cmd, uint16_t data)
{
    uint8_t hi_byte = addr | cmd | (data >> 8);     // Combine the address, command and MSB to make the high byte.
    uint8_t lo_byte = data;                         // Grab the bottom 8 bits from the data for the low byte.

    _spi_bus->beginTransaction(SPISettings(250000, MSBFIRST, SPI_MODE0));   // Set the SPI settings for this chip.
    digitalWrite(_pin_cs, LOW);                                             // Set the chip select line low.    
    hi_byte = _spi_bus->transfer(hi_byte);                                  // Send the high byte.
    lo_byte = _spi_bus->transfer(lo_byte);                                  // Send the low byte.
    digitalWrite(_pin_cs, HIGH);                                            // Set the chip select line high. 
    _spi_bus->endTransaction();                                             // Release the SPI bus.

    uint16_t reply = (uint16_t) (hi_byte << 8) + lo_byte;   // Combine the high and low bytes.
    reply &= 0x01FF;                                        // Kick out all but the bottom 9 bits.

    return reply;                                           // Return the result.
}


// Send a command without data (increment, decrement).
void Vulintus_MCP4xxx_DigPot::send_cmd(uint8_t addr, uint8_t cmd)
{
    uint8_t hi_byte = addr | cmd;           // Combine the address, command and MSB to make the high byte.

    _spi_bus->beginTransaction(SPISettings(250000, MSBFIRST, SPI_MODE0));   // Set the SPI settings for this chip.
    digitalWrite(_pin_cs, LOW);                                             // Set the chip select line low.    
    _spi_bus->transfer(hi_byte);                                            // Send the high byte.
    digitalWrite(_pin_cs, HIGH);                                            // Set the chip select line high. 
    _spi_bus->endTransaction();                                             // Release the SPI bus.
}                