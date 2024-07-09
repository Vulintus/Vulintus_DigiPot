/*!
	Vulintus_DigiPot.h

	Vulintus, Inc., 2023

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

		// PublicFunctions. // 
        virtual void begin(void) = 0; 									// Initialization.        
		virtual void write_float(float float_val) = 0;					// Write the Wiper 0 value, scaled 0-1.
		virtual void write_float(float float_val, uint8_t wiper_i) = 0;	// Write the specified wiper value, scaled 0-1.
		virtual float read_float(void);                        			// Read the Wiper 0 value, scaled 0-1.
        virtual float read_float(uint8_t wiper_i);         				// Read the specified wiper value, scaled 0-1.

};


// Microchip MCP40D17/18/19 (volatile, I2C).
#include <Vulintus_MCP40D1x_DigiPot.h>

// Microchip MCP413X/415X/423X/425X (volatile, SPI).
#include <Vulintus_MCP4xxx_129_DigiPot.h>
// #include <Vulintus_MCP4xxx_257_DigiPot.h>

// Microchip MCP453X/455X/463X/465X (volatile, I2C).
// #include <Vulintus_MCP45xx_129_DigiPot.h>
// #include <Vulintus_MCP46xx_129_DigiPot.h>
// #include <Vulintus_MCP45xx_257_DigiPot.h>
// #include <Vulintus_MCP46xx_257_DigiPot.h>


// DEFINITIONS ***************************************************************//

#define Vulintus_MCP40D17   Vulintus_MCP40D1x_DigiPot   // Single rheostat, I2C, RAM memory, 7-bit.
#define Vulintus_MCP40D18   Vulintus_MCP40D1x_DigiPot   // Single potentiometer, I2C, RAM memory, 7-bit.
#define Vulintus_MCP40D19   Vulintus_MCP40D1x_DigiPot   // Single rheostat, I2C, RAM memory, 7-bit.

#define Vulintus_MCP4131    Vulintus_MCP4xxx_129_DigiPot    // Single potentiometer, SPI, RAM memory, 7-bit.
#define Vulintus_MCP4132    Vulintus_MCP4xxx_129_DigiPot    // Single rheostat, SPI, RAM memory, 7-bit.
#define Vulintus_MCP4141    Vulintus_MCP4xxx_129_DigiPot    // Single potentiometer, SPI, EE memory, 7-bit.
#define Vulintus_MCP4142    Vulintus_MCP4xxx_129_DigiPot    // Single rheostat, SPI, EE memory, 7-bit.
#define Vulintus_MCP4151    Vulintus_MCP4xxx_257_DigiPot    // Single potentiometer, SPI, RAM memory, 8-bit.
#define Vulintus_MCP4152    Vulintus_MCP4xxx_257_DigiPot    // Single rheostat, SPI, RAM memory, 8-bit.
#define Vulintus_MCP4161    Vulintus_MCP4xxx_257_DigiPot    // Single potentiometer, SPI, EE memory, 8-bit.
#define Vulintus_MCP4162    Vulintus_MCP4xxx_257_DigiPot    // Single rheostat, SPI, EE memory, 8-bit.
#define Vulintus_MCP4231    Vulintus_MCP4xxx_129_DigiPot    // Dual potentiometer, SPI, RAM memory, 7-bit.
#define Vulintus_MCP4232    Vulintus_MCP4xxx_129_DigiPot    // Dual rheostat, SPI, RAM memory, 7-bit.
#define Vulintus_MCP4241    Vulintus_MCP4xxx_129_DigiPot    // Dual potentiometer, SPI, EE memory, 7-bit.
#define Vulintus_MCP4242    Vulintus_MCP4xxx_129_DigiPot    // Dual rheostat, SPI, EE memory, 7-bit.
#define Vulintus_MCP4251    Vulintus_MCP4xxx_257_DigiPot    // Dual potentiometer, SPI, RAM memory, 8-bit.
#define Vulintus_MCP4252    Vulintus_MCP4xxx_257_DigiPot    // Dual rheostat, SPI, RAM memory, 8-bit.
#define Vulintus_MCP4261    Vulintus_MCP4xxx_257_DigiPot    // Dual potentiometer, SPI, EE memory, 8-bit.
#define Vulintus_MCP4262    Vulintus_MCP4xxx_257_DigiPot    // Dual rheostat, SPI, E memory, 8-bit.

#define Vulintus_MCP4531    Vulintus_MCP4xxx_DigiPot    // Single potentiometer, I2C, RAM memory, 7-bit.
#define Vulintus_MCP4532    Vulintus_MCP4xxx_DigiPot    // Single rheostat, I2C, RAM memory, 7-bit.
#define Vulintus_MCP4541    Vulintus_MCP4xxx_DigiPot    // Single potentiometer, I2C, EE memory, 7-bit.
#define Vulintus_MCP4542    Vulintus_MCP4xxx_DigiPot    // Single rheostat, I2C, EE memory, 7-bit.
#define Vulintus_MCP4551    Vulintus_MCP4xxx_DigiPot    // Single potentiometer, I2C, RAM memory, 8-bit.
#define Vulintus_MCP4552    Vulintus_MCP4xxx_DigiPot    // Single rheostat, I2C, RAM memory, 8-bit.
#define Vulintus_MCP4561    Vulintus_MCP4xxx_DigiPot    // Single potentiometer, I2C, EE memory, 8-bit.
#define Vulintus_MCP4562    Vulintus_MCP4xxx_DigiPot    // Single rheostat, I2C, EE memory, 8-bit.
#define Vulintus_MCP4631    Vulintus_MCP4xxx_DigiPot    // Dual potentiometer, I2C, RAM memory, 7-bit.
#define Vulintus_MCP4632    Vulintus_MCP4xxx_DigiPot    // Dual rheostat, I2C, RAM memory, 7-bit.
#define Vulintus_MCP4641    Vulintus_MCP4xxx_DigiPot    // Dual potentiometer, I2C, EE memory, 7-bit.
#define Vulintus_MCP4642    Vulintus_MCP4xxx_DigiPot    // Dual rheostat, I2C, EE memory, 7-bit.
#define Vulintus_MCP4651    Vulintus_MCP4xxx_DigiPot    // Dual potentiometer, I2C, RAM memory, 8-bit.
#define Vulintus_MCP4652    Vulintus_MCP4xxx_DigiPot    // Dual rheostat, I2C, RAM memory, 8-bit.
#define Vulintus_MCP4661    Vulintus_MCP4xxx_DigiPot    // Dual potentiometer, I2C, EE memory, 8-bit.
#define Vulintus_MCP4662    Vulintus_MCP4xxx_DigiPot    // Dual rheostat, I2C, E memory, 8-bit.


#endif      // #ifndef VULINTUS_DIGIPOT_H