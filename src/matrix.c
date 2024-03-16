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

void matrix_copy(Matrix* a, Matrix* b) {
  if (a->rows != b->rows || a->cols != b->cols) PANIC("Invalid input, dimensions doesn't match");
  for (uint32_t i = 0; i < b->rows; i++) {
    for (uint32_t j = 0; j < b->cols; j++) {
      a->items[i][j] = b->items[i][j];
    }
  }
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
  Matrix* res = matrix_create(dimension, dimension);
  for (uint32_t i = 0; i < dimension; i++) {
    for (uint32_t j = 0; j < dimension; j++) {
      res->items[i][j] = (i == j ? 1.0 : 0.0);
    }
  }
  return res;
}

bool matrix_is_square(Matrix* m) {
    return (m->rows == m->cols);
}

double matrix_determinant(Matrix* m) {
    if (!matrix_is_square(m)) PANIC("Invalid input, matrix is non-square");
    if (m->rows == 1) {
      return m->items[0][0];
    }
    double det = 0;
    Matrix* submatrix = matrix_create(m->rows - 1, m->cols - 1);
    for (uint32_t k = 0; k < m->cols; k++) {
      for (uint32_t i = 1; i < m->rows; i++) {
        for (uint32_t j = 0; j < m->cols; j++) {
          if (j < k) {
            submatrix->items[i - 1][j] = m->items[i][j];
          } else if (j > k) {
            submatrix->items[i - 1][j - 1] = m->items[i][j];
          }
        }
      }
      det += (k % 2 == 0 ? 1 : -1) * m->items[0][k] * matrix_determinant(submatrix);
    }
    matrix_destroy(submatrix);
    return det;
}

bool matrix_is_singular(Matrix* m) {
    return (matrix_determinant(m) == (double)0);
}

Matrix* matrix_inverse(Matrix* m) {
    if (matrix_is_singular(m)) PANIC("Invalid input, matrix is singular no inverse exists");
    Matrix* temp = matrix_create(m->rows, m->cols);
    matrix_copy(temp, m);
    Matrix* inv = matrix_identity(m->rows);

     for (uint32_t i = 0; i < m->rows; i++) {
        // Check for zero pivot
        if (temp->items[i][i] == 0.0) {
            matrix_destroy(inv);
            matrix_destroy(temp);
            PANIC("Inverse does not exist. Zero pivot found");
        }

        // Scale row i to have a leading 1
        double scale = 1.0 / temp->items[i][i];
        for (uint32_t j = 0; j < m->rows; j++) {
            temp->items[i][j] *= scale;
            inv->items[i][j] *= scale;
        }

        // Eliminate non-zero entries in column i
        for (uint32_t k = 0; k < m->rows; k++) {
            if (k != i) {
                double factor = temp->items[k][i];
                for (uint32_t j = 0; j < m->rows; j++) {
                    temp->items[k][j] -= factor * temp->items[i][j];
                    inv->items[k][j] -= factor * inv->items[i][j];
                }
            }
        }
    }

    // Free temporary matrix
    matrix_destroy(temp);

    return inv;
}

void matrix_destroy(Matrix* m) {
  if (!m) PANIC("NULL pointer");
  for (uint32_t i = 0; i < m->rows; i++) {
        free(m->items[i]);
  }
  free(m->items);
  free(m);
}

void matrix_display(Matrix* m) {
  for (uint32_t i = 0; i < m->rows; i++) {
    printf("[%.6lf", m->items[i][0]);
    for (uint32_t j = 1; j < m->cols; j++) {
      printf("\t%.6lf", m->items[i][j]);
    }
    printf("]\n");
  }
  printf("\n");
}