#include "../s21_matrix.h"

/**
 * @brief  Считает матрицу обратную
 *
 * Сначала надо посчитать матрицу алг.доп.
 * Транспонировать её.
 * Умножить на детерминант первоначальной матрицы.
 *
 * @param A, result (matrix_t *) указатели на матрицы начальную и результат
 * @return (int)
 *
 * 0 - OK если всё ок
 *
 * 1 - INCORRECT_MATRIX если поданы неверные данные матрицы
 *
 * 2 - CALCULATION_ERROR если матрица не квадратная или размером 1х1 или
 * детерминант = 0
 */
int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  if (!s21_matrix_ok(A) || result == NULL) return INCORRECT_MATRIX;
  if (A->columns != A->rows) return CALCULATION_ERROR;

  int temp = OK;
  double det = 0;
  if (s21_determinant(A, &det)) temp = CALCULATION_ERROR;
  if (det == 0) temp = CALCULATION_ERROR;

  if (!temp && det != 0) {
    if (A->rows == 1) {
      temp = s21_create_matrix(A->rows, A->columns, result);
      if (!temp) result->matrix[0][0] = 1 / A->matrix[0][0];
    } else {
      matrix_t tmp_calc_complement = {0}, tmp_transpose = {0};
      temp = s21_calc_complements(A, &tmp_calc_complement);
      if (!temp) temp = s21_transpose(&tmp_calc_complement, &tmp_transpose);
      if (!temp) temp = s21_mult_number(&tmp_transpose, 1 / det, result);
      s21_remove_matrix(&tmp_calc_complement);
      s21_remove_matrix(&tmp_transpose);
    }
  }
  // if (!temp && det == 0) temp = CALCULATION_ERROR;
  return temp;
}
