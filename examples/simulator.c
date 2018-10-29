#ifndef F_CPU
#define F_CPU 1000000UL
#endif

#include <avr/io.h>
#include <util/delay.h>

#define LED_PIN0 (1 << PB0)
#define LED_PIN1 (1 << PB1)
#define LED_PIN2 (1 << PB2)

#include <simavr/avr/avr_mcu_section.h>
AVR_MCU(F_CPU, "attiny85");
AVR_MCU_VCD_FILE("simple.vcd", 1000);

const struct avr_mmcu_vcd_trace_t _mytrace[] _MMCU_ = {
	{ AVR_MCU_VCD_SYMBOL("DDRB"), .what = (void*)&DDRB, },
	{ AVR_MCU_VCD_SYMBOL("PORTB"), .what = (void*)&PORTB, }
};

int main(void) {
  // set 0 and 1 pins to output, default is input
  DDRB = LED_PIN1|LED_PIN0;

  // PB1 output is high, current flows from that pin, via yellow to PB0
  PORTB = LED_PIN1;
  
  while (1) {
    PORTB ^= LED_PIN1|LED_PIN0;
    _delay_ms(200);
  }
}
