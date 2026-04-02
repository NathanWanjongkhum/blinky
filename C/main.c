// AVR is a family of 8-bit and 32-bit RISC microcontrollers developed by Microchip Technology
// This example uses a Arduino R3
#include <avr/io.h>

// The MCU clock speed
#define F_CPU 16000000
// The delay in ms, the delay lib will then use the MCU clock speed
// versus the desired delay and calculates the amount of NOPs neccesary
// to satisfy the delay.
#define BLINK_DELAY_MS 500

#include <util/delay.h>

int main() {
  // Find the boards schematic and look for the microcontroller
  // The ATMEGA328P is the most common MCU for Arduino boards
  // The Arduino UNO R3 specifically has the ATMEGA328p-PU.

  // For a simple off-the-board example use male-to-male wires
  // and wire in series, any digital pin 8-13 from Port B, (these handle SPI and PWM outputs)
  // into the anaode (+) of the led then out the cathode (-) a resister (<100 Ohms for visibility) 
  // to avoid burnout. Then back into the GND pin, closing the circuit.

  // Macros from the AVR lib:
  // PORTB - The Port B Data Register. Stores each I/O pin as a bit in a 8-bit memory-mapped
  // register that controls output state (1-high | 0-low).
  // DDRB - The Port B Data Direction Register. When 1 makes the related pin "hot" (5V) 
  // so it is ready for output. While 0 readys it for input.
  
  // Arduino digital pin 8 (pin 0 on PORTB) for output
  // DDRB |= 0B000001; // PORTB8
  // Above is a bitwise OR assignment operator which is functionally equivalent to
  // DDRB = DDRB | 0B000001;
  // This word of 0 and 1s can be tedius to debug, recounting the correct bit is set
  // DDRB = DDRB | (1 << DDB0);
  // Above is a bitwise left shift operator of the PORTB0 macro, setting it to 1
  DDRB |= (1 << DDB0);
  // Is the cleneast solution since it would be read:
  // "For the Data Direction Register for Port B turn on Port B pin 0"
  // As mentioned, in this context "turn on" is setting the pin to output 

  // Common way to make an infinite loop in bare-metal for continouous operation
  while (1) {
    // Turn LED on
    // PORTB |= 0B000001;
    PORTB |= (1 << PORTB0);
    // "For the Port B Register turn on Port B pin 5"
    // As mentioned, in this context "turn on" is High
    
    _delay_ms(BLINK_DELAY_MS);

    // Turn LED off
    // PORTB &= ~0B000001;
    PORTB &= ~(1 << PORTB0);
    // Similar to turning on but this is subtle in that the
    // PORTB AND NOT (SET PORTB5 1)
    // See that logically this ignore all other bits and turns off the LED
    
    _delay_ms(BLINK_DELAY_MS);
  }
}
