/*!
	Vulintus_DigiPot.cpp

	Vulintus, Inc., 2023

	Catch-all library for digital potentiometers/rheostats commonly used by Vulintus.
	
	UPDATE LOG:
		2024-07-08 - Drew Sloan	- Created "Vulintus_DigiPot" base class.						  
*/


#include ".Vulintus_DigiPot.h"


// Class Constructor. //
Vulintus_DigiPot::Vulintus_DigiPot(void)
{

}


// Class Destructor. //
Vulintus_DigiPot::~Vulintus_DigiPot(void)
{

}


// Read the Wiper 0 value, scaled 0-1.
float Vulintus_DigiPot::get_scaled(void)
{
    return (float) -1;
}


// Read the specified wiper value, scaled 0-1.
float Vulintus_DigiPot::get_scaled(uint8_t wiper_i)
{
    return (float) -1;
}


// Read the Wiper 0 value, in real resistance.
float Vulintus_DigiPot::get_resistance(void)
{
    return (float) -1;
}


// Read the specified wiper value, in real resistance.
float Vulintus_DigiPot::get_resistance(uint8_t wiper_i)
{
    return (float) -1;
}