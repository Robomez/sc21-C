#include "../s21_matrix.h"

/**
 * @brief Инициализирует матрицу нужного размера
 * @param rows, columns (int) размеры матрицы рядов/колонок
 * @param result (matrix_t *) указатель на матрицу, которая будет в структуре
 *
 * @return (int)
 *
 * 0 - OK если всё ок
 *
 * 1 - INCORRECT_MATRIX если нет
 */
int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int matrix_status = OK;
  // Проверка аргументов
  if (result == NULL || rows < 1 || columns < 1) {
    return INCORRECT_MATRIX;
  }

  result->rows = rows;
  result->columns = columns;
  result->matrix = (double **)calloc(rows + rows * columns, sizeof(double));
  if (result->matrix == NULL) {
    matrix_status = INCORRECT_MATRIX;
  } else {
    double *starting_point = (double *)(result->matrix + rows);
    int max_dimension = rows <= columns ? columns : rows;
    for (int i = 0; i < max_dimension; i++)
      result->matrix[i] = starting_point + i * columns;
  }

  return matrix_status;
}