#include "../s21_matrix.h"

/**
 * @brief Умножение матриц
 * @param A, B, result (matrix_t *) указатели на матрицы множимых и результат
 *
 * @return (int)
 *
 * 0 - OK если всё ок
 *
 * 1 - INCORRECT_MATRIX если поданы неверные данные матриц
 *
 * 2 - CALCULATION_ERROR если к-во столбцов А не равно строкам B (не умножить)
 */
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  if (!s21_matrix_ok(A) || !s21_matrix_ok(B) || result == NULL)
    return INCORRECT_MATRIX;
  if (A->columns != B->rows) return CALCULATION_ERROR;

  int temp = s21_create_matrix(A->rows, B->columns, result);
  if (!temp) {
    for (int i = 0; i < result->rows; i++) {
      for (int j = 0; j < result->columns; j++) {
        for (int k = 0; k < B->rows; k++) {
          result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
        }
      }
    }
  }
  return temp;
}
