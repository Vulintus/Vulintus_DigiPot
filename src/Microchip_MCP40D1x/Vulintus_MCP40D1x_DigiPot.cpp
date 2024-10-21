/* 
    Vulintus_MCP40D1x_DigiPot.cpp

    Copyright 2023, Vulintus, Inc.
    
    See "Vulintus_MCP40D1x_DigiPot.h" for documentation and change log.

*/


#include "./Vulintus_MCP40D1x_DigiPot.h"    //Vulintus MCP40D1x digital potentiometer library.     


// CLASS FUNCTIONS ***********************************************************// 


// Class constructor.
Vulintus_MCP40D1x_DigiPot::Vulintus_MCP40D1x_DigiPot(uint8_t addr, TwoWire *i2c_bus)
    : _i2c_addr(addr)
{
    _i2c_bus = &Wire;                       // Set the I2C bus to the default.
}


// Initialization.
uint8_t Vulintus_MCP40D1x_DigiPot::begin(void)
{
    uint8_t error = 0;                          // Assume no connection error.
    _i2c_bus->begin();                          // Initialize the I2C bus.
    _i2c_bus->beginTransmission(_i2c_addr);     // Start an I2C transmission to the chip.
    error = _i2c_bus->endTransmission();        // Check for an ACK from the chip.
    return error;                               // Return the error value.
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
    float_val *= (wiper_resistance + max_resistance);   // Multiply by the wiper resistance and max resistance to get the actual resistance value.
    return float_val;                                   // Return the float value.
}		


//Read the wiper value.
uint8_t Vulintus_MCP40D1x_DigiPot::read(void)
{
    uint8_t reply;                              // Reply and success/error code.

    _i2c_bus->setClock(MCP40D1X_I2C_CLKRATE);   // Set the I2C clockrate.
    _i2c_bus->beginTransmission(_i2c_addr);     // Start I2C transmission.
    _i2c_bus->write(MCP40D1X_CMD);              // Send the read/write command code (0).    
    reply = _i2c_bus->endTransmission(); 	    // End the transmission.

    if (reply) {                                // If an error occured.
        return 0xFF;                            // Return a value of 255.
    }

    reply = _i2c_bus->requestFrom(_i2c_addr,(uint8_t) 1);  // Request one byte.
    if (reply) {                                // If at least one byte was returned...
        reply = _i2c_bus->read();               // Read the returned byte.
    }
    else {                                      // If no bytes were returned...
        reply = 0xFF;                           // Return a value of 255.
    }

    return reply;                               // Return the reply.
}                         
   


//Write the wiper value.
uint8_t Vulintus_MCP40D1x_DigiPot::write(uint8_t value)
{
    uint8_t nack;                               // NACK success/error code.

    _i2c_bus->setClock(MCP40D1X_I2C_CLKRATE);   // Set the I2C clockrate.
    _i2c_bus->beginTransmission(_i2c_addr);     // Start I2C transmission.
    _i2c_bus->write(MCP40D1X_CMD);              // Send the read/write command code (0).    
    _i2c_bus->write(value);                     // Write the wiper value.
    nack = _i2c_bus->endTransmission(); 	    // End the transmission.

    return nack;                                // Return the reply.
}     