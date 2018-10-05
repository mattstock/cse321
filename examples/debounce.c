#ifndef F_CPU
#define F_CPU 1000000UL
#endif

#include <avr/io.h>
#include <util/delay.h>

typedef enum { RELEASED=0, PRESSED } key_t;

#define LED_PIN0 (1 << PB0)
#define LED_PIN1 (1 << PB1)
#define KEY0     (1 << PB3)

int main(void) {
  uint8_t history = 0;
  key_t keystate = RELEASED;
  
  DDRB = LED_PIN1|LED_PIN0; // set 0 and 1 pins to output, default is input
  PORTB = 0;

  while (1) {
    // Get a sample of the key pin
    history = history << 1;
    if ((PINB & KEY0) == 0) // low if button is pressed!
      history = history | 0x1;
    
    // Update the key state based on the latest 6 samples
    if ((history & 0b111111) == 0b111111)
      keystate = PRESSED;
    if ((history & 0b00111111) == 0)
      keystate = RELEASED;
    
    // Turn on the LED based on the state
    if (keystate == PRESSED)
      PORTB = LED_PIN0;
    else
    PORTB = 0;
  }
}
