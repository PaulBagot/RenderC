#ifndef FABRIC_IMAGE_H
#define FABRIC_IMAGE_H

struct ImageBase {
	char * magic_number;
	int hight;
	int width;
	
} typedef ImageBase;

struct ImagePBM {
	ImageBase base;
	int ** data;
} typedef ImagePBM;

struct ImagePGM {
	ImageBase base;
	int max_gray_value;
	int ** data;
} typedef ImagePGM;

struct Pixel {
	int r;
	int g;
	int b;
} typedef Pixel;

struct ImagePPM {
	ImageBase base;
	int max_color_value;
	Pixel ** pixels;
} typedef ImagePPM;

ImageBase allocate_image_base(int hight, int width, char magic_number[2]);

ImagePBM allocate_image_pbm(int hight, int width);

ImagePGM allocate_image_pgm(int hight, int width, int max_gray_value);

ImagePPM allocate_image_ppm(int hight, int width, int max_color_value);

#endif // FABRIC_IMAGE_H INCLUDED
