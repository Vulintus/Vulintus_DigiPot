/* 

    Vulintus_MCP4xxx_DigiPot.h

    Copyright 2023, Vulintus, Inc.
    
    Arduino-compatible library for the Microchip MCP4xxx series single and 
    MCP42xx series dual digital potentiometers/rheostats, including:
        - MCP4131 -> Single potentiometer, SPI, RAM memory, 7-bit
        - MCP4132 -> Single rheostat, SPI, RAM memory, 7-bit
        - MCP4141 -> Single potentiometer, SPI, EE memory, 7-bit
        - MCP4142 -> Single rheostat, SPI, EE memory, 7-bit
        - MCP4151 -> Single potentiometer, SPI, RAM memory, 8-bit
        - MCP4152 -> Single rheostat, SPI, RAM memory, 8-bit
        - MCP4161 -> Single potentiometer, SPI, EE memory, 8-bit
        - MCP4162 -> Single rheostat, SPI, EE memory, 8-bit
        - MCP4231 -> Dual potentiometer, SPI, RAM memory, 7-bit
        - MCP4232 -> Dual rheostat, SPI, RAM memory, 7-bit
        - MCP4241 -> Dual potentiometer, SPI, EE memory, 7-bit
        - MCP4242 -> Dual rheostat, SPI, EE memory, 7-bit
        - MCP4251 -> Dual potentiometer, SPI, RAM memory, 8-bit
        - MCP4252 -> Dual rheostat, SPI, RAM memory, 8-bit
        - MCP4261 -> Dual potentiometer, SPI, EE memory, 8-bit
        - MCP4262 -> Dual rheostat, SPI, E memory, 8-bit

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
        2024-07-16 - Drew Sloan - Converted to a base MCP4xxx class with 
                                  inheriting classs for the 128 and 256 step 
                                  variants.
                                        
*/


#include <Microchip_MCP4xxx/Vulintus_MCP4xxx_DigiPot.h>     // Library header. 


// CLASS FUNCTIONS ***********************************************************// 

// Class constructor (SPI with chip select).
Vulintus_MCP4xxx_DigiPot::Vulintus_MCP4xxx_DigiPot(uint16_t n_resistors, uint8_t pin_cs, SPIClass *spi_bus)
    : _n_resistors(n_resistors), _pin_cs(pin_cs)
{
    _spi_bus = &SPI;                    // Set the SPI bus to the default bus.
}


// Class constructor (I2C with address).
Vulintus_MCP4xxx_DigiPot::Vulintus_MCP4xxx_DigiPot(uint16_t n_resistors, TwoWire *i2c_bus, \
        MCP4xxx_I2C_addr i2c_addr)
    : _n_resistors(n_resistors), _i2c_addr(i2c_addr)
{
    _i2c_bus = i2c_bus;                 // Set the I2C bus to the specified bus.
}


// Initialization.
uint8_t Vulintus_MCP4xxx_DigiPot::begin(void)
{
    uint8_t error = 0;                          // Assume no connection error.
    if (_spi_bus == NULL) {                     // I2C mode (SPI pointer is NULL).
        _i2c_bus->begin();                      // Initialize the I2C bus.
        _i2c_bus->beginTransmission(_i2c_addr); // Start an I2C transmission to the chip.
        error = _i2c_bus->endTransmission();    // Check for an ACK from the chip.
    }
    else {                                      // SPI mode.
        _spi_bus->begin();                      // Initialize the SPI bus.
        pinMode(_pin_cs, OUTPUT);               // Set the CS pin mode to output.
        digitalWrite(_pin_cs, HIGH);            // Set the CS pin high.
    }    
    return error;                               // Return the error value.
}


// Write the Wiper 0 value, scaled 0-1 (Vulintus_DigiPot base class function).
float Vulintus_MCP4xxx_DigiPot::set_scaled(float float_scaled)
{
    float_scaled = set_scaled(float_scaled, (uint8_t) 0);   // Write the value to wiper 0.
    return float_scaled;                                   // Return the actual scaled value.
}


// Write the specified wiper value, scaled 0-1 (Vulintus_DigiPot base class function).
float Vulintus_MCP4xxx_DigiPot::set_scaled(float float_scaled, uint8_t wiper_i)
{
    float_scaled *= (float) _n_resistors;   // Calculate the fractional number of steps.
    uint16_t uint_val = float_scaled;       // Convert the float to a uint16.
    write(uint_val, wiper_i);               // Write the value to the specified wiper.
    float_scaled = get_scaled(wiper_i);     // Read the actual scaled value.
    return float_scaled;                    // Return the actual scaled value.
}


