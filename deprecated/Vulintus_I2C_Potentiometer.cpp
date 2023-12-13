#include "Vulintus_I2C_Potentiometer.h" 					//Make sure to include the corresponding header file.


//CLASS CONSTRUCTOR ********************************************************************************************************************************************************************************//
Vulintus_I2C_Potentiometer::Vulintus_I2C_Potentiometer(uint8_t addr, uint16_t ntaps, uint8_t cmd_byte, uint32_t clockrate)
	:  _addr(addr), _ntaps(ntaps), _cmd_byte(cmd_byte), _clockrate(clockrate)
{}


//INITIALIZATION ***********************************************************************************************************************************************************************************//
uint8_t Vulintus_I2C_Potentiometer::begin()
{
	Wire.begin();																//Join the I2C bus as the master.
	Wire.setClock(_clockrate);									//Set the I2C clock frequency.
	Wire.beginTransmission(_addr); 							//Start an I2C transmission to the potentiometer.
	uint8_t ret = Wire.endTransmission(true); 	//End the transmission, releasing the I2C bus.
	if (ret != 0) { 														//If a transmit ACK wasn't received...
		return 0; 																//Return an error.
	}
	return 1; 																	//Return the success/error code.
}


//FUNCTIONS ****************************************************************************************************************************************************************************************//
void Vulintus_I2C_Potentiometer::write(uint16_t pot_val)
{
	uint16_t factor = 1;											//Create an unsigned integer to hold a multiplication factor.
	if ((pot_val + 1) > (_ntaps)) { 					//If the passed value is greater than the number of taps...
		if (((pot_val + 1) % _ntaps) == 0) { 		//If the passed value is a remainder-less factor of the number of taps...
			factor = (pot_val + 1)/_ntaps;				//Set the multiplication factor.
		}
		else { 																	//Otherwise, if there is a remainder...
			factor = (pot_val + 1)/_ntaps + 1;		//Set the multiplication factor, adding one.
		}
		pot_val = (pot_val + 1)/factor - 1;			//Scale the pot value accordingly.
	}
	Wire.setClock(_clockrate);								//Set the I2C clock frequency.
	Wire.beginTransmission(_addr); 						//Start an I2C transmission to the potentiometer.
	if (_cmd_byte) { 													//If the potentiometer uses a command byte...
		Wire.write(byte(0x00));            			//Write a command byte of zero.
	}
	Wire.write(pot_val);             					//Send the potentiometer setting value.
	if (_ntaps > 256) { 											//If the resolution is greater than 8 bits...
		Wire.write(pot_val >> 8);								//Send the second byte.
	}
	Wire.endTransmission();     							//End the transmission.
}


uint8_t Vulintus_I2C_Potentiometer::read(uint16_t *pot_val)
{
	uint8_t ret = 1;													//Create an unsigned byte for returning success/error codes.
	uint8_t return_bytes;											//Create an unsigned byte to hold the number of expected return bytes.
	uint16_t serial_reply;										//Create an unsigned integer to hold the serial reply.
	Wire.setClock(_clockrate);								//Set the I2C clock frequency.
	Wire.beginTransmission(_addr); 						//Start an I2C transmission to the potentiometer.
	if (_cmd_byte) { 													//If the potentiometer uses a command byte...
		Wire.write(byte(0x00));            			//Write a command byte of zero.
	}
	ret = Wire.endTransmission(false); 				//End the transmission, but do not release the bus.
	if (ret != 0) { 													//If an error was returned...
		return ret; 														//Return the success/error code.
	}
	if (_ntaps > 256) { 											//If the resolution is greater than 8 bits...
		return_bytes = 2;												//Set the number of expected return bytes to 2.
	}
	else {																		//Otherwise, if the resolution is 8 bits or less...
		return_bytes = 1;												//Set the number of expected return bytes to 2.
	}
	Wire.requestFrom(_addr, return_bytes); 		//Request bytes from the potentiometer.
	if (Wire.available() < return_bytes) {		//If there's fewer bytes available than requested...
		return 0; 															//Return an error.
	}
	for (int i = 0; i < return_bytes; i++) { 	//Increment through the requested bytes.
		serial_reply = Wire.read() + (serial_reply << 8);	//Read the next byte from the I2C buffer.
	}
	*pot_val = serial_reply;									//Copy the serial reply to the input pointer.
}


