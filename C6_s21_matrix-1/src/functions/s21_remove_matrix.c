#include "../s21_matrix.h"

/**
 * @brief Очищает матрицу
 * @param A (matrix_t *) указатель на матрицу
 *
 * @return (void)
 */
void s21_remove_matrix(matrix_t *A) {
  if (A != NULL && A->matrix != NULL) {
    // Освободить память
    free(A->matrix);
    A->columns = 0;
    A->rows = 0;
    // Занулить указатель
    A->matrix = NULL;
  }
}