#ifndef VULINTUS_I2C_POTENTIOMETER_H
#define VULINTUS_I2C_POTENTIOMETER_H

#include "Arduino.h" 										//Include the general Arduino library.
#include "Wire.h"												//Include the general I2C library.


//I2C ADDRESSES ******************************************************************************************************//
	#define MCP40D_I2C_ADDR				0x2E		//I2C address for the MCP40D** rheostat/potentiometer.
	#define MCP40DA_I2C_ADDR			0x3E		//I2C address for the MCP40D18A rheostat/potentiometer (alternate I2C address for MCP30D18).

//POTENTIOMETER RESOLUTION *************************************************************************************//
	#define MCP40D_NTAPS					128			//Number of taps in the MCP40D** rheostat/potentiometer.

//CONTROL BYTES ******************************************************************************************************//
	#define MCP40D_CMD_SET				0x00		//Command byte for setting the potentiometer value.

//I2C CONSTANTS ******************************************************************************************************//
	#define I2C_400KHZ_CLOCK			400000	//Set the clock frequency for I2C communication.


//CLASSES ************************************************************************************************************//
class Vulintus_I2C_Potentiometer {

	public:

		//Constructors.//
		Vulintus_I2C_Potentiometer(uint8_t addr, uint16_t ntaps,
			uint8_t cmd_byte, uint32_t clockrate);		//Class constructor, using default I2C address.

		//Functions.//
		uint8_t begin(void); 								//Function for initializing the potentiometer.
		void write(uint16_t pot_val);				//Function for setting the tap position.
		uint8_t read(uint16_t *pot_val);		//Function for reading the current tap position.

	private:

		//Variables.//
		uint8_t _addr;											//Unsigned byte for the I2C address.
		uint16_t _ntaps;										//Unsigned integer to hold the number of taps in the pot (a.k.a. bit resolution).
		uint32_t _clockrate;								//Unsigned long integer to hold the I2C clockrate.
		uint8_t _cmd_byte;									//Unsigned byte to indicate when a command byte is necessary.

};

#endif 																	//#ifndef VULINTUS_I2C_POTENTIOMETER_H