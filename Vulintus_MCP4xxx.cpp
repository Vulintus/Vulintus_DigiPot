/* 
    Vulintus_MCP4xxx.cpp

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
*/


#include <Vulintus_MC41xx.h>            //Vulintus MCP41xx library.     
#include <SPI.h>                        //Arduino SPI library.


// CLASS FUNCTIONS ***********************************************************// 

// Class constructor.
Vulintus_MPC41xx::Vulintus_MPC41xx(uint8_t pin_cs) : _pin_cs(pin_cs)
{
    SPI.begin();                        //Initialize SPI communication.
    pinMode(pin_cs, OUTPUT);            //Set the CS pin mode to output.
    digitalWrite(pin_cs, HIGH);         //Set the CS pin high.
}


//Read the Wiper 0 value.
uint16_t Vulintus_MPC41xx::read()
{
    return Vulintus_MPC41xx::read((uint8_t) 0);             //Read the value from wiper 0.
}                         


//Read the specified wiper value.
uint16_t Vulintus_MPC41xx::read(uint8_t wiper_i)
{
    return send_cmd(MCP41XX_REG_WIPER[wiper_i], MCP41XX_CMD_READ, (uint16_t) 255);
}          


//Write the Wiper 0 value.
void Vulintus_MPC41xx::write(uint16_t value)
{
    Vulintus_MPC41xx::write(uint16_t value, (uint8_t) 0);   //Write the value to wiper 0.
}     


//Write the specified wiper value.
void Vulintus_MPC41xx::write(uint16_t value, uint8_t wiper_i)
{
    send_cmd(MCP41XX_REG_WIPER[wiper_i], MCP41XX_CMD_WRITE, value);
}   


//Increment Wiper 0.
void Vulintus_MPC41xx::increment()
{
    Vulintus_MPC41xx::increment((uint8_t) 0);     //Increment wiper 0.
}           


//Increment the specified wiper.
void Vulintus_MPC41xx::increment(uint8_t wiper_i)
{
    send_cmd(MCP41XX_REG_WIPER[wiper_i], MCP41XX_CMD_INCR);
}            


//Increment Wiper 1.
void Vulintus_MPC41xx::decrement()
{
    Vulintus_MPC41xx::decrement((uint8_t) 0);     //Decrement wiper 0.
}                         


//Increment the specified wiper.
void Vulintus_MPC41xx::decrement(uint8_t wiper_i)
{
    send_cmd(MCP41XX_REG_WIPER[wiper_i], MCP41XX_CMD_INCR);
}           


//Send a command with data.
uint16_t send_cmd(uint8_t addr, uint8_t cmd, uint16_t data)
{
    uint8_t hi_byte = addr | cmd | (data >> 8);     //Combine the address, command and MSB to make the high byte.
    uint8_t lo_byte = data;                         //Grab the bottom 8 bits from the data for the low byte.

    SPI.beginTransaction(SPISettings(250000, MSBFIRST, SPI_MODE0)); //Set the SPI settings for this chip.
    digitalWrite(_pin_cs, LOW);                                     //Set the chip select line low.    
    hi_byte = SPI.transfer(hi_byte);                                //Send the high byte.
    lo_byte = SPI.transfer(lo_byte);                                //Send the low byte.
    digitalWrite(_pin_cs, HIGH);                                    //Set the chip select line high. 
    SPI.endTransaction();                                           //Release the SPI bus.

    uint16_t reply = (uint16_t) (hi_byte << 8) + low_byte;          //Combine the high and low bytes.
    reply &= 0x01FF;                                                //Kick out all but the bottom 9 bits.

    return reply;                                                   //Return the result.
}


//Send a command without data (increment, decrement).
void send_cmd(uint8_t addr, uint8_t cmd)
{
    uint8_t hi_byte = addr | cmd | (data >> 8);     //Combine the address, command and MSB to make the high byte.

    SPI.beginTransaction(SPISettings(250000, MSBFIRST, SPI_MODE0)); //Set the SPI settings for this chip.
    digitalWrite(_pin_cs, LOW);                                     //Set the chip select line low.    
    SPI.transfer(hi_byte);                                          //Send the high byte.
    digitalWrite(_pin_cs, HIGH);                                    //Set the chip select line high. 
    SPI.endTransaction();                                           //Release the SPI bus.
}                