/* 
    Vulintus_MCP40D1x_DigiPot.cpp

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
        2023-12-12 - Drew Sloan - Added support for multiple SPI buses.
*/


#include <Vulintus_MCP40D1x_DigiPot.h>    //Vulintus MCP40D1x digital potentiometer library.     


// CLASS FUNCTIONS ***********************************************************// 


// Class constructor (Default I2C bus, default address).
Vulintus_MCP40D1x_DigiPot::Vulintus_MCP40D1x_DigiPot(void)
{
    _wire = &Wire;                      // Set the I2C bus to the default.
    _addr = ADDR_MCP40D1x_E;            // Set the I2C address.
}


// Class constructor (Specified I2C bus, default address.
Vulintus_MCP40D1x_DigiPot::Vulintus_MCP40D1x_DigiPot(TwoWire *i2c_bus)
        : _wire(i2c_bus)
{
    _addr = ADDR_MCP40D1x_E;            // Set the I2C address.
}


// Class constructor (Specified I2C bus, default address).
Vulintus_MCP40D1x_DigiPot::Vulintus_MCP40D1x_DigiPot(TwoWire *i2c_bus, uint8_t addr)
        : _wire(i2c_bus), _addr(addr)
{

}


// Initialization.
void Vulintus_MCP40D1x_DigiPot::begin(void)
{
    _wire->begin();                     // Initialize the I2C bus.    
}


//Read the wiper value.
uint8_t Vulintus_MCP40D1x_DigiPot::read(void)
{
    uint8_t reply;                          // Reply and success/error code.

    _wire->setClock(MCP40D1X_I2C_CLKRATE);  // Set the I2C clockrate.
    _wire->beginTransmission(_addr); 	    // Start I2C transmission.
    _wire->write(MCP40D1X_CMD);             // Send the read/write command code (0).    
    reply = _wire->endTransmission(); 	    // End the transmission.

    if (reply) {                            // If an error occured.
        return 0xFF;                        // Return a value of 255.
    }

    reply = _wire->requestFrom(_addr, 1);   // Request one byte.
    if (reply) {                            // If at least one byte was returned...
        reply = _wire->read();              // Read the returned byte.
    }
    else {                                  // If no bytes were returned...
        reply = 0xFF;                       // Return a value of 255.
    }

    return reply;                           // Return the reply.
}                         
   


//Write the wiper value.
uint8_t Vulintus_MCP40D1x_DigiPot::write(uint8_t value)
{
    uint8_t nack;                           // NACK success/error code.

    _wire->setClock(MCP40D1X_I2C_CLKRATE);  // Set the I2C clockrate.
    _wire->beginTransmission(_addr); 	    // Start I2C transmission.
    _wire->write(MCP40D1X_CMD);             // Send the read/write command code (0).    
    _wire->write(value);                    // Write the wiper value.
    nack = _wire->endTransmission(); 	    // End the transmission.

    return nack;                            // Return the reply.
}     