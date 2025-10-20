#include "Matrix.hpp"
#include "Matrix_test_helpers.hpp"
#include "unit_test_framework.hpp"

using namespace std;

// Here's a free test for you! Model yours after this one.
// Test functions have no interface and thus no RMEs, but
// add a comment like the one here to say what it is testing.
// -----
// Fills a 3x5 Matrix with a value and checks
// that Matrix_at returns that value for each element.
TEST(test_fill_basic) {
    Matrix mat;
    const int width = 3;
    const int height = 5;
    const int value = 42;
    Matrix_init(&mat, 3, 5);
    Matrix_fill(&mat, value);

    for (int r = 0; r < height; ++r) {
        for (int c = 0; c < width; ++c) {
            ASSERT_EQUAL(*Matrix_at(&mat, r, c), value);
        }
    }
}

TEST(test_matrix_init) {
    Matrix mat;
    const int width = 4;
    const int height = 6;
    Matrix_init(&mat, width, height);

    ASSERT_EQUAL(Matrix_width(&mat), width);
    ASSERT_EQUAL(Matrix_height(&mat), height);

    // Ensure all elements are initialized to 0
    for (int row = 0; row < height; ++row) {
        for (int col = 0; col < width; ++col) {
            ASSERT_EQUAL(*Matrix_at(&mat, row, col), 0);
        }
    }
}

TEST(test_matrix_width) {
    Matrix mat;
    Matrix_init(&mat, 7, 8);
    ASSERT_EQUAL(Matrix_width(&mat), 7);
}

TEST(test_matrix_height) {
    Matrix mat;
    Matrix_init(&mat, 7, 8);
    ASSERT_EQUAL(Matrix_height(&mat), 8);
}

TEST(test_matrix_at) {
    Matrix mat;
    Matrix_init(&mat, 4, 4);
    *Matrix_at(&mat, 2, 2) = 99;
    ASSERT_EQUAL(*Matrix_at(&mat, 2, 2), 99);
}

TEST(test_matrix_fill) {
    Matrix mat;
    Matrix_init(&mat, 5, 5);
    Matrix_fill(&mat, 7);

    for (int row = 0; row < Matrix_height(&mat); ++row) {
        for (int col = 0; col < Matrix_width(&mat); ++col) {
            ASSERT_EQUAL(*Matrix_at(&mat, row, col), 7);
        }
    }
}

TEST(test_matrix_fill_border) {
    Matrix mat;
    Matrix_init(&mat, 4, 4);
    Matrix_fill_border(&mat, 9);

    for (int row = 0; row < 4; ++row) {
        for (int col = 0; col < 4; ++col) {
            if ((row == 0) || (row == 3) || (col == 0) || (col == 3)) {
                ASSERT_EQUAL(*Matrix_at(&mat, row, col), 9);
            }
            else {
                ASSERT_EQUAL(*Matrix_at(&mat, row, col), 0);
            }
        }
    }
}

TEST(test_matrix_max) {
    Matrix mat;
    Matrix_init(&mat, 3, 3);
    *Matrix_at(&mat, 1, 1) = 50;
    *Matrix_at(&mat, 2, 2) = 100;
    *Matrix_at(&mat, 0, 0) = 10;

    ASSERT_EQUAL(Matrix_max(&mat), 100);

    Matrix_init(&mat, 4, 4);
    for (int row = 0; row < 4; ++row) {
        for (int col = 0; col < 4; ++col) {
            *Matrix_at(&mat, row, col) = -2;
        }
    }
    *Matrix_at(&mat, 0, 0) = -1;
    ASSERT_EQUAL(Matrix_max(&mat), -1);

    Matrix_init(&mat, 3, 3);
    *Matrix_at(&mat, 0, 0) = -10;
    *Matrix_at(&mat, 0, 1) = 20;
    *Matrix_at(&mat, 1, 1) = -5;
    *Matrix_at(&mat, 2, 2) = 15;

    ASSERT_EQUAL(Matrix_max(&mat), 20);

    Matrix_init(&mat, 5, 5);
    Matrix_fill(&mat, 7);

    ASSERT_EQUAL(Matrix_max(&mat), 7);

    Matrix_init(&mat, 1, 1);
    *Matrix_at(&mat, 0, 0) = 42;

    ASSERT_EQUAL(Matrix_max(&mat), 42);
}

TEST(test_matrix_column_of_min_value_in_row) {
    Matrix mat;
    Matrix_init(&mat, 4, 4);
    *Matrix_at(&mat, 2, 1) = 3;
    *Matrix_at(&mat, 2, 2) = 2;
    *Matrix_at(&mat, 2, 3) = 5;

    ASSERT_EQUAL(Matrix_column_of_min_value_in_row(&mat, 2, 1, 4), 2);
}

TEST(test_matrix_min_value_in_row) {
    Matrix mat;
    Matrix_init(&mat, 5, 5);
    *Matrix_at(&mat, 3, 1) = 5;
    *Matrix_at(&mat, 2, 3) = 5;
    *Matrix_at(&mat, 3, 3) = 8;
    *Matrix_at(&mat, 3, 4) = 4;

    ASSERT_EQUAL(Matrix_min_value_in_row(&mat, 3, 1, 5), 0);

    Matrix_init(&mat, 4, 4);
    *Matrix_at(&mat, 2, 0) = 5;
    *Matrix_at(&mat, 2, 1) = 3;
    *Matrix_at(&mat, 2, 2) = 7;
    *Matrix_at(&mat, 2, 3) = 2;

    ASSERT_EQUAL(Matrix_min_value_in_row(&mat, 2, 0, 4), 2);

    Matrix_init(&mat, 4, 4);
    *Matrix_at(&mat, 1, 0) = -5;
    *Matrix_at(&mat, 1, 1) = -19;
    *Matrix_at(&mat, 1, 2) = -12;
    *Matrix_at(&mat, 1, 3) = -2;

    ASSERT_EQUAL(Matrix_min_value_in_row(&mat, 1, 0, 4), -19);

    Matrix_init(&mat, 5, 5);
    Matrix_fill(&mat, 7);

    ASSERT_EQUAL(Matrix_min_value_in_row(&mat, 3, 0, 5), 7);

    Matrix_init(&mat, 3, 3);

    ASSERT_EQUAL(Matrix_min_value_in_row(&mat, 0, 0, 3), 0);
}
// ADD YOUR TESTS HERE
// You are encouraged to use any functions from Matrix_test_helpers.hpp as needed.

TEST_MAIN() // Do NOT put a semicolon here 
