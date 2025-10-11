#include <stdio.h>
#include <string.h>
#include "test.h"
#include "../include/fabric_image.h"

void test_allocate_image_base() {
	ImageBase base = allocate_image_base(150, 140, "P1");
	printf("%d\n", base.hight == 150);
	printf("%d\n", base.width == 140);
	printf("%d\n", strcmp(base.magic_number, "P1") == 0);
}

void test_allocate_image_pbm() {
	ImagePBM image = allocate_image_pbm(150, 140);
	printf("%d\n", image.base.hight == 150);
	printf("%d\n", image.base.width == 140);
	printf("%d\n", strcmp(image.base.magic_number, "P1") == 0);
	int true = 1;
	for(int i = 0; i < image.base.hight; i++) {
		for(int j = 0; j < image.base.width; j++) {
			if(image.data[i][j] != 0) {
				true = 0;
			}
		}
	}
	printf("%d\n", true);
} 

void test_allocate_image_pgm() {
	ImagePGM image = allocate_image_pgm(100, 50, 255);
	printf("%d\n", image.base.hight == 100);
	printf("%d\n", image.base.width == 50);
	printf("%d\n", strcmp(image.base.magic_number, "P2") == 0);
	printf("%d\n", image.max_gray_value == 255);
	int true = 1;
	for(int i = 0; i < image.base.hight; i++) {
		for(int j = 0; j < image.base.width; j++) {
			if(image.data[i][j] != 0) {
				true = 0;
			}
		}
	}
	printf("%d\n", true);
}

void test_allocate_image_ppm() {
	ImagePPM image = allocate_image_ppm(50, 100, 255);
	printf("%d\n", image.base.hight == 50);
	printf("%d\n", image.base.width == 100);
	printf("%d\n", strcmp(image.base.magic_number, "P3") == 0);
	printf("%d\n", image.max_color_value == 255);
	int true = 1;
	for(int i = 0; i < image.base.hight; i++) {
		for(int j = 0; j < image.base.width; j++) {
			if(image.pixels[i][j].r != 0) {
				true = 0;
			}
			if(image.pixels[i][j].g != 0) {
				true = 0;
			}
			if(image.pixels[i][j].b != 0) {
				true = 0;
			}
		}
	}
	printf("%d\n", true);
}

void  test_save_image_pbm() {
	//ImagePBM image, char * path
	ImagePBM image = allocate_image_pbm(3, 3);
	for(int i = 0; i < 3; i++) {
		for(int j = 0; j < 3; j++) {
			image.data[i][j] = i % 2;
		}
	}
	printf("%d\n", save_image_pbm(image, "./tests/tmp/test_save_pbm.ppm") == 1);
}

int main(void) {
	display_start_of_test("tests fabric image");
	test_allocate_image_base();
	test_allocate_image_pbm();
	test_allocate_image_pgm();
	test_allocate_image_ppm();
	test_save_image_pbm();
	display_end_of_test();
	return 0;
}
