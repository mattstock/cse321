#include <avr/io.h>

#define LED_PIN0 (1 << PB0)
#define LED_PIN1 (1 << PB1)
#define KEY_PIN0 (1 << PB3)

// version of the sw-led program using the proj 2 hardware.
// If the button is pressed, the LED will turn on.

int main(void) {
  // set PB0 and PB1 pins to output, default is input (high-Z)
  DDRB = LED_PIN1|LED_PIN0;
  // both low means no current flows and LEDs are off
  PORTB = 0;

  while (1) {
    PORTB = (PINB & KEY_PIN0 ? 0 : LED_PIN0);

    /* This is identical code as above:
         if (PINB & KEY_PIN0)
           PORTB = 0;
         else
           PORTB = LED_PIN0;
    */
  }
}
