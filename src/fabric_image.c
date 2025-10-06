#include "../include/fabric_image.h"
#include <stdlib.h>
#include <stdio.h>

ImageBase allocate_image_base(int hight, int width, char magic_number[2]) {
	
	ImageBase base;
	base.magic_number = malloc(sizeof(char) * 2);
	base.magic_number = magic_number;
	base.hight = hight;
	base.width = width;
	
	return base;
}

ImagePBM allocate_image_pbm(int hight, int width) {
	
	ImagePBM new_image;
	new_image.base = allocate_image_base(hight, width, "P1");
	new_image.data = malloc(sizeof(int*) * hight);
	
	for(int i = 0; i < hight; i++) {
		new_image.data[i] = malloc(sizeof(int) * width);
	}
	return new_image;
}

ImagePGM allocate_image_pgm(int hight, int width, int max_gray_value) {
	
	ImagePGM new_image;
	new_image.base = allocate_image_base(hight, width, "P2");
	new_image.max_gray_value = max_gray_value;
	new_image.data = malloc(sizeof(int*) * hight);
	
	for(int i = 0; i < hight; i++) {
		new_image.data[i] = malloc(sizeof(int) * width);
	}
	return new_image;
}

ImagePPM allocate_image_ppm(int hight, int width, int max_color_value) {

	ImagePPM new_image;
	new_image.base = allocate_image_base(hight, width, "P3");
	new_image.max_color_value = max_color_value;
	new_image.pixels = malloc(sizeof(Pixel*) * hight);
	
	for(int i = 0; i < hight; i++) {
		new_image.pixels[i] = malloc(sizeof(Pixel) * width);
		for(int j = 0; j < width; j++) {
			Pixel new_pixel;
			new_pixel.r = 0;
			new_pixel.g = 0;
			new_pixel.b = 0;
			new_image.pixels[i][j] = new_pixel;
		}
	}
	return new_image;
}

int save_image_pbm(ImagePBM image, char * path) {
	
	FILE * file = fopen(path, "w");
	if(file == NULL) {
		return 0;
	}
	
	fprintf(file, "%s\n", image.base.magic_number);
	fprintf(file, "%d %d\n", image.base.width, image.base.hight);
	
	for(int i = 0; i < image.base.hight; i++) {
		for(int j = 0; j < image.base.width; j++) {
			fprintf(file, "%d", image.data[i][j]);
		}
		fprintf(file, "\n");
	}
	
	fclose(file);
	
	return 1;
}

