#include "../include/image.h"
#include <stdlib.h>
#include <stdio.h>

int allocate_image_base(ImageBase * image, int hight, int width, char magic_number[2]) {
	
	if(hight < 1 || width < 1) {
		return 0;
	}

	image->magic_number = malloc(sizeof(char) * 2);
	image->magic_number = magic_number;
	image->hight = hight;
	image->width = width;
	
	return 1;
}

int allocate_image_pbm(ImagePBM * image, int hight, int width) {
	
	if(allocate_image_base(&image->base, hight, width, "P1") == 0) {
		return 0;
	}
	
	image->data = malloc(sizeof(int*) * hight);
	for(int i = 0; i < hight; i++) {
		image->data[i] = malloc(sizeof(int) * width);
	}

	return 1;
}

int allocate_image_pgm(ImagePGM * image, int hight, int width, int max_gray_value) {
	
	if(allocate_image_base(&image->base, hight, width, "P2") == 0) {
		return 0;
	}
	
	image->max_gray_value = max_gray_value;
	image->data = malloc(sizeof(int*) * hight);
	for(int i = 0; i < hight; i++) {
		image->data[i] = malloc(sizeof(int) * width);
	}

	return 1;
}

int allocate_image_ppm(ImagePPM * image, int hight, int width, int max_color_value) {

	if(allocate_image_base(&image->base, hight, width, "P3") == 0) {
		return 0;
	}
	
	image->max_color_value = max_color_value;
	image->pixels = malloc(sizeof(Pixel*) * hight);
	for(int i = 0; i < hight; i++) {

		image->pixels[i] = malloc(sizeof(Pixel) * width);
		for(int j = 0; j < width; j++) {	
			Pixel new_pixel;
			new_pixel.r = 0;
			new_pixel.g = 0;
			new_pixel.b = 0;
			image->pixels[i][j] = new_pixel;
		}
	}
	
	return 1;
}

int save_image_pbm(ImagePBM image, char * path) {
		
	FILE * file = fopen(path, "w+");
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


int load_image_pbm(ImagePBM * image, char * path) {
	
	FILE * file = fopen(path, "r");
	if(file == NULL) {
		return 0;
	}
	
	char magic_number[2];
	fscanf(file, "%s\n", magic_number); 
	
	int width = 0;
	int hight = 0;
	fscanf(file, "%d %d\n", &width, &hight);
	
	if(allocate_image_pbm(image, hight, width) == 0) {
		return 0;
	}
	
	for(int i = 0; i < image->base.hight; i++) {
		for(int j = 0; j < image->base.width; j++) {
			fscanf(file, "%d", &image->data[i][j]);
		}
	}
	return 1;
}

