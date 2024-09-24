/* 

    Vulintus_AD5273_DigiPot.h

    Copyright 2023, Vulintus, Inc.
    
    Arduino-compatible library for the Microchip AD5273 series single digital
    potentiometers/rheostats, including:
        - MCP4131 -> Single rheostat, I2C, RAM memory, 7-bit
        - MCP4132 -> Single potentiometer, I2C, RAM memory, 7-bit
        - MCP4141 -> Single rheostat, I2C, RAM memory, 7-bit

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
        2024-07-17 - Drew Sloan - Converted to a base MCP4xxx class with 
                                  inheriting classs for the 128 and 256 step 
                                  variants.

*/


#ifndef VULINTUS_AD5273_DIGIPOT_H
#define VULINTUS_AD5273_DIGIPOT_H


//Included libraries.//
#include <Arduino.h>            // Arduino main header.
#include <Wire.h>               // Arduino I2C library.

#include <Vulintus_DigiPot.h>   // Vulintus digital potentiometer base class.


// DEFINITIONS *******************************************************************************************************//
enum AD5273_I2C_addr : uint8_t {
    AD5273I2C_ADDR_L = 0b1011000,   // 0x58, AD0 pin is low.
    AD5273I2C_ADDR_H = 0b1011001,   // 0x59, AD0 pin is high.
};


// CLASSES ***********************************************************************************************************// 
class Vulintus_AD5273_DigiPot : public Vulintus_DigiPot {

	public:

		// Constructor. //
        Vulintus_AD5273_DigiPot(AD5273_I2C_addr addr = AD5273I2C_ADDR_L, \
                TwoWire *i2c_bus = &Wire);

        // Public variables matching "Vulintus_DigiPot" base class. //
        float wiper_resistance = 60;            // Wiper resistance, in ohms.
        float max_resistance = 10000;           // Maximum resistance (not counting wiper), in ohms

        // Public functions matching "Vulintus_DigiPot" base class. //
        uint8_t begin(void); 		            // Initialization.          

		float set_scaled(float float_scaled);			        // Write the Wiper 0 value, scaled 0-1.
		float set_scaled(float float_scaled, uint8_t wiper_i);  // Write the specified wiper value, scaled 0-1.
		float get_scaled(void);                                 // Read the Wiper 0 value, scaled 0-1.
        float get_scaled(uint8_t wiper_i);         		        // Read the specified wiper value, scaled 0-1.

        float set_resistance(float float_ohms);					    // Write the Wiper 0 value, in real resistance (ohms).
		float set_resistance(float float_ohms, uint8_t wiper_i);    // Write the specified wiper value, in real resistance (ohms).
		float get_resistance(void);                        		    // Read the Wiper 0 value, in real resistance (ohms).
        float get_resistance(uint8_t wiper_i);         			    // Read the specified wiper value, in real resistance (ohms).

        // Public Functions. //
        uint8_t read(void);                     //Read the wiper value.
        uint8_t write(uint8_t value);           //Write the wiper value.

    private:

        // Private Constants. //
        static const uint8_t AD5273_CMD = 0x00;             // Command code for read and write operations.
        static const uint32_t AD5273_I2C_CLKRATE = 400000;  // Clock frequency for I2C communication.
        const uint16_t _n_resistors = 63;                   // Number of resistors in the ladder network.   

        // Private Variables. //
        TwoWire *_i2c_bus;              // I2C interface pointer.
        uint8_t _i2c_addr;              // I2C address.

};

#endif      // #ifndef VULINTUS_AD5273_DIGIPOT_H