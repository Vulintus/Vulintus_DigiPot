/*!
	Vulintus_DigiPot.h

	copyright 2023, Vulintus, Inc.

	Catch-all library for digital potentiometers/rheostats commonly used by Vulintus.
	
	UPDATE LOG:
		2023-12-12 - Drew Sloan - File first created to combine all digital 
                                  potentiometer library calls under a single 
                                  parent header.
		2024-07-08 - Drew Sloan	- Created "Vulintus_DigiPot" base class.						  
*/


#ifndef VULINTUS_DIGIPOT_H
#define VULINTUS_DIGIPOT_H

#include <Arduino.h>                    //Standard Arduino header.


//CLASSES ******************************************************************************************************//
class Vulintus_DigiPot
{
    public:

        // Class Constructor. //
        Vulintus_DigiPot(void);

        // Class Destructor. //
        ~Vulintus_DigiPot(void);

		// Public Variables. //
		float wiper_resistance;    	// Wiper resistance, in ohms.
		float max_resistance;    	// Maximum resistance (not counting wiper), in ohms.
		uint16_t n_resistors;     	// Number of resistors in the ladder network.  

		// Public Functions. // 
        virtual uint8_t begin(void) = 0;		// Initialization.        

		virtual float set_scaled(float float_scaled) = 0;						// Write the Wiper 0 value, scaled 0-1.
		virtual float set_scaled(float float_scaled, uint8_t wiper_i) = 0;		// Write the specified wiper value, scaled 0-1.
		virtual float get_scaled(void);                        					// Read the Wiper 0 value, scaled 0-1.
        virtual float get_scaled(uint8_t wiper_i);         						// Read the specified wiper value, scaled 0-1.

		virtual float set_resistance(float float_ohms) = 0;						// Write the Wiper 0 value, in real resistance (ohms).
		virtual float set_resistance(float float_ohms, uint8_t wiper_i) = 0;	// Write the specified wiper value, in real resistance (ohms).
		virtual float get_resistance(void);                        				// Read the Wiper 0 value, in real resistance (ohms).
        virtual float get_resistance(uint8_t wiper_i);         					// Read the specified wiper value, in real resistancev.

};


// Analog Devices MCP40D17/18/19 (volatile/OTP, I2C).
#include "./Analog_Devices_AD5273/Vulintus_AD5273_DigiPot.h"

// Microchip MCP40D17/18/19 (volatile, I2C).
#include "./Microchip_MCP40D1x/Vulintus_MCP40D1x_DigiPot.h"

// Microchip MCP413X/415X/423X/425X/453X/455X/463X/465X (volatile, SPI or I2C).
#include "./Microchip_MCP4xxx/Vulintus_MCP4xxx_DigiPot.h"



// DEFINITIONS ***************************************************************//

#define Vulintus_AD5273   	Vulintus_AD5273_DigiPot   			// Single potentiometer, I2C, OTP, 6-bit.

#define Vulintus_MCP40D17   Vulintus_MCP40D1x_DigiPot   		// Single rheostat, I2C, RAM memory, 7-bit.
#define Vulintus_MCP40D18   Vulintus_MCP40D1x_DigiPot   		// Single potentiometer, I2C, RAM memory, 7-bit.
#define Vulintus_MCP40D19   Vulintus_MCP40D1x_DigiPot   		// Single rheostat, I2C, RAM memory, 7-bit.

