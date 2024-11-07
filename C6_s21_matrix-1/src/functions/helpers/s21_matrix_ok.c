#include "../../s21_matrix.h"

/**
 * @brief Проверяет матрицу на валидность. т.е. не NULL и ряды не < 1
 *
 * @param A (matrix_t *) указатель на структуру матрицы.
 *
 * @return matrix_status (int)
 *
 * 1 - SUCESS
 *
 * 0 - FAILURE
 */
int s21_matrix_ok(matrix_t *A) {
  int matrix_status = SUCCESS;
  if (A == NULL || A->matrix == NULL || A->rows < 1 || A->columns < 1)
    matrix_status = FAILURE;
  return matrix_status;
}