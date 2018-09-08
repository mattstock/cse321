#include <inttypes.h>

uint8_t * const registers = (uint8_t *)0x20;

#define PORTB (registers[0x18])
#define DDRB (registers[0x17])
#define PINB (registers[0x16])

int main() {
  DDRB = 1; // Pin 0 is output, rest are inputs
  while (1) {
    if (PINB & 0b10000) {
      PORTB &= ~1;
    } else {
      PORTB |= 1;
    }
  }
}
