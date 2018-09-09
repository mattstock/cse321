#include <inttypes.h>

volatile uint8_t * const registers = (uint8_t *)0x20;

#define PORTB (registers[0x18])
#define DDRB (registers[0x17])
#define PINB (registers[0x16])

int main() {
  DDRB = 1; // Pin 0 is output, rest are inputs

  while (1) {
    if (PINB & 0b10000) { // Check if Pin 4 is high
      PORTB &= 0b11111110; // clear Pin 0
      // PORTB &= 254; // these are all equivalent
      // PORTB &= 0xfe;
      // PORTB &= ~1; // invert happens at compile time
    } else {
      PORTB |= 1; // set pin 0 
    }
  }
}
