#include "../../s21_matrix.h"

/**
 * @brief Проверяет две матрицы на совпадение размеров
 *
 * @param A, B (matrix_t *) указатели на две структуры матрицы.
 *
 * @return (int)
 *
 * 1 - SUCESS если равны

 * 0 - FAILURE если нет
 */
int s21_matrices_same_size(matrix_t *A, matrix_t *B) {
  if (A->rows == B->rows && A->columns == B->columns)
    return SUCCESS;
  else
    return FAILURE;
}