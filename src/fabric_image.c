#include "../include/fabric_image.h"
#include <stdlib.h>

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
