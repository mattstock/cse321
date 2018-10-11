#include <stdio.h>
#include <stdlib.h>

int main(){

	int input;
	scanf("%d",&input);

	switch(input){

		case 0:
			printf("The input is zero\n");
			break;
		case 1:
			printf("The input is one\n");
			break;
		case 2:
			printf("The input is two\n");
			//break;
		case 3:
			printf("The input is three\n");
			break;
		default:
			printf("default value\n");
	}
}