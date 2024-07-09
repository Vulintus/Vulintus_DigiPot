/* 
    Vulintus_MCP4xxx_129_DigiPot.h

    Copyright 2023, Vulintus, Inc.
    
    Arduino-compatible library for the Microchip MCP413X/414X/423x/424x series
    single/dual digital potentiometers/rheostats using the SPI interface.

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
                                         "...MCP4xxx_129..." and 
                                         "...MCP4xxx_257..." variants.
*/


#ifndef VULINTUS_MCP4XXX_129_DIGIPOT_H
#define VULINTUS_MCP4XXX_129_DIGIPOT_H


// Included libraries.// 
#include <Arduino.h>                // Arduino main header.
#include <SPI.h>		            // Standard Arduino SPI library.

#include <Vulintus_DigiPot.h>       // Vulintus digital potentiometer base class.


// CLASS *************************************************************************************************************// 
class Vulintus_MCP4xxx_129_DigiPot : public Vulintus_DigiPot {

	public:

		// Constructors. // 
		Vulintus_MCP4xxx_129_DigiPot(uint8_t pin_cs);                        // Default SPI with chip select.
        Vulintus_MCP4xxx_129_DigiPot(SPIClass *spi_bus, uint8_t pin_cs);     // Specified SPI with chip select.

        // Public functions matching "Vulintus_DigiPot" base class.
        void begin(void); 							            // Initialization.        
		void write_float(float float_val);				        // Write the Wiper 0 value, scaled 0-1.
		void write_float(float float_val, uint8_t wiper_i);     // Write the specified wiper value, scaled 0-1.
		float read_float(void);                                 // Read the Wiper 0 value, scaled 0-1.
        float read_float(uint8_t wiper_i);         		        // Read the specified wiper value, scaled 0-1.

        // Public functions. //
        uint16_t read();                                        // Read the Wiper 0 value.
        uint16_t read(uint8_t wiper_i);                         // Read the specified wiper value.
        void write(uint16_t value);                             // Write the Wiper 0 value.
        void write(uint16_t value, uint8_t wiper_i);            // Write the specified wiper value.MCP4XXX
        void increment();                                       // Increment Wiper 0.
        void increment(uint8_t wiper_i);                        // Increment the specified wiper.
        void decrement();                                       // Increment Wiper 1.
        void decrement(uint8_t wiper_i);                        // Increment the specified wiper.        

    private:

        // Private constants. // 
        static const uint8_t MCP4XXX_REG_WIPER0  = 0x00;            // Volatile Wiper 0.
        static const uint8_t MCP4XXX_REG_WIPER1  = 0x10;            // Volatile Wiper 1.
        static const uint8_t MCP4XXX_REG_TCON    = 0x40;            // Volatile TCON Register.
        static const uint8_t MCP4XXX_REG_STATUS  = 0x50;            // Status Register.

        static const uint8_t MCP4XXX_STATUS_SHDN = 0x02;            // Hardware Shutdown pin Status bit.

        static const uint8_t MCP4XXX_TCON_R0HW   = 0x08;            // Resistor 0 Hardware Configuration Control bit.
        static const uint8_t MCP4XXX_TCON_R0A    = 0x04;            // Resistor 0 Terminal A (P0A pin) Connect Control bit .
        static const uint8_t MCP4XXX_TCON_R0W    = 0x02;            // Resistor 0 Wiper (P0W pin) Connect Control bit.
        static const uint8_t MCP4XXX_TCON_R0B    = 0x01;            // Resistor 0 Terminal B (P0B pin) Connect Control bit.
        static const uint8_t MCP4XXX_TCON_R1HW   = 0x80;            // Resistor 1 Hardware Configuration Control bit.
        static const uint8_t MCP4XXX_TCON_R1A    = 0x40;            // Resistor 1 Terminal A (P1A pin) Connect Control bit .
        static const uint8_t MCP4XXX_TCON_R1W    = 0x20;            // Resistor 1 Wiper (P1W pin) Connect Control bit.
        static const uint8_t MCP4XXX_TCON_R1B    = 0x10;            // Resistor 1 Terminal B (P1B pin) Connect Control bit.

        static const uint8_t MCP4XXX_CMD_WRITE   = 0x00;            // Write data command.
        static const uint8_t MCP4XXX_CMD_READ    = 0x0C;            // Read data command.
        static const uint8_t MCP4XXX_CMD_INCR    = 0x04;            // Increment command.
        static const uint8_t MCP4XXX_CMD_DECR    = 0x08;            // Decrement command.

        // Private variables. // 
        SPIClass *_spi_bus = NULL;	                // SPI interface pointer.
        const uint8_t _pin_cs;                      // Chip select pin.
        const uint16_t _n_steps = 129;              // Number of steps.
        const uint8_t _wiper_resistance = 75;       // Wiper resistance, in ohms.

        // Private functions. // 
        uint16_t send_cmd(uint8_t addr, uint8_t cmd, uint16_t data);     // Send a command with data.
        void send_cmd(uint8_t addr, uint8_t cmd);                        // Send a command without data (increment, decrement).

};

#endif      // #ifndef VULINTUS_MCP4XXX_129_DIGIPOT_H