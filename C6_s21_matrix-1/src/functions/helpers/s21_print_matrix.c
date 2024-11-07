#include "../../s21_matrix.h"

/**
 * @brief Печатает матрицу.
 *
 * @param result (matrix_t) структура матр.
 *
 * @return печатает в консоль:
 *
 * rows (int) количество рядов
 *
 * columns (int) количество колонок
 *
 * значения матрицы
 */
void s21_print_matrix(matrix_t result) {
  printf("rows %d\n", result.rows);
  printf("cols %d\n", result.columns);

  for (int i = 0; i < result.rows; i++) {
    for (int j = 0; j < result.columns; j++) {
      printf("%f ", result.matrix[i][j]);
    }
    printf("\n");
  }
  printf("\n");
}