#include <stdio.h>
#include "test.h"

void display_start_of_test(char * text) {
	printf("----------");
	printf("%s", text);
	printf("----------\n");
}

void display_end_of_test() {
	printf("----------End of test----------\n");
}
