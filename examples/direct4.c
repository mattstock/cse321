#include <inttypes.h>

uint8_t * const registers = (uint8_t *)0x20;

#define PORTB (registers[0x18])

int main() {
  PORTB = 0x79;
  if (PORTB) {
    asm("nop");
  }
}
