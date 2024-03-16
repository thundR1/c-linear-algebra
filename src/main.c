#include "../inc/matrix.h"

int main(void) {
  
  Matrix* a = matrix_create(3, 3);

  TABLE(a, 3, 3, {1, -5, 3}, {1, 15, 7.4950}, {-9.245, 3, -2});
  
  matrix_display(a);
  matrix_display(matrix_inverse(a));
  printf("det = %lf\n", matrix_determinant(a));
  

  return 0;
}
