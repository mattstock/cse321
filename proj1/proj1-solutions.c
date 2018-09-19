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
 * the result of the program shoudl match what is in validate.txt.
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

/* Arbitrary power of two width reversal. */
uint8_t reverseN(unsigned int x, unsigned int width) {
  unsigned int shift;
  unsigned int mask;

  if (width == 1)
    return x;

  shift = width/2;
  mask = (1 << shift)-1;
  
  return (reverseN(x & mask, shift) << shift)
    | reverseN((x >> shift) & mask, shift);
}

// Treat it like a stream of bits.
uint8_t reverseStream(uint8_t x) {
  uint8_t res;

  for (int i=0; i < 8; i++) {
    res <<= 1;
    res |= (x & 1);
    x >>= 1;
  }
  return res;
}

/* Efficient for 8 bits. */
uint8_t lut(uint8_t x) {
  switch (x&0xf) {
  case 0x0: return 0x0;
  case 0x1: return 0x8;
  case 0x2: return 0x4;
  case 0x3: return 0xc;
  case 0x4: return 0x2;
  case 0x5: return 0xa;
  case 0x6: return 0x6;
  case 0x7: return 0xe;
  case 0x8: return 0x1;
  case 0x9: return 0x9;
  case 0xa: return 0x5;
  case 0xb: return 0xd;
  case 0xc: return 0x3;
  case 0xd: return 0xb;
  case 0xe: return 0x7;
  case 0xf: return 0xf;
  }
}

uint8_t lutTable[] = { 0x0, 0x8, 0x4, 0xc,
		       0x2, 0xa, 0x6, 0xe,
		       0x1, 0x9, 0x5, 0xd,
		       0x3, 0xb, 0x7, 0xf };

uint8_t reverseL(uint8_t x) {
  return lutTable[x & 0xf] << 4 | lutTable[x >> 4];
}

/* Take a value x and reverse the order of the bits. */
uint8_t reverse(uint8_t x) {
  uint8_t v = x >> 7;
  v |= (x & 0x40) >> 5;
  v |= (x & 0x20) >> 3;
  v |= (x & 0x10) >> 1;
  v |= x << 7;
  v |= (x & 0x2) << 5;
  v |= (x & 0x4) << 3;
  v |= (x & 0x8) << 1;
  // return v;
  //return reverseN(x, 8);
  //return reverseL(x);
  return reverseStream(x);
}

/* For all of the one bits in mv, clear the corresponding bits in val and
 * return the result. */
uint8_t clearbits(uint8_t val, uint8_t mv) {
  return val&(~mv);
}

/* Shift val the number of bits provided by sv.  If sv is positive, shift left.
 * If sv is negative, logically shift right the absolute value. */
uint8_t shift(uint8_t val, int8_t sv) {
  if (sv < 0) {
    sv = -sv;
    return val >> sv;
  }
  return val << sv;
}

/* Another look up table example */
const char * const binL[] = { "0000", "0001", "0010", "0011",
			      "0100", "0101", "0110", "0111",
			      "1000", "1001", "1010", "1011",
			      "1100", "1101", "1110", "1111" };

/* Print out the value val in string form to standard output.  Assume big
 * endian.
 */
void binaryPrint(uint8_t val) {
  printf("%s%s", binL[val >> 4], binL[val & 0xf]);
}

/* Calculate and return the number of test values in the input array.
 * Assume that additional values could be added or removed, so don't just
 * return a constant 13!
 */
int getTestCount() {
  return sizeof(inputs)/sizeof(struct ntuple);
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
