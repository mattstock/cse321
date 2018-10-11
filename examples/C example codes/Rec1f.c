#include "Rec1f.h"
#include <stdio.h>

inline int square(int x){
	return x*x;
}
inline void PrintValue(int x, int y){

	printf("x = %d , y=%d\n",x,y);
}
int main(){
	int x,y;
	scanf("%d",&x);
	Print(x);
	x = square(x);
	printf("----squaring the value of input x with inline function---\n");
	Print(x);
	y = 10;
	printf("The value of y is %d\n",y);
	SWAP(x,y);
	printf("---swaping the value of x with y using SWAP macro included \nin seperated header file----\n");
	PrintValue(x,y);
	return 0;
}