// Read the Wiper 0 value, scaled 0-1 (Vulintus_DigiPot base class function).
float Vulintus_MCP4xxx_DigiPot::get_scaled(void)
{
    float float_scaled = get_scaled((uint8_t) 0);   // Read the value from wiper 0.    
    return float_scaled;                            // Return the float value.
}                        


// Read the specified wiper value, scaled 0-1 (Vulintus_DigiPot base class function).
float Vulintus_MCP4xxx_DigiPot::get_scaled(uint8_t wiper_i)
{
    float float_scaled = read((uint8_t) wiper_i);           // Read the value from the specified wiper.    
    float_scaled /= (float) _n_resistors;                   // Convert the step setting to fractional 0-1.
    float_scaled *= max_resistance;                         // Convert the scaled value to resistance (ohms).
    float_scaled += wiper_resistance;                       // Add the wiper resistance.
    float_scaled /= (wiper_resistance + max_resistance);    // Divide by the wiper resistance and max resistance to get the actual scaled value.
    return float_scaled;                                    // Read the value from wiper 0.
}      		    


// Write the Wiper 0 value, in real resistance (ohms).
float Vulintus_MCP4xxx_DigiPot::set_resistance(float float_ohms)
{
    float_ohms = set_resistance(float_ohms, (uint8_t) 0);   // Set the resistance (ohms) on wiper 0.
    return float_ohms;                                      // Return the float value.
}					


// Write the specified wiper value, in real resistance (ohms).
float Vulintus_MCP4xxx_DigiPot::set_resistance(float float_ohms, uint8_t wiper_i)
{
    if (float_ohms > wiper_resistance) {             // If the specified resistance is greater than the wiper resistance...
        float_ohms -= wiper_resistance;              // Subtract the wiper resistance.
        float_ohms /= max_resistance;                // Convert the resistance value to scaled, 0-1.
    }
    else {                                          // Otherwise, if the specified resistance is less than the wiper resistance...
        float_ohms = 0;                             // Set the scaled value to zero.
    }    
    float_ohms = set_scaled(float_ohms, wiper_i);   // Set the scaled setting.
    float_ohms *= max_resistance;                   // Convert the scaled value to resistance (ohms).
    float_ohms += wiper_resistance;                 // Add the wiper resistance.
    return float_ohms;                              // Return the float value.
}	


// Read the Wiper 0 value, in real resistance (ohms).
float Vulintus_MCP4xxx_DigiPot::get_resistance(void)
{
    float float_ohms = get_resistance((uint8_t) 0);     // Fetch the resistance from wiper 0.
}    			


// Read the specified wiper value, in real resistance (ohms).
float Vulintus_MCP4xxx_DigiPot::get_resistance(uint8_t wiper_i)
{
    float float_ohms = get_scaled(wiper_i);             // Read the scaled value of the wiper, 0-1.
    float_ohms *= (max_resistance + wiper_resistance);  // Convert the scaled value to resistance (ohms).
    return float_ohms;                                  // Return the float value.
}		


// Read the Wiper 0 value.
uint16_t Vulintus_MCP4xxx_DigiPot::read(void)
{
    return read((uint8_t) 0);   // Read the value from wiper 0.
}                         


// Read the specified wiper value.
uint16_t Vulintus_MCP4xxx_DigiPot::read(uint8_t wiper_i)
{
    if (!wiper_i) {
        return send_cmd(MCP4XXX_REG_WIPER0, MCP4XXX_CMD_READ, (uint16_t) 0x01FF);
    }
    else {
        return send_cmd(MCP4XXX_REG_WIPER1, MCP4XXX_CMD_READ, (uint16_t) 0x01FF);
    }
}          


// Write the Wiper 0 value.
void Vulintus_MCP4xxx_DigiPot::write(uint16_t value)
{
    write(value, (uint8_t) 0);          // Write the value to wiper 0.
}     


// Write the specified wiper value.
void Vulintus_MCP4xxx_DigiPot::write(uint16_t value, uint8_t wiper_i)
{
    if (!wiper_i) {
        send_cmd(MCP4XXX_REG_WIPER0, MCP4XXX_CMD_WRITE, value);
    }
    else {
        send_cmd(MCP4XXX_REG_WIPER1, MCP4XXX_CMD_WRITE, value);
    }
}   


// Increment Wiper 0.MCP4XXX
void Vulintus_MCP4xxx_DigiPot::increment()
{
    increment((uint8_t) 0);             // Increment wiper 0.
}           


// Increment the specified wiper.
void Vulintus_MCP4xxx_DigiPot::increment(uint8_t wiper_i)
{
    if (!wiper_i) {
        send_cmd(MCP4XXX_REG_WIPER0, MCP4XXX_CMD_INCR);
    }
    else {
        send_cmd(MCP4XXX_REG_WIPER1, MCP4XXX_CMD_INCR);
    }
}            


