#include "../inc/matrix.h"

int main(void) {
  
  double** A;

  TABLE(A, 3, 3, {1, 5, 3}, {1, -1, 8}, {9, 3, 7});
  Matrix* a = matrix_create_fill(3, 3, A);
  
  matrix_display(a);
  matrix_display(matrix_inverse(a));
  printf("det = %lf\n", matrix_determinant(a));
  

  return 0;
}
