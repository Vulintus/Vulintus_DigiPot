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

#include <Vulintus_DigiPot.h>       // Vulintus digital potentiometer base class.


// I2C addresses
enum MCP40D1x_I2C_Addr : uint8_t {
    MCP40D1x_E_I2C_ADDR = 0x2E,     // Used by most variants.
    MCP40D18_AE_I2C_ADDR = 0x3E,    // Only used by the MCP40D18-xxxAE/LT variants.
};


// CLASS *************************************************************************************************************// 
class Vulintus_MCP40D1x_DigiPot : public Vulintus_DigiPot {

	public:

		// Constructor. //
		Vulintus_MCP40D1x_DigiPot(void);                                        // Default I2C bus, default address.
        Vulintus_MCP40D1x_DigiPot(TwoWire *i2c_bus);                            // Specified I2C bus, default address.
        Vulintus_MCP40D1x_DigiPot(TwoWire *i2c_bus, MCP40D1x_I2C_Addr addr);   // Specified I2C bus, default address.

        // Public variables matching "Vulintus_DigiPot" base class. //
        float wiper_resistance = 75;                            // Wiper resistance, in ohms.
        float max_resistance = 10000;                           // Maximum resistance (not counting wiper), in ohms

        // Public functions matching "Vulintus_DigiPot" base class. //
        uint8_t begin(void); 							            // Initialization.       

		float set_scaled(float float_scaled);				    // Write the Wiper 0 value, scaled 0-1.
		float set_scaled(float float_scaled, uint8_t wiper_i);  // Write the specified wiper value, scaled 0-1.
		float get_scaled(void);                                 // Read the Wiper 0 value, scaled 0-1.
        float get_scaled(uint8_t wiper_i);         		        // Read the specified wiper value, scaled 0-1.

        float set_resistance(float float_ohms) = 0;					    // Write the Wiper 0 value, in real resistance (ohms).
		float set_resistance(float float_ohms, uint8_t wiper_i) = 0;	// Write the specified wiper value, in real resistance (ohms).
		float get_resistance(void);                        			    // Read the Wiper 0 value, in real resistance (ohms).
        float get_resistance(uint8_t wiper_i);         				    // Read the specified wiper value, in real resistance (ohms).

        // Public Functions. //
        uint8_t read(void);             //Read the wiper value.
        uint8_t write(uint8_t value);   //Write the wiper value.

    private:

        // Private Constants. //
        static const uint8_t MCP40D1X_CMD = 0x00;               // Command code for read and write operations.
        static const uint32_t MCP40D1X_I2C_CLKRATE = 400000;    // Clock frequency for I2C communication.
        const uint16_t _n_resistors = 127;                      // Number of resistors in the ladder network.   

        // Private Variables. //
        TwoWire *_wire;                 // I2C interface pointer.
        uint8_t _addr;                  // I2C address.

};

#endif      // #ifndef VULINTUS_MCP40D1X_H