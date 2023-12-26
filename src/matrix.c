#include "../inc/matrix.h"

Matrix* matrix_create(uint32_t rows, uint32_t cols) {
  Matrix* res = (Matrix*) malloc(sizeof(Matrix));
  res->rows = rows;
  res->cols = cols;
  res->items = (double**) malloc(rows * sizeof(double*));
  for (uint32_t i = 0; i < rows; i++) {
    res->items[i] = (double*) malloc(cols * sizeof(double));
    for (uint32_t j = 0; j < cols; j++) {
      res->items[i][j] = 0;
    }
  }
  return res;
}

Matrix* matrix_create_fill(uint32_t rows, uint32_t cols, double** items) {
  if (!items || !(*items)) PANIC("NULL pointer");
  Matrix* res = matrix_create(rows, cols);
  for (uint32_t i = 0; i < rows; i++) {
    for (uint32_t j = 0; j < cols; j++) {
      res->items[i][j] = items[i][j];
    }
  }
  return res;
}

Matrix* matrix_dot(Matrix* a, Matrix* b) {
  if (a->cols != b->rows) PANIC("Invlaid matrix dimensions");
  Matrix* res = matrix_create(a->rows, b->cols);
  for (uint32_t i = 0; i < a->rows; i++) {
    for (uint32_t j = 0; j < b->rows; j++) {
      for (uint32_t k = 0; k < b->cols; k++) {
        res->items[i][k] += a->items[i][j] * b->items[j][k];
      }
    }
  }
  return res;
}

bool matrix_is_equal(Matrix* a, Matrix* b) {
  if ((a->rows != b->rows) || (a->cols != b->cols)) return false;
  for (uint32_t i = 0; i < a->rows; i++) {
    for (uint32_t j = 0; j < a->cols; j++) {
      if (a->items[i][j] != b->items[i][j]) return false;
    }
  }
  return true;
}

Matrix* matrix_transpose(Matrix* m) {
    Matrix* res = matrix_create(m->cols, m->rows);
    for (uint32_t i = 0; i < m->rows; i++) {
        for (uint32_t j = 0; j < m->cols; j++) {
            res->items[j][i] = m->items[i][j];
        }
    }
    return res;
}

Matrix* matrix_identity(uint32_t dimension) {
  if (dimension < 0) PANIC("Invalid Dimensions");
  Matrix* res = matrix_create(dimension, dimension);
  for (uint32_t i = 0; i < dimension; i++) {
    for (uint32_t j = 0; j < dimension; j++) {
      res->items[i][j] = (i == j ? 1 : 0);
    }
  }
  return res;
}

bool matrix_is_square(Matrix* m) {
    return (m->rows == m->cols);
}

double matrix_determinant(Matrix* m) {
    if (!matrix_is_square(m)) PANIC("Invalid input, matrix is non-square");
    //
}

bool matrix_is_singular(Matrix* m) {
    return (matrix_determinant(m) == (double)0);
}

Matrix* matrix_inverse(Matrix* m) {
    if (matrix_is_singular(m)) PANIC("Invalid input, matrix is singular");
    //
}

void matrix_free(Matrix** m) {
  if (!m || !(*m)) PANIC("NULL pointer");
  for (uint32_t i = 0; i < (*m)->rows; i++) {
    free((*m)->items[i]);
    (*m)->items[i] = NULL;
  }
  free((*m)->items);
  (*m)->items = NULL;
  free(m);
  m = NULL;
}

void matrix_display(Matrix* m) {
  for (uint32_t i = 0; i < m->rows; i++) {
    printf("[%.3lf", m->items[i][0]);
    for (uint32_t j = 1; j < m->cols; j++) {
      printf("\t%.3lf", m->items[i][j]);
    }
    printf("]\n");
  }
  printf("\n");
}