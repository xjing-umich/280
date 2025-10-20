#include "Matrix.hpp"
#include "Image_test_helpers.hpp"
#include "unit_test_framework.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include <cassert>

using namespace std;

// Here's a free test for you! Model yours after this one.
// Test functions have no interface and thus no RMEs, but
// add a comment like the one here to say what it is testing.
// -----
// Sets various pixels in a 2x2 Image and checks
// that Image_print produces the correct output.
TEST(test_print_basic) {
  Image img;
  const Pixel red = {255, 0, 0};
  const Pixel green = {0, 255, 0};
  const Pixel blue = {0, 0, 255};
  const Pixel white = {255, 255, 255};

  Image_init(&img, 2, 2);
  Image_set_pixel(&img, 0, 0, red);
  Image_set_pixel(&img, 0, 1, green);
  Image_set_pixel(&img, 1, 0, blue);
  Image_set_pixel(&img, 1, 1, white);

  // Capture our output
  ostringstream s;
  Image_print(&img, s);

  // Correct output
  ostringstream correct;
  correct << "P3\n2 2\n255\n";
  correct << "255 0 0 0 255 0 \n";
  correct << "0 0 255 255 255 255 \n";
  ASSERT_EQUAL(s.str(), correct.str());
}

// IMPLEMENT YOUR TEST FUNCTIONS HERE
// You are encouraged to use any functions from Image_test_helpers.hpp as needed.

TEST(test_image_init) {
    Image img;
    Image_init(&img, 3, 3);

    ASSERT_EQUAL(Image_width(&img), 3);
    ASSERT_EQUAL(Image_height(&img), 3);

    for (int row = 0; row < Image_height(&img); row++) {
        for (int col = 0; col < Image_width(&img); col++) {
            Pixel p = Image_get_pixel(&img, row, col);
            ASSERT_EQUAL(p.r, 0);
            ASSERT_EQUAL(p.g, 0);
            ASSERT_EQUAL(p.b, 0);
        }
    }
}
TEST(test_Image_init){
    string ppm_data =
            "P3\n"
            "2 2\n"
            "255\n"
            "255 0 0   0 255 0\n"
            "0 0 255   255 255 255\n";
        istringstream is(ppm_data);

        Image img;
        Image_init(&img, is);

        ASSERT_EQUAL(Image_width(&img), 2);
        ASSERT_EQUAL(Image_height(&img), 2);

        
        Pixel expected_pixels[2][2] = {
            {{255, 0, 0}, {0, 255, 0}},   // First row
            {{0, 0, 255}, {255, 255, 255}} // Second row
        };

        // Validate pixel colors
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                Pixel p = Image_get_pixel(&img, i, j);
                ASSERT_EQUAL(p.r, expected_pixels[i][j].r);
                ASSERT_EQUAL(p.g, expected_pixels[i][j].g);
                ASSERT_EQUAL(p.b, expected_pixels[i][j].b);
            }
        }
    }

    
TEST(test_image_width) {
    Image img;
    Image_init(&img, 5, 7);
    ASSERT_EQUAL(Image_width(&img), 5);
}

TEST(test_image_height) {
    Image img;
    Image_init(&img, 5, 7);
    ASSERT_EQUAL(Image_height(&img), 7);
}

TEST(test_image_get_pixel) {
    Image img;
    Image_init(&img, 3, 3);
    Pixel color = { 100, 150, 200 };
    Image_set_pixel(&img, 1, 1, color);

    Pixel pix = Image_get_pixel(&img, 1, 1);
    ASSERT_EQUAL(pix.r, 100);
    ASSERT_EQUAL(pix.g, 150);
    ASSERT_EQUAL(pix.b, 200);
}

TEST(test_image_set_pixel) {
    Image img;
    Image_init(&img, 2, 2);

    Pixel red = { 255, 0, 0 };
    Image_set_pixel(&img, 0, 0, red);

    Pixel pix = Image_get_pixel(&img, 0, 0);
    ASSERT_EQUAL(pix.r, 255);
    ASSERT_EQUAL(pix.g, 0);
    ASSERT_EQUAL(pix.b, 0);
}

TEST(test_image_fill) {
    Image img;
    Image_init(&img, 4, 4);
    Pixel col = { 255, 255, 0 };
    Image_fill(&img, col);

    for (int row = 0; row < Image_height(&img); row++) {
        for (int col = 0; col < Image_width(&img); col++) {
            Pixel pix = Image_get_pixel(&img, row, col);
            ASSERT_EQUAL(pix.r, 255);
            ASSERT_EQUAL(pix.g, 255);
            ASSERT_EQUAL(pix.b, 0);
        }
    }
}




TEST_MAIN() // Do NOT put a semicolon here
