#ifndef F_CPU
#define F_CPU 1000000UL
#endif

#include <avr/io.h>
#include <util/delay.h>

/* This uses the PWM mode of the timer/counter as a way to
 * dim and brighten the LED as controlled by the main loop.
 */

#define LED_PIN0 (1 << PB0)
#define LED_PIN1 (1 << PB1)

int main(void) {
  DDRB = LED_PIN1|LED_PIN0; // set 0 and 1 pins to output, default is input

  TCCR0B = 0b010; // div 8 prescaler (ref 11.9.3)
  TCCR0A = 0b10000101; // phase correct PWM mode (ref 11.9.2)

  /* silly "breathing LED" effect */
  while (1) {
    while (OCR0A < 0xf0) {
      OCR0A += 5;
      _delay_ms(30);
    }
    while (OCR0A > 0x20) {
      OCR0A -= 5;
      _delay_ms(30);
    }
  }    
}
