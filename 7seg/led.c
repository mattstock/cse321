#ifndef F_CPU
#define F_CPU 8000000UL
#endif

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define DISPLAY_SIZE 16

/*
 * Firmware v2.0 for 7seg SPI display.
 *
 * Instructions are of the form RW DD VVVV
 * RW = 0x00 is read, 0x01 is write
 * DD = digit (0-DISPLAY_SIZE)
 * VVV0 = display value, low 6 bits always 0
 *
 * Value bits:          15 
 *                    10  14
 *                       9
 *                    11  13
 *                      12    8 (dp)
 * 
 * bit 7 tick (future)
 * bit 6 colon (shared for row)
 */
 
unsigned short num2seg(unsigned char dig);

// digit we are displaying
volatile unsigned char digit = 0;
// SPI I/O state machine
volatile unsigned char spistate = 0;
// address of digit for SPI
volatile unsigned char addr;
// direction of current SPI operation
volatile unsigned char rw;
// display values
unsigned short values[DISPLAY_SIZE];

ISR(SPI_STC_vect) {
  TCNT1 = 0; // reset the timer watchdog  
  switch (spistate) {
  case 0: // direction byte
    rw = (SPDR != 0);
    spistate = 1;
    break;
  case 1: // R: prep high byte, W: nothing;
    addr = SPDR;
    if (addr >= DISPLAY_SIZE) {
      SPDR = 0xff;
      spistate = 0;
    } else {
      spistate = 2;
      if (!rw)
	SPDR = values[addr] >> 8;
    }
    break;
  case 2: // R: prep low byte, W: fetch high byte
    if (!rw) {
      SPDR = values[addr] && 0xff;
    } else
      values[addr] = SPDR << 8;
    spistate = 3;
    break;
  case 3: // R: prep junk, W: fetch low byte
    if (!rw)
      SPDR = 0xa4;
    else
      values[addr] |= SPDR;
    spistate = 0;
    break;
  }
}

inline void led_enable() {
  PORTB &= 0x3f;
}

inline void led_disable() {
  PORTB |= 0x80;
}

inline void led_latch() {
  PORTC |= 0x80;
  PORTC &= 0x3f;
}

inline void led_clock() {
  PORTC |= 0x20;
  PORTC &= 0xdf;
}

inline void led_data(unsigned char state) {
  PORTC = (state ? PORTC | 0x10 : PORTC & 0xef);
}

// take 16 bits as input, and push to the tlc6c5912 (12 bits)
void bitbang(unsigned short value) {
  int i;

  // 4 low order bits are padding to get nice byte alignment.
  // We can throw them away.
  value >>= 4;

  // "Bit Bang" the remaining 12 bits into the shift register.
  for (i=0; i < 12; i++) {
    led_data(value & 0x1);
    value >>= 1;
    led_clock();
  }
  led_latch();
}


ISR(TIMER0_COMPA_vect) {
  digit = (digit+1)%DISPLAY_SIZE;
}

// ABCDEF coded output for testing.
unsigned short num2seg(unsigned char dig) {
  switch (dig) {
  case 0: return 0b1111110000000000;
  case 1: return 0b0110000000000000;
  case 2: return 0b1101101000000000;
  case 3: return 0b1111001000000000;
  case 4: return 0b0110011000000000;
  case 5: return 0b1011011000000000;
  case 6: return 0b1011111000000000;
  case 7: return 0b1110000000000000;
  case 8: return 0b1111111000000000;
  case 9: return 0b1111011000000000;
  case 10: return 0b1110111000000000;
  case 11: return 0b0011111000000000;
  case 12: return 0b0001101000000000;
  case 13: return 0b0111101000000000;
  case 14: return 0b1001111000000000;
  case 15: return 0b1000111000000000;
  }
  return 0b0;
}

int main(void) {
  int i;
  unsigned char old_digit = 255;
  
  /*
   * Data direction registers.  1 is output, 0 is input.
   * We need to be careful about which pins we choose, since many of them
   * serve multiple purposes.  We need the SPI pins for example.
   */
  DDRA = 0b00001111; // digits 8-11
  DDRB = 0b11010011; // colons, tick, SPI, and enable
  DDRC = 0b10111111; // latch out, clock, digits 12-15
  DDRD = 0b11111111; // digits 0-7

  /* The actual outputs we are turning on during initialization. */
  PORTA = 0x00;
  PORTB = 0x40;
  PORTC = 0x00;
  PORTD = 0x01;

  // SPI control register p126
  SPCR = 0b11000000; // slave mode, msb, enable SPI interrupt, mode0
 
  // timer 0 - display strobe
  // OCRA is top, IOclk/64, and since IOclk == 8Mhz, this is 125Khz
  TCCR0A = 0b1011;
  // Output compare A, which is used as the top of the counting range
  OCR0A = 0x60;
  // enable OCIE0A interrupt
  TIMSK0 = 0b10;  
  // enable interrupts (SPI and timer0)
  sei();

  // Write version 2.0 on boot
  for (i=0; i < DISPLAY_SIZE; i++)
    values[i] = 0;
  values[0] = num2seg(2) | 0x100;
  values[1] = num2seg(0);

  // Main loop
  while (1) {
    /*
     * If we see that the slave select is released, we make sure we
     * reset the state machine.  This implies that we need to have a
     * whole message within a single transmission.
     */
    if (PINB & 0x4)
      spistate = 0;
    
    // If the strobe timer changed, we need to refresh.
    if (digit != old_digit) {
      old_digit = digit;
      led_disable();
      bitbang(values[digit]);
      if (digit < 8) {
	PORTB &= 0xfc;
	PORTB |= 0x01;
	PORTC &= 0xf0;
	PORTD = (1 << digit);
      } else if (digit < 12) {
	PORTA = 1 << (digit - 8);
	PORTB &= 0xfc;
	PORTB |= 0x02;
	PORTD = 0x00;
      } else {
	PORTA = 0x00;
	PORTC &= 0xf0;
	PORTC |= 1 << (digit - 12);
      }
      led_enable();
    }
  }
}
