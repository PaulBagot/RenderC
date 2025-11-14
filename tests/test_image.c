#include "../include/image.h"
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <CUnit/TestRun.h>
#include <CUnit/TestDB.h>

void test_allocate_image_base()
{
    ImageBase base;

    CU_ASSERT_FALSE(allocate_image_base(&base, 0, 0, "P1"));
    CU_ASSERT_FALSE(allocate_image_base(&base, 0, 1, "P1"));
    CU_ASSERT_FALSE(allocate_image_base(&base, 1, -1, "P1"));
    CU_ASSERT_TRUE(allocate_image_base(&base, 150, 140, "P1"));

    CU_ASSERT(base.hight == 150);
    CU_ASSERT(base.width == 140);

    CU_ASSERT_STRING_EQUAL(base.magic_number, "P1");
}

void test_allocate_image_pbm()
{
    ImagePBM image;

    CU_ASSERT_TRUE(allocate_image_pbm(&image, 150, 140));
    CU_ASSERT(image.base.hight == 150);
    CU_ASSERT(image.base.width == 140);

    CU_ASSERT_STRING_EQUAL(image.base.magic_number, "P1");

    int test = 1;
    for (int i = 0; i < image.base.hight; i++) {
        for (int j = 0; j < image.base.width; j++) {
            if (image.data[i][j] != 0) {
                test = 0;
            }
        }
    }
    CU_ASSERT_TRUE(test);
}

void test_allocate_image_pgm()
{
    ImagePGM image;

    CU_ASSERT_TRUE(allocate_image_pgm(&image, 100, 50, 255));

    CU_ASSERT(image.base.hight == 100);
    CU_ASSERT(image.base.width == 50);

    CU_ASSERT_STRING_EQUAL(image.base.magic_number, "P2");
    CU_ASSERT(image.max_gray_value == 255);

    int test = 1;
    for (int i = 0; i < image.base.hight; i++) {
        for (int j = 0; j < image.base.width; j++) {
            if (image.data[i][j] != 0) {
                test = 0;
            }
        }
    }
    CU_ASSERT_TRUE(test);
}

void test_allocate_image_ppm()
{
    ImagePPM image;

    CU_ASSERT_TRUE(allocate_image_ppm(&image, 50, 100, 255));
    CU_ASSERT(image.base.hight == 50);
    CU_ASSERT(image.base.width == 100);
    CU_ASSERT_STRING_EQUAL(image.base.magic_number, "P3");
    CU_ASSERT(image.max_color_value == 255);

    int test = 1;
    for (int i = 0; i < image.base.hight; i++) {
        for (int j = 0; j < image.base.width; j++) {
            if (image.pixels[i][j].r != 0) {
                test = 0;
            }
            if (image.pixels[i][j].g != 0) {
                test = 0;
            }
            if (image.pixels[i][j].b != 0) {
                test = 0;
            }
        }
    }
    CU_ASSERT_TRUE(test);
}

void test_save_image_pbm()
{
    ImagePBM image;
    allocate_image_pbm(&image, 3, 3);
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            image.data[i][j] = i % 2;
        }
    }
    CU_ASSERT_TRUE(save_image_pbm(image, "./tests/tmp/test_save_pbm.ppm"));
}

void test_save_image_pgm()
{
    ImagePGM image;
    allocate_image_pgm(&image, 3, 3, 15);
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            image.data[i][j] = i * j;
        }
    }
    CU_ASSERT_TRUE(save_image_pgm(image, "./tests/tmp/test_save_pgm.ppm"));
}

void test_create_pixel()
{
    ImagePPM image;
    allocate_image_ppm(&image, 1, 1, 255);
    int max = image.max_color_value;
    CU_ASSERT_FALSE(create_pixel(&image.pixels[0][0], max, -1, 0, 0));
    CU_ASSERT_FALSE(create_pixel(&image.pixels[0][0], max, 0, -1, 0));
    CU_ASSERT_FALSE(create_pixel(&image.pixels[0][0], max, 0, 0, -1));

    CU_ASSERT_FALSE(create_pixel(&image.pixels[0][0], max, max + 1, max, max));
    CU_ASSERT_FALSE(create_pixel(&image.pixels[0][0], max, max, max + 1, max));
    CU_ASSERT_FALSE(create_pixel(&image.pixels[0][0], max, max, max, max + 1));

    CU_ASSERT_TRUE(create_pixel(&image.pixels[0][0], max, 0, 0, 0));
    CU_ASSERT_TRUE(create_pixel(&image.pixels[0][0], max, max, max, max));
}

void test_save_image_ppm()
{
    ImagePPM image;
    allocate_image_ppm(&image, 3, 3, 255);

    create_pixel(&image.pixels[0][0], image.max_color_value, 0, 0, 0);
    create_pixel(&image.pixels[0][1], image.max_color_value, 0, 0, 255);
    create_pixel(&image.pixels[0][2], image.max_color_value, 0, 255, 0);

    create_pixel(&image.pixels[1][0], image.max_color_value, 0, 255, 255);
    create_pixel(&image.pixels[1][1], image.max_color_value, 255, 0, 0);
    create_pixel(&image.pixels[1][2], image.max_color_value, 255, 0, 255);

    create_pixel(&image.pixels[2][0], image.max_color_value, 255, 255, 0);
    create_pixel(&image.pixels[2][1], image.max_color_value, 255, 255, 255);
    create_pixel(&image.pixels[2][2], image.max_color_value, 0, 0, 0);

    CU_ASSERT_TRUE(save_image_ppm(image, "./tests/tmp/test_save_ppm.ppm"));
}

int main(void)
{
    CU_initialize_registry();

    CU_pSuite suiteAllocate = CU_add_suite("Tests Images Allocations", NULL, NULL);
    CU_add_test(suiteAllocate, "test_allocate_image_base", test_allocate_image_base);
    CU_add_test(suiteAllocate, "test_allocate_image_pbm", test_allocate_image_pbm);
    CU_add_test(suiteAllocate, "test_allocate_image_pgm", test_allocate_image_pgm);
    CU_add_test(suiteAllocate, "test_allocate_image_ppm", test_allocate_image_ppm);

    CU_pSuite suiteSave = CU_add_suite("Tests Images Savings", NULL, NULL);
    CU_add_test(suiteSave, "test_save_image_pbm", test_save_image_pbm);
    CU_add_test(suiteSave, "test_save_image_pgm", test_save_image_pgm);
    CU_add_test(suiteSave, "test_create_pixel", test_create_pixel);
    CU_add_test(suiteSave, "test_save_image_ppm", test_save_image_ppm);

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();

    CU_cleanup_registry();

    return 0;
}
