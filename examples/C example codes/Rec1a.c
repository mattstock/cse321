#include <stdio.h>
#include <stdint.h>


uint8_t a; //test with int //same as unsigned char
uint16_t b; //unsigned short
uint32_t c; //unsigned int
uint64_t d; //unsigned long long
uint32_t statusIO = 0;
volatile uint32_t volatilestatusIO = 0;
volatile uint32_t volatileStatusPtr = 0xE4321000; //volatileStatusPtr is pointing to a memory location at where the content may change
                                                  //at any point in time by some peripheral which may be unknown to the program. Making it volatile makes the compiler
                                                  // realize that it shouldn't perform optimization for this variable.
int main(){

    a= 'A';// try with 75
    b= 77;
    c = 78;
    d = 79;
    printf("%c %d %d %d",a,b,c,d); //instead of %c, try %d

    /* prints the same damn thing with uint8_t and int.
    So what is the use?
    - makes code far easier to read
    - helps in making code portable. One machine might interpret int as 16-bit and another as 32 bit.
    With stint.h you get what you type. If you use int8_t instead of char you know that it is a signed 8 bit variable.
    char can be signed and unsigned. Behavior is implementation-defined and varies across compiler. Using char as default
    can be dangerous when you are trying to make your code portable or use across a variety of devices.

    */

    /*------------------------------------------------------------------*/

    /* Volatile variable are used so that compilers do not do optimizations for those variables.

    - We use volatile when we are writing low level C code, especially when we are dealing with peripheral devices,
    IO ports (mainly memory mapped IO ports), Interrupt Service Routines (ISRs) which interact with Hardware.
    - At high levels compilers convert C code to machine code so that executables can run without the actual source code.
    - Compilers try to optimize output so that lesser Machine code needs to be executed.
    - In trying to optimize, compiler removes redundant machine code for a variable which does not change according to the compiler.
    - If compilers do that problems can occur when we are dealing with the status of IO operation.*/
    /*
    while(statusIO==0){
        /* while the status of the IO port is zero, keep doing something. If status changes do some other thing.
        this will be converted by compiler to while(1) and thus the purpose of the code is hampered.
    }*/

    /*
    while(volatilestatusIO){
     // this loop is accessed all the time.
    }

     */
}
