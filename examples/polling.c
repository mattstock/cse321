#ifndef F_CPU
#define F_CPU 1000000UL
#endif

#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>

#define LED_PIN0 (1 << PB0)
#define LED_PIN1 (1 << PB1)
#define LED_PIN2 (1 << PB2)

#define SLOW 0x90

/* example of how we'd use timer0 without interrupts.
 * timer0 is documented in chapter 11 on the datasheet.
 */

int main(void) {
  uint8_t slow;

  DDRB = LED_PIN1|LED_PIN0; // set 0 and 1 pins to output, default is input
  PORTB = LED_PIN0;
  
  TCCR0B = 0b101; // prescale by 1024

  slow = TCNT0 + SLOW;

  while (1) {
    if (slow == TCNT0) {
      PORTB ^= LED_PIN1|LED_PIN0;
      slow += SLOW;
    }
#ifdef BUSY
    switch (rand() % 4) {
    case 0:
      _delay_ms(10);
    case 1:
      _delay_ms(10);
    case 2:
      _delay_ms(10);
    case 3:
      _delay_ms(10);
    }
#endif
  }
}
