#ifndef IMAGE_H
#define IMAGE_H

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

/**
 * @brief allocate a base image with the values in parameters
 * 
 * @param image The newly allocated image
 * @param hight The amount of rows for the image
 * @param width The amount of columns for the image
 * @param magic_number An id for saying what type of PPM Image it is
 * 
 * @return Integer 0 if something went wrong, else return 1
 */
int allocate_image_base(ImageBase * image, int hight, int width, char magic_number[2]);

/**
 * @brief allocate a PBM image with the values in parameters
 * 
 * @param image The image that will be allocated
 * @param hight The amount of rows for the image
 * @param width The amount of columns for the image
 * 
 * @return Integer 0 if something went wrong, else return 1
 */
int allocate_image_pbm(ImagePBM * image, int hight, int width);

/**
 * @brief allocate a PGM image with the values in parameters
 * 
 * @param image The image that will be allocated
 * @param hight The amount of rows for the image
 * @param width The amount of columns for the image
 * @param max_gray_value The maximum gray value a pixel can have (16 generaly)
 * 
 * @return Integer 0 if something went wrong, else return 1
 */
int allocate_image_pgm(ImagePGM * image, int hight, int width, int max_gray_value);

/**
 * @brief allocate a PPM image with the values in parameters
 * 
 * @param image The image that will be allocated
 * @param hight The amount of rows for the image
 * @param width The amount of columns for the image
 * @param max_color_value The maximum value a color can have (255 generaly)
 * 
 * @return Integer 0 if something went wrong, else return 1
 */
int allocate_image_ppm(ImagePPM * image, int hight, int width, int max_color_value);

/**
 * @brief save a PBM image into a file, if file doesn't exist it will try to create it
 * 
 * @param image The image that will be saved
 * @param path the path where the image will be downloaded
 * 
 * @return Integer 0 if something went wron, else 1
 * 
 */
int save_image_pbm(ImagePBM image, char * path);

/**
 * @brief load a PBM image from a existing file
 * 
 * @param image The image that will be returned
 * @param path the path where the image is supposed stored
 * 
 * @return Integer 0 if something went wron, else 1
 * 
 */
int load_image_pbm(ImagePBM image, char * path);

//int save_image_pgm(ImagePGM image, char * path);

//int save_image_ppm(ImagePPM image, char * path);

#endif // IMAGE_H INCLUDED

