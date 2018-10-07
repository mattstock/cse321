#ifndef F_CPU
#define F_CPU 1000000UL
#endif

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/power.h>
#include <avr/sleep.h>

ISR(PCINT0_vect) {
  // In a real program, you'd do something interesting.
  // Here we just want the interrupt to wake us from sleep
  // Note that pin change is rise or fall (0 -> 1 and 1 -> 0)!
}

int main(void) {
  DDRB = 3;
  // Set the pin change mask so that PB3 triggers interrupt
  PCMSK = (1 << PCINT3);
  // enable pin change interrupts
  GIMSK = (1 << PCIE);
  // Set up sleep modes
  set_sleep_mode(SLEEP_MODE_IDLE);
  sleep_enable();
  // Set interrupt
  sei();
  // It will wait here until the interrupt wakes things up
  // In idle mode, we're at 0.67mA
  sleep_mode();
  // Wait 5s so we can see the wake current (1.5mA)
  _delay_ms(5000);
  // Fire up an LED so we see that current draw (52mA)
  // This likely means we're overdriving our I/O pins because we aren't
  // limiting the current.  Bad (but simple) design!
  PORTB = 1;
}
