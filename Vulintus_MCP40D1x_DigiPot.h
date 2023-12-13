/* 
    Vulintus_MCP40D1x_DigiPot.h

    Copyright 2023, Vulintus, Inc.
    
    Arduino-compatible library for the Microchip MCP40D17/18/19 series digital
    potentiometers/rheostats using an I2C interface.

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
        2023-12-12 - Drew Sloan - Library first created.
*/


#ifndef VULINTUS_MCP40D1X_H
#define VULINTUS_MCP40D1X_H


//Included libraries.//
#include <Arduino.h>            // Arduino main header.
#include <Wire.h>               // Arduino I2C library.


// CLASS *************************************************************************************************************// 
class Vulintus_MCP40D1x_DigiPot {

	public:

        // I2C addresses
        enum MCP40D1x_I2C_Addrs : uint8_t {
            ADDR_MCP40D1x_E = 0x2E,     // Used by most variants.
            ADDR_MCP40D18_AE = 0x3E,    // Only used by the MCP40D18-xxxAE/LT variants.
        };

		// Constructor. //
		Vulintus_MCP40D1x_DigiPot(void);                            // Default I2C bus, default address.
        Vulintus_MCP40D1x_DigiPot(TwoWire *i2c_bus);                // Specified I2C bus, default address.
        Vulintus_MCP40D1x_DigiPot(TwoWire *i2c_bus, uint8_t addr);  // Specified I2C bus, default address.

        // Functions. //
        void begin(void); 			    //Initialization.
        uint8_t read(void);             //Read the wiper value.
        uint8_t write(uint8_t value);   //Write the wiper value.

    private:

        // Constants. //
        static const uint8_t MCP40D1X_CMD = 0x00;               //Command code for read and write operations.
        static const uint32_t MCP40D1X_I2C_CLKRATE = 400000;    // Clock frequency for I2C communication

        // Variables. //
        TwoWire *_wire;                 // I2C interface pointer.
        uint8_t _addr;                  // I2C address.

};

#endif      // #ifndef VULINTUS_MCP40D1X_H