#ifndef F_CPU
#define F_CPU 1000000UL
#endif

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define LED_PIN0 (1 << PB0)
#define LED_PIN1 (1 << PB1)
#define LED_PIN2 (1 << PB2)

#define SLOW 0x70
#define FAST 0x68

ISR(TIMER0_COMPA_vect) {
  PORTB = 0;
  // Add our interval to whatever the last value was
  OCR0A += SLOW;
}

ISR(TIMER0_COMPB_vect) {
  PORTB = LED_PIN1;
  OCR0B += FAST;
}

int main(void) {
  DDRB = LED_PIN1|LED_PIN0; // set 0 and 1 pins to output, default is input
  PORTB = 0; // both low == LEDs off

  OCR0A = SLOW;
  OCR0B = FAST;
  TCCR0B = 0b101; // no prescale

  // Enable the two timer0 comparator interrupts
  TIMSK = (1 << OCIE0A) | (1 << OCIE0B);

  sei();
  
  while (1);
}
