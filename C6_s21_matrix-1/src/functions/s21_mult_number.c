#include "../s21_matrix.h"

/**
 * @brief Умножение матрицы на число
 * @param A (matrix_t *) указатель на матрицу множимых
 * @param number (double) число, на которое умножить
 * @param result (matrix_t *) указатель на матрицу результат
 *
 * @return (int)
 *
 * 0 - OK если всё ок
 *
 * 1 - INCORRECT_MATRIX если поданы неверные данные матриц
 *
 * 2 - CALCULATION_ERROR если матрицы не одного размера (не сделать сложение)
 */
int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  if (!s21_matrix_ok(A) || result == NULL) return INCORRECT_MATRIX;

  int temp = s21_create_matrix(A->rows, A->columns, result);
  if (!temp) {
    for (int i = 0; i < result->rows; i++) {
      for (int j = 0; j < result->columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] * number;
      }
    }
  }
  return temp;
}
