// AVR is a family of 8-bit and 32-bit RISC microcontrollers developed by Microchip Technology
// This example uses a Arduino R3
#include <avr/io.h>
#include <avr/interrupt.h>

// The MCU clock speed
#define F_CPU 16000000

ISR (TIMER1_OVF_vect)
{
  PORTB ^= _BV(PORTB0);
  TCNT1 = 65535 - (F_CPU / 1024);
}

int main() {
  DDRB |= _BV(DDB0);

  // Max value of 65535
  TCNT1 = 65535 - (F_CPU / 1024);

  // set the prescaler to 1024
  // 16M/1024 = 15625Hz

  TCCR1B = (1 << CS10) | (1 << CS12);

  TCCR1A = 0x00;

  TIMSK1 = (1 << TOIE1);

  sei();
  
  while (1) {
    ;;
  }
}
