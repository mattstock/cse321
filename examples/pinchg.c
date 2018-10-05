#include <avr/io.h>

/* This is an example of leveraging the timer/counter built in
 * features to toggle an output pin when a fixed time elapses.
 */
#define LED_PIN0 (1 << PB0)
#define LED_PIN1 (1 << PB1)

int main(void) {
  DDRB = LED_PIN1|LED_PIN0; // set 0 and 1 pins to output, default is input
  
  OCR0A = 0x40; // a somewhat arbitrary TOP value
  TCCR0B = 0b101; // div 1024 prescaler
  TCCR0A = 0b01000010; // toggle pins on and clear timer on match (TOP)
  
  while (1); // look ma, no code!
}
