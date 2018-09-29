#ifndef F_CPU
#define F_CPU 1000000UL
#endif

#include <avr/io.h>
#include <util/delay.h>

#define LED_PIN0 (1 << PB0)
#define LED_PIN1 (1 << PB1)
#define LED_PIN2 (1 << PB2)

int main(void) {
  DDRB = LED_PIN1|LED_PIN0; // set 0 and 1 pins to output, default is input

  PORTB = LED_PIN1;
  
  while (1) {
    _delay_ms(1000);
    PORTB ^= LED_PIN1|LED_PIN0;
  }
}
