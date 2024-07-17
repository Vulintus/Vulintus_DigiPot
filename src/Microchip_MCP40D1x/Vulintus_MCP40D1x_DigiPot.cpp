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


#include <Microchip_MCP40D1x/Vulintus_MCP40D1x_DigiPot.h>    //Vulintus MCP40D1x digital potentiometer library.     


// CLASS FUNCTIONS ***********************************************************// 


// Class constructor (Default I2C bus, default address).
Vulintus_MCP40D1x_DigiPot::Vulintus_MCP40D1x_DigiPot(void)
{
    _wire = &Wire;                      // Set the I2C bus to the default.
    _addr = MCP40D1x_E_I2C_ADDR;        // Set the I2C address.
}


// Class constructor (Specified I2C bus, default address.
Vulintus_MCP40D1x_DigiPot::Vulintus_MCP40D1x_DigiPot(TwoWire *i2c_bus)
        : _wire(i2c_bus)
{
    _addr = MCP40D1x_E_I2C_ADDR;        // Set the I2C address.
}


// Class constructor (Specified I2C bus, default address).
Vulintus_MCP40D1x_DigiPot::Vulintus_MCP40D1x_DigiPot(TwoWire *i2c_bus, MCP40D1x_I2C_Addr addr)
        : _wire(i2c_bus), _addr(addr)
{

}


// Initialization.
uint8_t Vulintus_MCP40D1x_DigiPot::begin(void)
{
    uint8_t success;
    // uint8_t success = _wire->begin();                     // Initialize the I2C bus.    
    return success;
}


// Write the Wiper 0 value, scaled 0-1 (Vulintus_DigiPot base class function).
float Vulintus_MCP40D1x_DigiPot::set_scaled(float float_scaled)
{
    float_scaled *= (float) _n_resistors;   // Calculate the fractional number of steps.
    uint16_t uint_val = float_scaled;       // Convert the float to a uint16.
    write(uint_val);                        // Write the value to the specified wiper.
    float_scaled = get_scaled();            // Read the actual scaled value.
    return float_scaled;                    // Return the actual scaled value.
}


// Write the specified wiper value, scaled 0-1 (Vulintus_DigiPot base class function).
float Vulintus_MCP40D1x_DigiPot::set_scaled(float float_val, uint8_t wiper_i)
{
    float_val = set_scaled(float_val);     // Write the value, ignoring the wiper index.
    return float_val;                      // Return the actual scaled value.
}


// Read the Wiper 0 value, scaled 0-1 (Vulintus_DigiPot base class function).
float Vulintus_MCP40D1x_DigiPot::get_scaled(void)
{
    float float_val = read();                           // Read the wiper value, ignoring the wiper index.
    float_val /= (float) _n_resistors;                  // Convert the step setting to fractional 0-1.
    float_val *= max_resistance;                        // Convert the scaled value to resistance (ohms).
    float_val += wiper_resistance;                      // Add the wiper resistance.
    float_val /= (wiper_resistance + max_resistance);   // Divide by the wiper resistance and max resistance to get the actual scaled value.
    return float_val;                                   // Read the scaled value.
}                        


// Read the specified wiper value, scaled 0-1 (Vulintus_DigiPot base class function).
float Vulintus_MCP40D1x_DigiPot::get_scaled(uint8_t wiper_i)
{
    float float_val = get_scaled();         // Read the scaled value, ignoring the wiper index.
    return float_val;                       // Return the scaled float value.
}      		    


// Write the Wiper 0 value, in real resistance (ohms).
float Vulintus_MCP40D1x_DigiPot::set_resistance(float float_val)
{
    float_val = set_resistance(float_val, (uint8_t) 0);     // Set the resistance (ohms) on wiper 0.
    return float_val;                                       // Return the float value.
}					


// Write the specified wiper value, in real resistance (ohms).
float Vulintus_MCP40D1x_DigiPot::set_resistance(float float_val, uint8_t wiper_i)
{
    if (float_val > wiper_resistance) {             // If the specified resistance is greater than the wiper resistance...
        float_val -= wiper_resistance;              // Subtract the wiper resistance.
        float_val /= max_resistance;                // Convert the resistance value to scaled, 0-1.
    }
    else {                                          // Otherwise, if the specified resistance is less than the wiper resistance...
        float_val = 0;                              // Set the scaled value to zero.
    }    
    float_val = set_scaled(float_val, wiper_i);     // Set the scaled setting.
    float_val *= max_resistance;                    // Convert the scaled value to resistance (ohms).
    float_val += wiper_resistance;                  // Add the wiper resistance.
    return float_val;                               // Return the float value.
}	


// Read the Wiper 0 value, in real resistance (ohms).
float Vulintus_MCP40D1x_DigiPot::get_resistance(void)
{
    float float_val = get_resistance((uint8_t) 0);      // Fetch the resistance from wiper 0.
}    			


// Read the specified wiper value, in real resistance (ohms).
float Vulintus_MCP40D1x_DigiPot::get_resistance(uint8_t wiper_i)
{
    float float_val = get_scaled(wiper_i);              // Read the scaled value of the wiper, 0-1.
    float_val += (wiper_resistance + max_resistance);   // Multiply by the wiper resistance and max resistance to get the actual resistance value.
    return float_val;                                   // Return the float value.
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

    reply = _wire->requestFrom(_addr,(uint8_t) 1);  // Request one byte.
    if (reply) {                                    // If at least one byte was returned...
        reply = _wire->read();                      // Read the returned byte.
    }
    else {                                          // If no bytes were returned...
        reply = 0xFF;                               // Return a value of 255.
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