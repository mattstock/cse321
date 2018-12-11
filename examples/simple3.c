#ifndef F_CPU
#define F_CPU 1000000UL
#endif

#include <avr/io.h>
#include <util/delay.h>

#define LED_PIN0 (1 << PB0) //0b00000001
#define LED_PIN1 (1 << PB1) //0b00000010
#define LED_PIN2 (1 << PB2) //0b00000100

// SWITCHING BETWEEN GREEN AND RED LED
//carefully look at the board diagram.
int main(void) {
  // set 0,1,2 pins to output, default is input
  DDRB = LED_PIN1|LED_PIN2|LED_PIN0;
  // PB1 output is high, current flows from that pin, via yellow to PB0
  PORTB = LED_PIN0;

  while (1) {
    // busy wait for 1s, based on the clock described above
    //PORTB = LED_PIN1;
    _delay_ms(1000);
    //PORTB = LED_PIN0;
    // swap current source and sink, causing yellow and green to toggle

    PORTB ^= LED_PIN0|LED_PIN2;
  }
}
