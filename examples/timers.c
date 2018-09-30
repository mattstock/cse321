#ifndef F_CPU
#define F_CPU 1000000UL
#endif

#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <avr/interrupt.h>

#define LED_PIN0 (1 << PB0)
#define LED_PIN1 (1 << PB1)
#define LED_PIN2 (1 << PB2)

#define SLOW 0xff

ISR(TIMER0_COMPA_vect) {
  // Toggle the pin
  PORTB ^= LED_PIN0|LED_PIN1;
  // Add our interval to whatever the last value was
  OCR0A += SLOW;
}

int main(void) {
  DDRB = LED_PIN1|LED_PIN0; // set 0 and 1 pins to output, default is input
  PORTB = LED_PIN0;

  OCR0A = SLOW;
  TCCR0B = 0b101; // no prescale

  // Enable the timer0 comparator a interrupt
  TIMSK = (1 << OCIE0A);

  sei();
  
  while (1) {
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
  }
}
