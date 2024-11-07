#include "../s21_matrix.h"

/**
 * @brief Транспонирует матрицу в результат
 * @param A, result (matrix_t *) указатели на матрицы начальную и результат
 *
 * @return (int)
 *
 * 0 - OK если всё ок
 *
 * 1 - INCORRECT_MATRIX если поданы неверные данные матрицы
 *
 */
int s21_transpose(matrix_t *A, matrix_t *result) {
  if (!s21_matrix_ok(A) || result == NULL) return INCORRECT_MATRIX;

  int temp = s21_create_matrix(A->columns, A->rows, result);
  if (!temp) {
    for (int i = 0; i < A->columns; i++) {
      for (int j = 0; j < A->rows; j++) {
        result->matrix[i][j] = A->matrix[j][i];
      }
    }
  }
  return temp;
}