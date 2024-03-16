#include "../inc/matrix.h"

int main(void) {
  
  double** A;

  TABLE(A, 3, 3, {1, -5, 3}, {1, 0, 8.64}, {-9.245, 3, -2});
  Matrix* a = matrix_create_fill(3, 3, A);
  
  matrix_display(a);
  matrix_display(matrix_inverse(a));
  printf("det = %lf\n", matrix_determinant(a));
  

  return 0;
}
