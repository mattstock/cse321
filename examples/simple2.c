#ifndef F_CPU
#define F_CPU 1000000UL
#endif

#include <avr/io.h>
#include <util/delay.h>

#define LED_PIN0 (1 << PB0) //0b00000001
#define LED_PIN1 (1 << PB1) //0b00000010
#define LED_PIN2 (1 << PB2) //0b00000100

int main(void) {
  // set 0 and 1 pins to output, default is input


  DDRB = LED_PIN0 | LED_PIN1;
  //DDRB = (1 << DDB0) | (1 << DDB1)
  // PB1 and PB2 both are high. So no potential difference. LEDs do not light up.
  PORTB = LED_PIN0|LED_PIN1 ;

  while (1) {
    // busy wait for 1s, based on the clock described above
    //PORTB = LED_PIN1;
    _delay_ms(1000);
    //PORTB = LED_PIN0;
    // swap current source and sink, causing yellow and green to toggle
    PORTB ^= LED_PIN0|LED_PIN1;

  }
}
