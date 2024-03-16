#ifndef MATRIX_H
#define MATRIX_H

/* Inlude Section Start */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
/* Inlude Section End */

/* Function-like Macros Section Start */
#define PANIC(msg) do {fprintf(stderr, "Error: %s\n", msg); exit(EXIT_FAILURE);} while(0)
#define TABLE(arr, rows, cols, ...) \
    do { \
        arr = (double **)malloc(rows * sizeof(double *)); \
        for (size_t i = 0; i < rows; i++) { \
            arr[i] = (double *)malloc(cols * sizeof(double)); \
        } \
        double temp_arr[rows][cols] = { __VA_ARGS__ }; \
        for (size_t i = 0; i < rows; i++) { \
            for (size_t j = 0; j < cols; j++) { \
                arr[i][j] = temp_arr[i][j]; \
            } \
        } \
    } while(0)
/* Function-like Macros Section End */

/* Types Section Start */
typedef struct {
  uint32_t rows, cols;
  double** items;
} Matrix;
/* Types Section End */

/* Function Section Start */
Matrix* matrix_create(uint32_t rows, uint32_t cols);
Matrix* matrix_create_fill(uint32_t rows, uint32_t cols, double** items);
Matrix* matrix_dot(Matrix* a, Matrix* b);
bool matrix_is_equal(Matrix* a, Matrix* b);
Matrix* matrix_transpose(Matrix* m);
Matrix* matrix_identity(uint32_t dimension); // Generates a (dimension x dimension) identity mattrix
bool matrix_is_square(Matrix* m);
double matrix_determinant(Matrix* m);
bool matrix_is_singular(Matrix* m);
Matrix* matrix_inverse(Matrix* m);
void matrix_destroy(Matrix* m);
void matrix_display(Matrix* m);
/* Function Section End */

#endif /* MATRIX_H */