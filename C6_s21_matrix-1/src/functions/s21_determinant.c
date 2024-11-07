#include "../s21_matrix.h"

/**
 * @brief  Считает детерминант матрицы (матрица д.б. квадратной)
 *
 * Cуммa произведений элементов строки (столбца) на соответствующие
 * алгебраические дополнения.
 *
 * @param A (matrix_t *) указатель на матрицу начальную
 * @param result (double *) указатель на дабл, куда запишется результат
 * @return (int)
 *
 * 0 - OK если всё ок
 *
 * 1 - INCORRECT_MATRIX если поданы неверные данные матрицы
 *
 * 2 - CALCULATION_ERROR если матрица не квадратная или размером 1х1
 */
int s21_determinant(matrix_t *A, double *result) {
  if (!s21_matrix_ok(A) || result == NULL) return INCORRECT_MATRIX;
  if (A->columns != A->rows) return CALCULATION_ERROR;

  int temp = 0, sign = 1;
  if (A->rows == 1) *result = A->matrix[0][0];
  if (A->rows == 2)
    *result =
        A->matrix[0][0] * A->matrix[1][1] - A->matrix[1][0] * A->matrix[0][1];
  if (A->rows > 2) {
    *result = 0;
    for (int i = 0; i < A->columns && !temp; i++) {
      calc_determ(&temp, result, i, A, &sign);
    }
  }
  return temp;
}
