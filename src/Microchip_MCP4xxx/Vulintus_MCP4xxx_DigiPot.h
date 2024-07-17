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


#ifndef VULINTUS_MCP4XXX_DIGIPOT_H
#define VULINTUS_MCP4XXX_DIGIPOT_H


// Included libraries.// 
#include <Arduino.h>                // Arduino main header.
#include <SPI.h>		            // Standard Arduino SPI library.

#include <Vulintus_DigiPot.h>       // Vulintus digital potentiometer base class.


// DEFINITIONS *******************************************************************************************************//
enum MCP4xxx_I2C_addr : uint8_t {
    MCP4XXX_I2C_ADDR_LLL = 0b0101000,   //0x28, MCP46x1.
    MCP4XXX_I2C_ADDR_LLH = 0b0101001,   //0x29, MCP46x1.
    MCP4XXX_I2C_ADDR_LHL = 0b0101010,   //0x2A, MCP46x1.
    MCP4XXX_I2C_ADDR_LHH = 0b0101011,   //0x2B, MCP46x1.
    MCP4XXX_I2C_ADDR_HLL = 0b0101100,   //0x2C, MCP45x2/46x1/46x2.
    MCP4XXX_I2C_ADDR_HLH = 0b0101101,   //0x2D, MCP45x2/46x1/46x2.
    MCP4XXX_I2C_ADDR_HHL = 0b0101110,   //0x2E, MCP45x1/45x2/46x1/46x2.
    MCP4XXX_I2C_ADDR_HHH = 0b0101111,   //0x2F, MCP45x1/45x2/46x1/46x2.
};

// CLASSES ***********************************************************************************************************// 

class Vulintus_MCP4xxx_DigiPot : public Vulintus_DigiPot {

	public:

		// Constructors. // 
        Vulintus_MCP4xxx_DigiPot(uint16_t n_resistors, uint8_t pin_cs, SPIClass *spi_bus = &SPI);
        Vulintus_MCP4xxx_DigiPot(uint16_t n_resistors, TwoWire *i2c_bus = &Wire, \
                MCP4xxx_I2C_addr i2c_addr = MCP4XXX_I2C_ADDR_HHL);

        // Public variables matching "Vulintus_DigiPot" base class. //
        float wiper_resistance = 75;        // Wiper resistance, in ohms.
        float max_resistance = 10000;       // Maximum resistance (not counting wiper), in ohms

        // Public functions matching "Vulintus_DigiPot" base class. //
        uint8_t begin(void); 		        // Initialization.       

		float set_scaled(float float_scaled);			        // Write the Wiper 0 value, scaled 0-1.
		float set_scaled(float float_scaled, uint8_t wiper_i);  // Write the specified wiper value, scaled 0-1.
		float get_scaled(void);                                 // Read the Wiper 0 value, scaled 0-1.
        float get_scaled(uint8_t wiper_i);         		        // Read the specified wiper value, scaled 0-1.

        float set_resistance(float float_ohms);					    // Write the Wiper 0 value, in real resistance (ohms).
		float set_resistance(float float_ohms, uint8_t wiper_i);    // Write the specified wiper value, in real resistance (ohms).
		float get_resistance(void);                        		    // Read the Wiper 0 value, in real resistance (ohms).
        float get_resistance(uint8_t wiper_i);         			    // Read the specified wiper value, in real resistance (ohms).

        // Public functions. //
        uint16_t read(void);                            // Read the Wiper 0 value.
        uint16_t read(uint8_t wiper_i);                 // Read the specified wiper value.
        void write(uint16_t value);                     // Write the Wiper 0 value.
        void write(uint16_t value, uint8_t wiper_i);    // Write the specified wiper value.
        void increment(void);                           // Increment Wiper 0.
        void increment(uint8_t wiper_i);                // Increment the specified wiper.
        void decrement(void);                           // Decrement Wiper 0.
        void decrement(uint8_t wiper_i);                // Decrement the specified wiper.        

    private:

        // Private constants. // 
        static const uint32_t MCP4XXX_I2C_CLKRATE = 400000;     // Clock frequency for I2C communication (Hz).
        static const uint32_t MCP4XXX_SPI_CLKRATE = 1000000;    // Clock frequency for SPI communication (Hz).

