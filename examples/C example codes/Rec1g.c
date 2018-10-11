#include <stdio.h>

void printBits(unsigned num)
{
    unsigned int i;
    for (i = 1 << 31; i > 0; i = i / 2){

        (num & i)? printf("1"): printf("0");
        /*if(num & i){ //the same meaining as line above
        	printf("1");
        }
        else
        	printf("0");*/
    }
    printf("\n");
}

int main(){
	unsigned int x ,y; 
	scanf("%u %u",&x,&y); 
    printf("x = "); printBits(x); 
    printf("y = "); printBits(y);
    printf("x&y = "); printBits(x&y); 
    printf("x|y = "); printBits(x|y);  
    printf("x^y = "); printBits(x^y); 
    printf("~x = "); printBits(~x);   
    printf("x<<2 = "); printBits(x<<2);   
    printf("x>>2 = "); printBits(x>>2);   
    
    return 0;

}