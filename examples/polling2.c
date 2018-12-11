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
// timer runs very fast
int main(void) {
  uint8_t slow;

  DDRB = LED_PIN1|LED_PIN0; // set 0 and 1 pins to output, default is input
  PORTB = LED_PIN0;

  //TCCR: Timer/Counter control register
  // prescale by 64 ; as a result timer runs really fast. We cannot observe the switch.

  TCCR0B = 0b011; 
//TCNT: Timer/Counter
  slow = TCNT0 + SLOW;

  while (1) {
    if (slow == TCNT0) {
      PORTB ^= LED_PIN1|LED_PIN0;
      slow += SLOW;
    }
#ifdef BUSY
    switch (rand() % 4) {
    case 0:
      _delay_ms(1000);
    case 1:
      _delay_ms(1000);
    case 2:
      _delay_ms(1000);
    case 3:
      _delay_ms(1000);
    }
#endif
  }
}