        static const uint8_t MCP4XXX_REG_WIPER0  = 0x00;    // Volatile Wiper 0.
        static const uint8_t MCP4XXX_REG_WIPER1  = 0x10;    // Volatile Wiper 1.
        static const uint8_t MCP4XXX_REG_TCON    = 0x40;    // Volatile TCON Register.
        static const uint8_t MCP4XXX_REG_STATUS  = 0x50;    // Status Register.

        static const uint8_t MCP4XXX_STATUS_SHDN = 0x02;    // Hardware Shutdown pin Status bit.

        static const uint8_t MCP4XXX_TCON_R0HW   = 0x08;    // Resistor 0 Hardware Configuration Control bit.
        static const uint8_t MCP4XXX_TCON_R0A    = 0x04;    // Resistor 0 Terminal A (P0A pin) Connect Control bit .
        static const uint8_t MCP4XXX_TCON_R0W    = 0x02;    // Resistor 0 Wiper (P0W pin) Connect Control bit.
        static const uint8_t MCP4XXX_TCON_R0B    = 0x01;    // Resistor 0 Terminal B (P0B pin) Connect Control bit.
        static const uint8_t MCP4XXX_TCON_R1HW   = 0x80;    // Resistor 1 Hardware Configuration Control bit.
        static const uint8_t MCP4XXX_TCON_R1A    = 0x40;    // Resistor 1 Terminal A (P1A pin) Connect Control bit .
        static const uint8_t MCP4XXX_TCON_R1W    = 0x20;    // Resistor 1 Wiper (P1W pin) Connect Control bit.
        static const uint8_t MCP4XXX_TCON_R1B    = 0x10;    // Resistor 1 Terminal B (P1B pin) Connect Control bit.

        static const uint8_t MCP4XXX_CMD_WRITE   = 0x00;    // Write data command.
        static const uint8_t MCP4XXX_CMD_READ    = 0x0C;    // Read data command.
        static const uint8_t MCP4XXX_CMD_INCR    = 0x04;    // Increment command.
        static const uint8_t MCP4XXX_CMD_DECR    = 0x08;    // Decrement command.

        // Private variables. // 
        SPIClass *_spi_bus = NULL;	    // SPI interface pointer.
        uint8_t _pin_cs;                // Chip select pin.

        TwoWire *_i2c_bus = NULL;       // I2C interface pointer.
        MCP4xxx_I2C_addr _i2c_addr;     // I2C address.
        
        uint16_t _n_resistors;          // Number of resistors in the ladder network.        

        // Private functions. // 
        uint16_t send_cmd(uint8_t addr, uint8_t cmd, uint16_t data);     // Send a command with data.
        void send_cmd(uint8_t addr, uint8_t cmd);                        // Send a command without data (increment, decrement).

};


class Vulintus_MCP4xxx_SPI_128_DigiPot : public Vulintus_MCP4xxx_DigiPot {

    public:
            
        Vulintus_MCP4xxx_SPI_128_DigiPot(uint8_t pin_cs, SPIClass *spi_bus) 
            : Vulintus_MCP4xxx_DigiPot(128, pin_cs, spi_bus)
        { 
            //empty
        }

};


class Vulintus_MCP4xxx_SPI_256_DigiPot : public Vulintus_MCP4xxx_DigiPot {

    public:
    
        Vulintus_MCP4xxx_SPI_256_DigiPot(uint8_t pin_cs, SPIClass *spi_bus) 
            : Vulintus_MCP4xxx_DigiPot(256, pin_cs, spi_bus)
        { 
            //empty
        }

};


class Vulintus_MCP4xxx_I2C_128_DigiPot : public Vulintus_MCP4xxx_DigiPot {

    public:
            
        Vulintus_MCP4xxx_I2C_128_DigiPot(TwoWire *i2c_bus = &Wire, MCP4xxx_I2C_addr i2c_addr = MCP4XXX_I2C_ADDR_HHL) 
            : Vulintus_MCP4xxx_DigiPot(128, i2c_bus, i2c_addr)
        { 
            //empty
        }

};


class Vulintus_MCP4xxx_I2C_256_DigiPot : public Vulintus_MCP4xxx_DigiPot {

    public:
    
        Vulintus_MCP4xxx_I2C_256_DigiPot(TwoWire *i2c_bus = &Wire, MCP4xxx_I2C_addr i2c_addr = MCP4XXX_I2C_ADDR_HHL) 
            : Vulintus_MCP4xxx_DigiPot(256, i2c_bus, i2c_addr)
        { 
            //empty
        }

};

        


#endif      // #ifndef VULINTUS_MCP4XXX_DIGIPOT_H