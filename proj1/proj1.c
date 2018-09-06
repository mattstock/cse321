#include <stdio.h>
#include <stdint.h>

/*
 * Project 1: Test skills with bitwise operators.
 *
 * Given an array of 8-bit 3-tuples as input, print out various outputs.
 * To accomplish, you need to implement the following functions:
 *
 * 1. reverse()
 * 2. clearbits()
 * 3. shift()
 * 4. binaryPrint()
 * 5. getTestCount()
 *
 * The description of what each function eneds to do is provided in the
 * comments above the function stub.
 *
 * The main() function should be left unchanged.  If all works as expected,
 * the result of the program should match what is in reference.txt.
 */

struct ntuple {
  uint8_t core;
  uint8_t mask;
  int8_t shift;
};

const struct ntuple inputs[] = {
  { 0x01, 0x0f, 3 },
  { 0x42, 0xf0, -2 },
  { 0x03, 0xaa, 0 },
  { 0xff, 0xf0, -7 },
  { 0xe3, 0xbc, 7 },
  { 0x7d, 0x00, -2 },
  { 0x88, 0x00, 8 },
  { 0xaa, 0x00, 2 },
  { 0x01, 0xaa, 3 },
  { 0x01, 0xcc, 3 },
  { 0xbb, 0xff, 2 },
  { 0xcc, 0x67, 4 },
  { 0x00, 0x32, 2 }  
};

/* Take a value x and reverse the order of the bits. */
uint8_t reverse(uint8_t x) {
}

/* For all of the one bits in mv, clear the corresponding bits in val and
 * return the result. */
uint8_t clearbits(uint8_t val, uint8_t mv) {
}

/* Shift val the number of bits provided by sv.  If sv is positive, shift left.
 * If sv is negative, logically shift right the absolute value. */
uint8_t shift(uint8_t val, int8_t sv) {
}

/* Print out the value val in string form to standard output.  Assume big
 * endian.
 */
void binaryPrint(uint8_t val) {
}

/* Calculate and return the number of test values in the input array.
 * Assume that additional values could be added or removed, so don't just
 * return a constant 13!
 */
int getTestCount() {
}

int main(int argc, char **argv) {
  int n = getTestCount();

  printf("size is %d\n", n);

  for (int i=0; i < n; i++) {
    printf("%02x: ", inputs[i].core);
    binaryPrint(inputs[i].core);
    printf(" ");
    binaryPrint(reverse(inputs[i].core));
    printf(" ");
    binaryPrint(clearbits(inputs[i].core, inputs[i].mask));
    printf(" ");
    binaryPrint(shift(inputs[i].core, inputs[i].shift));
    printf("\n");
  }
  return 0;
}
