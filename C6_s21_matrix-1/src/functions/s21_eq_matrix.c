#include "../s21_matrix.h"

/**
 * @brief Равны ли две матрицы
 * @param A, B, (matrix_t *) указатель на матрицы
 *
 * @return (int)
 *
 * 1 - SUCESS если равны

 * 0 - FAILURE если нет
 */
int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int ret_value = SUCCESS;
  ret_value = (s21_matrix_ok(A) && s21_matrix_ok(B));
  if (ret_value) ret_value = s21_matrices_same_size(A, B);
  if (ret_value) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        if (fabs(A->matrix[i][j] - B->matrix[i][j]) > EPSILON)
          ret_value = FAILURE;
      }
    }
  }
  return ret_value;
}
