#include <inttypes.h>

uint8_t * const registers = (uint8_t *)0x20;
#define DDRB (registers[0x17])
#define PORTB (registers[0x18])

int main() {
  DDRB = 0xaa;
  PORTB = 0x79;
}
