#include <avr/io.h>

#define LED_PIN0 (1 << PB0)
#define LED_PIN1 (1 << PB1)

int main(void) {
  DDRB = LED_PIN1|LED_PIN0; // set 0 and 1 pins to output, default is input

  OCR0A = 0x50;
  TCCR0B = 0b010; // div 8 prescaler
  TCCR0A = 0b10000101; // phase correct PWM

  while (1);
    
}
