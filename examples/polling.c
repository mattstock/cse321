#include <avr/io.h>

#define LED_PIN0 (1 << PB0)
#define LED_PIN1 (1 << PB1)
#define LED_PIN2 (1 << PB2)

#define SLOW 0xff
#define FAST 0xf8

/* example of how we'd use timer0 without interrupts.
 * timer0 is documented in chapter 11 on the datasheet.
 */

int main(void) {
  uint8_t slow;
  uint8_t fast;

  DDRB = LED_PIN1|LED_PIN0; // set 0 and 1 pins to output, default is input
  PORTB = 0; // both low == LEDs off
  
  TCCR0B = 0b101; // no prescale

  slow = TCNT0 + SLOW;
  fast = TCNT0 + FAST;
  
  while (1) {
    if (slow == TCNT0) {
      PORTB ^= LED_PIN1;
      slow += SLOW;
    }
    if (fast == TCNT0) {
      PORTB ^= LED_PIN0;
      fast += FAST;
    }
  }
}
