#include "../../s21_matrix.h"

void calc_determ(int *temp, double *result, int i, matrix_t *A, int *sign) {
  matrix_t *minor = s21_make_minor(0, i, A);
  if (minor == NULL)
    *temp = INCORRECT_MATRIX;
  else {
    double minor_det = 0;
    *temp = s21_determinant(minor, &minor_det);
    if (!*temp) {
      *result += *sign * A->matrix[0][i] * minor_det;
      *sign *= -1;
    }
    s21_remove_matrix(minor);
    free(minor);
    minor = NULL;
  }
}