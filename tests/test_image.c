#include <stdio.h>
#include <string.h>
#include "test.h"
#include "../include/image.h"

void test_allocate_image_base() {
	printf("#%s\n", __func__);
	ImageBase base;
	printf("%d\n", allocate_image_base(&base, 0, 0, "P1") == 0);
	printf("%d\n", allocate_image_base(&base, 0, 1, "P1") == 0);
	printf("%d\n", allocate_image_base(&base, 1, -1, "P1") == 0);
	printf("%d\n", allocate_image_base(&base, 150, 140, "P1") == 1);
	printf("%d\n", base.hight == 150);
	printf("%d\n", base.width == 140);
	printf("%d\n", strcmp(base.magic_number, "P1") == 0);
}

void test_allocate_image_pbm() {
	printf("#%s\n", __func__);
	ImagePBM image;
	printf("%d\n", allocate_image_pbm(&image, 150, 140) == 1);
	printf("%d\n", image.base.hight == 150);
	printf("%d\n", image.base.width == 140);
	printf("%d\n", strcmp(image.base.magic_number, "P1") == 0);
	int test = 1;
	for(int i = 0; i < image.base.hight; i++) {
		for(int j = 0; j < image.base.width; j++) {
			if(image.data[i][j] != 0) {
				test = 0;
			}
		}
	}
	printf("%d\n", test);
} 

void test_allocate_image_pgm() {
	printf("#%s\n", __func__);
	ImagePGM image;
	printf("%d\n", allocate_image_pgm(&image, 100, 50, 255) == 1);
	printf("%d\n", image.base.hight == 100);
	printf("%d\n", image.base.width == 50);
	printf("%d\n", strcmp(image.base.magic_number, "P2") == 0);
	printf("%d\n", image.max_gray_value == 255);
	int test = 1;
	for(int i = 0; i < image.base.hight; i++) {
		for(int j = 0; j < image.base.width; j++) {
			if(image.data[i][j] != 0) {
				test = 0;
			}
		}
	}
	printf("%d\n", test);
}

void test_allocate_image_ppm() {
	printf("#%s\n", __func__);
	ImagePPM image;
	printf("%d\n", allocate_image_ppm(&image, 50, 100, 255) == 1);
	printf("%d\n", image.base.hight == 50);
	printf("%d\n", image.base.width == 100);
	printf("%d\n", strcmp(image.base.magic_number, "P3") == 0);
	printf("%d\n", image.max_color_value == 255);
	int test = 1;
	for(int i = 0; i < image.base.hight; i++) {
		for(int j = 0; j < image.base.width; j++) {
			if(image.pixels[i][j].r != 0) {
				test = 0;
			}
			if(image.pixels[i][j].g != 0) {
				test = 0;
			}
			if(image.pixels[i][j].b != 0) {
				test = 0;
			}
		}
	}
	printf("%d\n", test);
}

void  test_save_image_pbm() {
	printf("#%s\n", __func__);
	ImagePBM image;
	allocate_image_pbm(&image, 3, 3);
	for(int i = 0; i < 3; i++) {
		for(int j = 0; j < 3; j++) {
			image.data[i][j] = i % 2;
		}
	}
	printf("%d\n", save_image_pbm(image, "./tests/tmp/test_save_pbm.ppm") == 1);
}

int main(void) {
	display_start_of_test("tests image");
	test_allocate_image_base();
	test_allocate_image_pbm();
	test_allocate_image_pgm();
	test_allocate_image_ppm();
	test_save_image_pbm();
	display_end_of_test();
	return 0;
}
