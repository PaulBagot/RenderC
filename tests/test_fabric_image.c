#include <stdio.h>
#include <string.h>
#include "../src/fabric_image.c"

void test_allocate_image_base() {
	ImageBase base = allocate_image_base(150, 140, "P1");
	printf("%d\n", base.hight == 150);
	printf("%d\n", base.width == 140);
	printf("%d\n", strcmp(base.magic_number, "P1") == 0);
}

void test_allocate_image_pbm() {
	
} 

int main(void) {
	printf("tests fabric image :\n");
	test_allocate_image_base();
	test_allocate_image_pbm();
	return 0;
}
