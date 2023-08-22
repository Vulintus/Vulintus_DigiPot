/* 
    Vulintus_MCP4xxx.h

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


#ifndef VULINTUS_MCP41XX_H
#define VULINTUS_MCP41XX_H


//Included libraries.//
#include <Arduino.h>            // Arduino main header.
#include <Wire.h>               // Arduino I2C library.



// CLASS *************************************************************************************************************// 
class Vulintus_MPC41xx {

	public:

		// Constructor. //
		Vulintus_MPC41xx(uint8_t pin_cs);

        // Functions. //
        uint16_t read();                                //Read the Wiper 0 value.
        uint16_t read(uint8_t wiper_i);                 //Read the specified wiper value.
        void write(uint16_t value);                     //Write the Wiper 0 value.
        void write(uint16_t value, uint8_t wiper_i);    //Write the specified wiper value.
        void increment();                               //Increment Wiper 0.
        void increment(uint8_t wiper_i);                //Increment the specified wiper.
        void decrement();                               //Increment Wiper 1.
        void decrement(uint8_t wiper_i);                //Increment the specified wiper.

    private:

        // Constants. //
        static const uint8_t MCP41XX_REG_WIPER[] = {0x00, 0x10};    //Volatile Wiper 0, 1.
        static const uint8_t MCP41XX_REG_TCON    = 0x40;            //Volatile TCON Register.
        static const uint8_t MCP41XX_REG_STATUS  = 0x50;            //Status Register.

        static const uint8_t MCP41XX_STATUS_SHDN = 0x02;            //Hardware Shutdown pin Status bit.

        static const uint8_t MCP41XX_TCON_R0HW   = 0x08;            //Resistor 0 Hardware Configuration Control bit.
        static const uint8_t MCP41XX_TCON_R0A    = 0x04;            //Resistor 0 Terminal A (P0A pin) Connect Control bit .
        static const uint8_t MCP41XX_TCON_R0W    = 0x02;            //Resistor 0 Wiper (P0W pin) Connect Control bit.
        static const uint8_t MCP41XX_TCON_R0B    = 0x01;            //Resistor 0 Terminal B (P0B pin) Connect Control bit.
        static const uint8_t MCP41XX_TCON_R1HW   = 0x80;            //Resistor 1 Hardware Configuration Control bit.
        static const uint8_t MCP41XX_TCON_R1A    = 0x40;            //Resistor 1 Terminal A (P1A pin) Connect Control bit .
        static const uint8_t MCP41XX_TCON_R1W    = 0x20;            //Resistor 1 Wiper (P1W pin) Connect Control bit.
        static const uint8_t MCP41XX_TCON_R1B    = 0x10;            //Resistor 1 Terminal B (P1B pin) Connect Control bit.

        static const uint8_t MCP41XX_CMD_WRITE   = 0x00;            //Write data command.
        static const uint8_t MCP41XX_CMD_READ    = 0x0C;            //Read data command.
        static const uint8_t MCP41XX_CMD_INCR    = 0x04;            //Increment command.
        static const uint8_t MCP41XX_CMD_DECR    = 0x08;            //Decrement command.

        // Variables. //
        uint8_t _pin_cs;                //Chip select pin.

        // Private Functions. //
        uint16_t send_cmd(uint8_t addr, uint8_t cmd, uint16_t data);     //Send a command with data.
        void send_cmd(uint8_t addr, uint8_t cmd);                        //Send a command without data (increment, decrement).

};

#endif      // #ifndef VULINTUS_MCP41XX_H