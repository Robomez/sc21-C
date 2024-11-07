#include "../../s21_matrix.h"

/**
 * @brief  Создать минор - матрица размерностью -1 с вычеркнутым рядом и
 * столбцом
 *
 * @param excluded_row, excluded_column (int) вычеркнутые ряд и столбец
 * @param A (matrix_t *) указатель на матрицу начальную
 * @return (matrix_t *) указатель на матрицу конечную
 *
 * Если всё ок, вернёт указатель на матрицу minor. Нет - NULL
 */
matrix_t *s21_make_minor(int excluded_row, int excluded_column, matrix_t *A) {
  int temp = 0;
  matrix_t *minor = calloc(1, sizeof(matrix_t));

  if (!s21_matrix_ok(A)) temp = INCORRECT_MATRIX;

  if (!temp) {
    temp = s21_create_matrix(A->rows - 1, A->columns - 1, minor);
  }
  if (!temp && minor != NULL) {
    for (int i = 0, row = 0; i < A->rows; i++) {
      for (int j = 0, column = 0; j < A->columns; j++) {
        if (i != excluded_row && j != excluded_column)
          minor->matrix[row][column++] = A->matrix[i][j];
      }
      if (i != excluded_row) row++;
    }
  }

  return temp == INCORRECT_MATRIX ? NULL : minor;
}