#include "backend_internal.h"

/**
 * @file copy_matrix.c
 * @brief Функции для копирования матриц и данных фигур.
 */

/**
 * @brief Копирует данные из статической матрицы 4x4 в фигуру.
 * @param destination_figure Указатель на фигуру-назначение.
 * @param src Исходная матрица 4x4.
 * @return 0 при успехе, RUNTIME_ERROR при ошибке (невалидные указатели).
 * @note Размер матрицы фиксирован - 4x4 (размер фигуры в Тетрисе).
 */
int CopyMatrix2dToFigure(figure_t *destination_figure, const int src[4][4]) {
  if (destination_figure == NULL || destination_figure->matrix == NULL ||
      src == NULL)
    return RUNTIME_ERROR;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      destination_figure->matrix[i][j] = src[i][j];
    }
  }
  return 0;
}

/**
 * @brief Копирует данные из динамической матрицы в фигуру.
 * @param destination_figure Указатель на фигуру-назначение.
 * @param src Указатель на исходную матрицу (int**).
 * @return 0 при успехе, RUNTIME_ERROR при ошибке (невалидные указатели).
 * @note Ожидается матрица 4x4, но проверка размера не выполняется.
 */
int CopyMatrixPtrToFigure(figure_t *destination_figure, int **src) {
  if (destination_figure == NULL || destination_figure->matrix == NULL ||
      src == NULL)
    return RUNTIME_ERROR;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      destination_figure->matrix[i][j] = src[i][j];
    }
  }
  return 0;
}

/**
 * @brief Копирует данные между двумя динамическими матрицами.
 * @param destination Указатель на матрицу-назначение.
 * @param src Указатель на исходную матрицу.
 * @return 0 при успехе, RUNTIME_ERROR при ошибке (невалидные указатели).
 * @note Ожидается, что обе матрицы имеют размер 4x4.
 */
int CopyMatrixToMatrix(int **destination, int **src) {
  if (destination == NULL || src == NULL) return RUNTIME_ERROR;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      destination[i][j] = src[i][j];
    }
  }
  return 0;
}