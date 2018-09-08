#include <inttypes.h>

uint8_t * const DDRB = (uint8_t *)0x37;
int main() {
  *DDRB = 0xaa;
}
