
#include <stdio.h>


//enum is a user defined data type in C. It is used to assign names to constants. It makes reading easier and the code more compact
typedef enum {Mon,Tue,Wed,Thurs,Fri,Sat,Sun}daysOfWeek;

int main(){

	daysOfWeek day = Thurs;
	printf("%d\n", day);
}


/*
enum daysOfWeek{Mon,Tue,Wed,Thurs,Fri,Sat,Sun};

int main(){

	enum daysOfWeek day = Thurs;
	printf("%d\n", day);
}
*/
