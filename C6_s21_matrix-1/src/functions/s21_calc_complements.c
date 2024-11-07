#include "../s21_matrix.h"

void cc_calc_determ(int *temp, matrix_t *result, int i, int j, matrix_t *A,
                    int *sign) {
  matrix_t *minor = s21_make_minor(i, j, A);
  if (minor == NULL) {
    *temp = INCORRECT_MATRIX;
  } else {
    double determinant = 0;
    *temp = s21_determinant(minor, &determinant);
    if (!*temp) {
      result->matrix[i][j] = *sign * determinant;
      *sign *= -1;
    }
    s21_remove_matrix(minor);
    free(minor);
    minor = NULL;
  }
}

/**
 * @brief  Считает матрицу алгебраических дополнений
 *
 * Сначала надо посчитать минор - детерминант, полученный вычёркиванием из
 * матрицы A i-й строки и j-го столбца. Для всех элементов матрицы.
 *
 * Затем матрицу миноров надо умножить на -1;
 *
 * @param A, result (matrix_t *) указатели на матрицы начальную и результат
 * @return (int)
 *
 * 0 - OK если всё ок
 *
 * 1 - INCORRECT_MATRIX если поданы неверные данные матрицы
 *
 * 2 - CALCULATION_ERROR если матрица не квадратная или размером 1х1
 */
int s21_calc_complements(matrix_t *A, matrix_t *result) {
  if (!s21_matrix_ok(A) || result == NULL) return INCORRECT_MATRIX;
  if (A->columns != A->rows || A->rows == 1) return CALCULATION_ERROR;

  int temp = s21_create_matrix(A->rows, A->columns, result);
  if (!temp) {
    for (int i = 0; i < A->rows && !temp; i++) {
      int sign = i % 2 == 0 ? 1 : -1;
      for (int j = 0; j < A->columns && !temp; j++) {
        // double determinant = 0;
        // calc_determ(&temp, &result->matrix[i][j], i, A, &sign);
        cc_calc_determ(&temp, result, i, j, A, &sign);
      }
    }
  }
  return temp;
}
