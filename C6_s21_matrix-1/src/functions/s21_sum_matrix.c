#include "../s21_matrix.h"

/**
 * @brief Складывает две матрицы в третью
 * @param A, B, result (matrix_t *) указатель на матрицы слагаемые и результат
 *
 * @return (int)
 *
 * 0 - OK если всё ок
 *
 * 1 - INCORRECT_MATRIX если поданы неверные данные матриц
 *
 * 2 - CALCULATION_ERROR если матрицы не одного размера (не сделать сложение)
 */
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  if (!s21_matrix_ok(A) || !s21_matrix_ok(B) || result == NULL)
    return INCORRECT_MATRIX;
  if (!s21_matrices_same_size(A, B)) return CALCULATION_ERROR;

  int temp = s21_create_matrix(A->rows, A->columns, result);
  if (!temp) {
    for (int i = 0; i < result->rows; i++) {
      for (int j = 0; j < result->columns; j++) {
        result->matrix[i][j] = (A->matrix[i][j]) + (B->matrix[i][j]);
      }
    }
  }
  return temp;
}
