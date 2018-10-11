#include <stdio.h>
#include <stdint.h>


int main(){
// testValue
unsigned long long val     = 0xFFFFFFFFFFFFFFFF; // 18446744073709551615

// 1 byte -> 0 to 2^8 -1 [0x00-0xFF]
uint8_t         unint8     = val;
unsigned char    unChar    = val;

printf("%u %u\n",uint8,unChar); //255
// 2 bytes -> 0 to 2^16 -1 [0x0000-0xFFFF]
uint16_t         uint16     = val;
unsigned short    unShort    = val;

printf("%u %u\n",uint16,unShort); //65535
// 4 bytes -> 0 to 2^32 -1 [0x00000000-0xFFFFFFFF]
uint32_t         uint32     = val;
unsigned int     unInt    = val;

printf("%u %u\n",uint32,unInt); // 4294967295
 // 8 bytes -> 0 to 2^64 -1  [0x0000000000000000-0xFFFFFFFFFFFFFFFF]
uint64_t             uint64         = val;
unsigned long long     uLongLong    = val;

printf("%llu %llu\n",uint64,uLongLong); // 18446744073709551615

}
//help: https://www.geeksforgeeks.org/