#define Vulintus_MCP4131    Vulintus_MCP4xxx_SPI_128_DigiPot    // Single potentiometer, SPI, RAM memory, 7-bit.
#define Vulintus_MCP4132    Vulintus_MCP4xxx_SPI_128_DigiPot    // Single rheostat, SPI, RAM memory, 7-bit.
#define Vulintus_MCP4141    Vulintus_MCP4xxx_SPI_128_DigiPot    // Single potentiometer, SPI, EE memory, 7-bit.
#define Vulintus_MCP4142    Vulintus_MCP4xxx_SPI_128_DigiPot    // Single rheostat, SPI, EE memory, 7-bit.
#define Vulintus_MCP4151    Vulintus_MCP4xxx_SPI_256_DigiPot    // Single potentiometer, SPI, RAM memory, 8-bit.
#define Vulintus_MCP4152    Vulintus_MCP4xxx_SPI_256_DigiPot    // Single rheostat, SPI, RAM memory, 8-bit.
#define Vulintus_MCP4161    Vulintus_MCP4xxx_SPI_256_DigiPot    // Single potentiometer, SPI, EE memory, 8-bit.
#define Vulintus_MCP4162    Vulintus_MCP4xxx_SPI_256_DigiPot    // Single rheostat, SPI, EE memory, 8-bit.
#define Vulintus_MCP4231    Vulintus_MCP4xxx_SPI_128_DigiPot    // Dual potentiometer, SPI, RAM memory, 7-bit.
#define Vulintus_MCP4232    Vulintus_MCP4xxx_SPI_128_DigiPot    // Dual rheostat, SPI, RAM memory, 7-bit.
#define Vulintus_MCP4241    Vulintus_MCP4xxx_SPI_128_DigiPot    // Dual potentiometer, SPI, EE memory, 7-bit.
#define Vulintus_MCP4242    Vulintus_MCP4xxx_SPI_128_DigiPot    // Dual rheostat, SPI, EE memory, 7-bit.
#define Vulintus_MCP4251    Vulintus_MCP4xxx_SPI_256_DigiPot    // Dual potentiometer, SPI, RAM memory, 8-bit.
#define Vulintus_MCP4252    Vulintus_MCP4xxx_SPI_256_DigiPot    // Dual rheostat, SPI, RAM memory, 8-bit.
#define Vulintus_MCP4261    Vulintus_MCP4xxx_SPI_256_DigiPot    // Dual potentiometer, SPI, EE memory, 8-bit.
#define Vulintus_MCP4262    Vulintus_MCP4xxx_SPI_256_DigiPot    // Dual rheostat, SPI, E memory, 8-bit.

#define Vulintus_MCP4531    Vulintus_MCP4xxx_I2C_128_DigiPot	// Single potentiometer, I2C, RAM memory, 7-bit.
#define Vulintus_MCP4532    Vulintus_MCP4xxx_I2C_128_DigiPot	// Single rheostat, I2C, RAM memory, 7-bit.
#define Vulintus_MCP4541    Vulintus_MCP4xxx_I2C_128_DigiPot 	// Single potentiometer, I2C, EE memory, 7-bit.
#define Vulintus_MCP4542    Vulintus_MCP4xxx_I2C_128_DigiPot    // Single rheostat, I2C, EE memory, 7-bit.
#define Vulintus_MCP4551    Vulintus_MCP4xxx_I2C_256_DigiPot    // Single potentiometer, I2C, RAM memory, 8-bit.
#define Vulintus_MCP4552    Vulintus_MCP4xxx_I2C_256_DigiPot    // Single rheostat, I2C, RAM memory, 8-bit.
#define Vulintus_MCP4561    Vulintus_MCP4xxx_I2C_256_DigiPot    // Single potentiometer, I2C, EE memory, 8-bit.
#define Vulintus_MCP4562    Vulintus_MCP4xxx_I2C_256_DigiPot    // Single rheostat, I2C, EE memory, 8-bit.
#define Vulintus_MCP4631    Vulintus_MCP4xxx_I2C_128_DigiPot    // Dual potentiometer, I2C, RAM memory, 7-bit. *
#define Vulintus_MCP4632    Vulintus_MCP4xxx_I2C_128_DigiPot   	// Dual rheostat, I2C, RAM memory, 7-bit.
#define Vulintus_MCP4641    Vulintus_MCP4xxx_I2C_128_DigiPot    // Dual potentiometer, I2C, EE memory, 7-bit.
#define Vulintus_MCP4642    Vulintus_MCP4xxx_I2C_128_DigiPot    // Dual rheostat, I2C, EE memory, 7-bit.
#define Vulintus_MCP4651    Vulintus_MCP4xxx_I2C_256_DigiPot    // Dual potentiometer, I2C, RAM memory, 8-bit.
#define Vulintus_MCP4652    Vulintus_MCP4xxx_I2C_256_DigiPot    // Dual rheostat, I2C, RAM memory, 8-bit.
#define Vulintus_MCP4661    Vulintus_MCP4xxx_I2C_256_DigiPot    // Dual potentiometer, I2C, EE memory, 8-bit.
#define Vulintus_MCP4662    Vulintus_MCP4xxx_I2C_256_DigiPot    // Dual rheostat, I2C, E memory, 8-bit.


#endif      // #ifndef VULINTUS_DIGIPOT_H