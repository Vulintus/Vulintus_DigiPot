/* 
    Vulintus_MCP4xxx_129_DigiPot.cpp

    Copyright 2023, Vulintus, Inc.
    
    Arduino-compatible library for the Microchip MCP413X/412X series single 
    digital potentiometers/rheostats using the SPI interface.

    Licensed under the Apache License, Version 2.0 (the "License"); you may not 
    use this file except in compliance with the License.

    You may obtain a copy of the License at

    http:// www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS, WITHOUT 
    WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the 
    License for the specific language governing permissions and limitations 
    under the License.

    UPDATE LOG:
        2023-08-22 - Drew Sloan - Library first created.
        2024-07-08 - Drew Sloan - Forked "...MCP4xxx..." class into 
                                         "...MCP41xx_129...", 
                                         "...MCP41xx_257...", 
                                         "...MCP42xx_129...", and 
                                         "...MCP42xx_257..." variants.
*/


#include <Vulintus_MCP4xxx_129_DigiPot.h>    // Vulintus MCP4xxx digital potentiometer library.     


// CLASS FUNCTIONS ***********************************************************// 

// Class constructor (default SPI with chip select).
Vulintus_MCP4xxx_129_DigiPot::Vulintus_MCP4xxx_129_DigiPot(uint8_t pin_cs)
    : _pin_cs(pin_cs)
{
    _spi_bus = &SPI;                    // Set the SPI bus to the default bus.
}


// Class constructor (specified SPI with chip select).
Vulintus_MCP4xxx_129_DigiPot::Vulintus_MCP4xxx_129_DigiPot(SPIClass *spi_bus, uint8_t pin_cs)
    : _pin_cs(pin_cs)
{
    _spi_bus = spi_bus;                 // Set the SPI bus to the specified bus.
}


// Initialization.
void Vulintus_MCP4xxx_129_DigiPot::begin(void)
{
    _spi_bus->begin();                  // Initialize the SPI bus.
    pinMode(_pin_cs, OUTPUT);           // Set the CS pin mode to output.
    digitalWrite(_pin_cs, HIGH);        // Set the CS pin high.
}


// Write the Wiper 0 value, scaled 0-1 (Vulintus_DigiPot base class function).
void Vulintus_MCP4xxx_129_DigiPot::write_float(float float_val)
{
    write_float(float_val, (uint8_t) 0);        // Write the value to wiper 0.
}

// Write the specified wiper value, scaled 0-1 (Vulintus_DigiPot base class function).
void Vulintus_MCP4xxx_129_DigiPot::write_float(float float_val, uint8_t wiper_i)
{
    float_val *= (float) _n_steps;      // Calculate the fractional number of steps.
    uint16_t uint_val = float_val;      // Convert the float to a uint16.
    write(uint_val, wiper_i);           // Write the value to the specified wiper.
}


// Read the Wiper 0 value, scaled 0-1 (Vulintus_DigiPot base class function).
float Vulintus_MCP4xxx_129_DigiPot::read_float(void)
{
    float float_val = read_float((uint8_t) 0);      // Read the value from wiper 0.    
    return float_val;                               // Return the float value.
}                        


// Read the specified wiper value, scaled 0-1 (Vulintus_DigiPot base class function).
float Vulintus_MCP4xxx_129_DigiPot::read_float(uint8_t wiper_i)
{
    float float_val = read((uint8_t) 0);    // Read the value from wiper 0.
    float_val /= (float) _n_steps;          // Convert the step setting to fractional 0-1.
    return float_val;                       // Read the value from wiper 0.
}      		    


// Read the Wiper 0 value.
uint16_t Vulintus_MCP4xxx_129_DigiPot::read(void)
{
    return read((uint8_t) 0);           // Read the value from wiper 0.
}                         


// Read the specified wiper value.
uint16_t Vulintus_MCP4xxx_129_DigiPot::read(uint8_t wiper_i)
{
    if (!wiper_i) {
        return send_cmd(MCP4XXX_REG_WIPER0, MCP4XXX_CMD_READ, (uint16_t) 255);
    }
    else {
        return send_cmd(MCP4XXX_REG_WIPER1, MCP4XXX_CMD_READ, (uint16_t) 255);
    }
}          


// Write the Wiper 0 value.
void Vulintus_MCP4xxx_129_DigiPot::write(uint16_t value)
{
    write(value, (uint8_t) 0);          // Write the value to wiper 0.
}     


// Write the specified wiper value.
void Vulintus_MCP4xxx_129_DigiPot::write(uint16_t value, uint8_t wiper_i)
{
    if (!wiper_i) {
        send_cmd(MCP4XXX_REG_WIPER0, MCP4XXX_CMD_WRITE, value);
    }
    else {
        send_cmd(MCP4XXX_REG_WIPER1, MCP4XXX_CMD_WRITE, value);
    }
}   


// Increment Wiper 0.MCP4XXX
void Vulintus_MCP4xxx_129_DigiPot::increment()
{
    increment((uint8_t) 0);             // Increment wiper 0.
}           


// Increment the specified wiper.
void Vulintus_MCP4xxx_129_DigiPot::increment(uint8_t wiper_i)
{
    if (!wiper_i) {
        send_cmd(MCP4XXX_REG_WIPER0, MCP4XXX_CMD_INCR);
    }
    else {
        send_cmd(MCP4XXX_REG_WIPER1, MCP4XXX_CMD_INCR);
    }
}            


// Increment Wiper 1.
void Vulintus_MCP4xxx_129_DigiPot::decrement()
{
    decrement((uint8_t) 0);             // Decrement wiper 0.
}                         


// Increment the specified wiper.
void Vulintus_MCP4xxx_129_DigiPot::decrement(uint8_t wiper_i)
{
    if (!wiper_i) {
        send_cmd(MCP4XXX_REG_WIPER0, MCP4XXX_CMD_DECR);
    }
    else {
        send_cmd(MCP4XXX_REG_WIPER1, MCP4XXX_CMD_DECR);
    }
}           


// Send a command with data.
uint16_t Vulintus_MCP4xxx_129_DigiPot::send_cmd(uint8_t addr, uint8_t cmd, uint16_t data)
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
void Vulintus_MCP4xxx_129_DigiPot::send_cmd(uint8_t addr, uint8_t cmd)
{
    uint8_t hi_byte = addr | cmd;           // Combine the address, command and MSB to make the high byte.

    _spi_bus->beginTransaction(SPISettings(250000, MSBFIRST, SPI_MODE0));   // Set the SPI settings for this chip.
    digitalWrite(_pin_cs, LOW);                                             // Set the chip select line low.    
    _spi_bus->transfer(hi_byte);                                            // Send the high byte.
    digitalWrite(_pin_cs, HIGH);                                            // Set the chip select line high. 
    _spi_bus->endTransaction();                                             // Release the SPI bus.
}                