// Decrement Wiper 1.
void Vulintus_MCP4xxx_DigiPot::decrement()
{
    decrement((uint8_t) 0);             // Decrement wiper 0.
}                         


// Decrement the specified wiper.
void Vulintus_MCP4xxx_DigiPot::decrement(uint8_t wiper_i)
{
    if (!wiper_i) {
        send_cmd(MCP4XXX_REG_WIPER0, MCP4XXX_CMD_DECR);
    }
    else {
        send_cmd(MCP4XXX_REG_WIPER1, MCP4XXX_CMD_DECR);
    }
}           


// Send a command with data.
uint16_t Vulintus_MCP4xxx_DigiPot::send_cmd(uint8_t addr, uint8_t cmd, uint16_t data)
{
    uint8_t hi_byte = addr | cmd | (data >> 8);     // Combine the address, command and MSB to make the high byte.
    uint8_t lo_byte = data;                         // Grab the bottom 8 bits from the data for the low byte.
    uint16_t reply;                                 // Transmission success indicator,

    if (_spi_bus == NULL) {                         // I2C mode (SPI pointer is NULL).
        _i2c_bus->setClock(MCP4XXX_I2C_CLKRATE);    // Set the I2C clockrate.
        _i2c_bus->beginTransmission(_i2c_addr);     // Start I2C transmission.
        _i2c_bus->write(hi_byte);                   // Send the high byte.
        if (cmd == MCP4XXX_CMD_READ) {              // If we're reading the register...
            reply = _i2c_bus->endTransmission();    // End the transmission.
            if (reply) {                            // If an error occured.
                return 0xFFFF;                      // Return a value of 65535.
            }
            reply = _i2c_bus->requestFrom(_i2c_addr,(uint8_t) 2);   // Request two bytes.
            if (reply < 2) {                        // If two bytes weren't returned...
                while (_i2c_bus->available()) {     // Loop until the I2C buffer is cleared.
                    _i2c_bus->read();               // Read and discard each byte.
                }
                return 0xFFFF;                      // Return a value of 65535.
            }
            hi_byte = _i2c_bus->read();             // Read the high byte.
            lo_byte = _i2c_bus->read();             // Read the low byte.
        }
        else {                                      // Otherwise, if we're writing the register...
            _i2c_bus->write(lo_byte);               // Send the low byte.
            lo_byte = _i2c_bus->endTransmission();  // End the transmission.
            hi_byte = 0x00;                         // Clear the high byte.
        }
    }
    else {                                          // SPI mode.    
        _spi_bus->beginTransaction(SPISettings(MCP4XXX_SPI_CLKRATE, MSBFIRST, SPI_MODE0));   // Set the SPI settings for this chip.
        digitalWrite(_pin_cs, LOW);                 // Set the chip select line low.    
        hi_byte = _spi_bus->transfer(hi_byte);      // Send the high byte.
        lo_byte = _spi_bus->transfer(lo_byte);      // Send the low byte.
        digitalWrite(_pin_cs, HIGH);                // Set the chip select line high. 
        _spi_bus->endTransaction();                 // Release the SPI bus.        
    }

    reply = (uint16_t) (hi_byte << 8) + lo_byte;    // Combine the high and low bytes.
    reply &= 0x01FF;                                // Kick out all but the bottom 9 bits.
    return reply;                                   // Return the result.
}


// Send a command without data (increment, decrement).
void Vulintus_MCP4xxx_DigiPot::send_cmd(uint8_t addr, uint8_t cmd)
{
    uint8_t hi_byte = addr | cmd;           // Combine the address, command and MSB to make the high byte.

    if (_spi_bus == NULL) {                             // I2C mode (SPI pointer is NULL).
        _i2c_bus->setClock(MCP4XXX_I2C_CLKRATE);        // Set the I2C clockrate.
        _i2c_bus->beginTransmission(_i2c_addr); 	        // Start I2C transmission.
        _i2c_bus->write(hi_byte);                       // Send the high byte.
        _i2c_bus->endTransmission(); 	                // End the transmission.
    }
    else {                                              // SPI mode.    
        _spi_bus->beginTransaction(SPISettings(MCP4XXX_SPI_CLKRATE, MSBFIRST, SPI_MODE0));   // Set the SPI settings for this chip.
        digitalWrite(_pin_cs, LOW);                     // Set the chip select line low.    
        _spi_bus->transfer(hi_byte);                    // Send the high byte.
        digitalWrite(_pin_cs, HIGH);                    // Set the chip select line high. 
        _spi_bus->endTransaction();                     // Release the SPI bus.
    }
}                