/*  Vulintus_DigiPot_Test.ino

    copyright Vulintus, Inc., 2024

    Example demonstrating control of a digital potentiometer/rheostat using
    the Vulintus_DigiPot class.

    UPDATE LOG:
      2024-07-17 - Drew Sloan - Example first created.

*/


// Included libraries. // 
#include <Vulintus_DigiPot.h>               // Vulintus digital potentiometer/rheostat catch-all library.

// Pin assignments. // 
#define PIN_CS      9                       // Chip-select for SPI potentiometers.

// I2C address. // 
#define I2C_ADDR  MCP4XXX_I2C_ADDR_LLL      // Address for I2C potentiometers

// Serial communication // 
const uint32_t SERIAL_BAUD_RATE = 115200;   // Serial baud rate.

// Potentiometer/rheostat object. // 
// Vulintus_MCP4131 pot(PIN_CS);    // Microchip MCP4131 single potentiometer, SPI, RAM memory, 7-bit
// Vulintus_MCP4132 pot(PIN_CS);    // Microchip MCP4132 single rheostat, SPI, RAM memory, 7-bit
// Vulintus_MCP4141 pot(PIN_CS);    // Microchip MCP4141 single potentiometer, SPI, EE memory, 7-bit
// Vulintus_MCP4142 pot(PIN_CS);    // Microchip MCP4142 single rheostat, SPI, EE memory, 7-bit
// Vulintus_MCP4151 pot(PIN_CS);    // Microchip MCP4551 single potentiometer, SPI, RAM memory, 8-bit
// Vulintus_MCP4152 pot(PIN_CS);    // Microchip MCP4152 single rheostat, SPI, RAM memory, 8-bit
// Vulintus_MCP4161 pot(PIN_CS);    // Microchip MCP4161 single potentiometer, SPI, EE memory, 8-bit
// Vulintus_MCP4162 pot(PIN_CS);    // Microchip MCP4162 single rheostat, SPI, EE memory, 8-bit
// Vulintus_MCP4231 pot(PIN_CS);    // Microchip MCP4231 Dual potentiometer, SPI, RAM memory, 7-bit
// Vulintus_MCP4232 pot(PIN_CS);    // Microchip MCP4232 Dual rheostat, SPI, RAM memory, 7-bit
// Vulintus_MCP4241 pot(PIN_CS);    // Microchip MCP4241 Dual potentiometer, SPI, EE memory, 7-bit
// Vulintus_MCP4242 pot(PIN_CS);    // Microchip MCP4242 Dual rheostat, SPI, EE memory, 7-bit
// Vulintus_MCP4251 pot(PIN_CS);    // Microchip MCP4251 Dual potentiometer, SPI, RAM memory, 8-bit
// Vulintus_MCP4252 pot(PIN_CS);    // Microchip MCP4252 Dual rheostat, SPI, RAM memory, 8-bit
// Vulintus_MCP4261 pot(PIN_CS);    // Microchip MCP4261 Dual potentiometer, SPI, EE memory, 8-bit
// Vulintus_MCP4262 pot(PIN_CS);    // Microchip MCP4261 Dual rheostat, SPI, E memory, 8-bit
// Vulintus_MCP4531 pot(I2C_ADDR);  // Microchip MCP4531 single potentiometer, I2C, RAM memory, 7-bit.
// Vulintus_MCP4532 pot(I2C_ADDR);  // Microchip MCP4532 single rheostat, I2C, RAM memory, 7-bit.
// Vulintus_MCP4541 pot(I2C_ADDR);  // Microchip MCP4541 single potentiometer, I2C, EE memory, 7-bit.
// Vulintus_MCP4542 pot(I2C_ADDR);  // Microchip MCP4542 single rheostat, I2C, EE memory, 7-bit.
// Vulintus_MCP4551 pot(I2C_ADDR);  // Microchip MCP4551 single potentiometer, I2C, RAM memory, 8-bit.
// Vulintus_MCP4552 pot(I2C_ADDR);  // Microchip MCP4552 single rheostat, I2C, RAM memory, 8-bit.
// Vulintus_MCP4561 pot(I2C_ADDR);  // Microchip MCP4561 single potentiometer, I2C, EE memory, 8-bit.
// Vulintus_MCP4562 pot(I2C_ADDR);  // Microchip MCP4562 single rheostat, I2C, EE memory, 8-bit.
Vulintus_MCP4631 pot(&Wire, I2C_ADDR);  // Microchip MCP4631 dual potentiometer, I2C, RAM memory, 7-bit. *
// Vulintus_MCP4632 pot(I2C_ADDR);  // Microchip MCP4632 dual rheostat, I2C, RAM memory, 7-bit.
// Vulintus_MCP4641 pot(I2C_ADDR);  // Microchip MCP4641 dual potentiometer, I2C, EE memory, 7-bit.
// Vulintus_MCP4642 pot(I2C_ADDR);  // Microchip MCP4642 dual rheostat, I2C, EE memory, 7-bit.
// Vulintus_MCP4651 pot(I2C_ADDR);  // Microchip MCP4651 dual potentiometer, I2C, RAM memory, 8-bit.
// Vulintus_MCP4652 pot(I2C_ADDR);  // Microchip MCP4652 dual rheostat, I2C, RAM memory, 8-bit.
// Vulintus_MCP4661 pot(I2C_ADDR);  // Microchip MCP4661 dual potentiometer, I2C, EE memory, 8-bit.
// Vulintus_MCP4662 pot(I2C_ADDR);  // Microchip MCP4662 dual rheostat, I2C, E memory, 8-bit.
const uint8_t wiper_i = 0;        // Wiper index, for multi-pot chips.


// INITIALIZATION ************************************************************// 
void setup() {

  // Initialize serial data transmission.
  Serial.begin(SERIAL_BAUD_RATE);
  while (!Serial);   

  // Initialize the potentiometer.
  pot.max_resistance = 10000;   // Maximum resistance, not counting the wiper (default is 10000).
  pot.wiper_resistance = 75;    // Wiper resistance (default is 75).
  if (pot.begin()) {            // If the potentiometer didn't connect...
    while (1) {
      Serial.println("Could not connect to potentiometer!");
      delay(5000);
    }
  }

  // analogReadResolution(12);
}


// MAIN LOOP *****************************************************************// 
void loop() {
  
  float resistance;                                 // Set the resistance as a float.
  for (uint8_t i = 0; i <= 8; i++) {                // Step through 8 resistance steps.
    resistance = pot.max_resistance;                // Grab the maximum resistance setting.
    resistance *= (float) i/8;                      // Scale the resistance to the current step.
    Serial.print("\nSETTING TARGET RESISTANCE: ");  // Print a message to the serial line.
    Serial.print(resistance,1);                     // Print the target resistance.
    Serial.println(" ohms");                        // Print the units.
    pot.set_resistance(resistance, wiper_i);        // Set the resistance.
    Serial.print("ACTUAL RESISTANCE: ");            // Print a message to the serial line.
    Serial.print(pot.get_resistance(wiper_i),1);    // Print the actual resistance.
    Serial.println(" ohms");                        // Print the units.
    Serial.print("pot.read(wiper_i) = ");
    Serial.println(pot.read(wiper_i));
    Serial.print("A3 = ");
    Serial.println(analogRead(A3));
    Serial.print("A4 = ");
    Serial.println(analogRead(A4));
    delay(5000);                                    // Pause for 5 seconds to get a good reading.
  }
  
}