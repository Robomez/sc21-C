#include "backend_internal.h"

/**
 * @file create_figure.c
 * @brief Функции для создания, инициализации и управления фигурами.
 */

/**
 * @brief Инициализирует фигуру заданного типа.
 * @param figure_type Тип фигуры (0-6).
 * @param result_figure Указатель на структуру фигуры для инициализации.
 * @return 0 в случае успеха, RUNTIME_ERROR в случае ошибки.
 */
int InitFigure(int figure_type, figure_t* result_figure) {
  if (result_figure == NULL || figure_type < 0 || figure_type > 6)
    return RUNTIME_ERROR;
  int result = 0;

  const int X = FIELD_SIGN_FIGURE;

  static const int figure_data[7][4][4] = {
      {{X, 0, 0, 0}, {X, 0, 0, 0}, {X, 0, 0, 0}, {X, 0, 0, 0}},  // I
      {{0, X, 0, 0}, {0, X, 0, 0}, {X, X, 0, 0}, {0, 0, 0, 0}},  // J
      {{X, 0, 0, 0}, {X, 0, 0, 0}, {X, X, 0, 0}, {0, 0, 0, 0}},  // L
      {{X, X, 0, 0}, {X, X, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},  // O
      {{0, X, X, 0}, {X, X, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},  // S
      {{X, X, X, 0}, {0, X, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},  // T
      {{X, X, 0, 0}, {0, X, X, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}}   // Z
  };

  static const int sizes[7][2] = {
      {4, 1},  // I
      {3, 2},  // J
      {3, 2},  // L
      {2, 2},  // O
      {2, 3},  // S
      {2, 3},  // T
      {2, 3}   // Z
  };

  if (result_figure->matrix == NULL) result = createEmptyFigure(result_figure);
  result_figure->rows = sizes[figure_type][0];
  result_figure->cols = sizes[figure_type][1];

  result = CopyMatrixToFigure(result_figure, figure_data[figure_type]);
  return result;
}

/**
 * @brief Создает пустую фигуру с заданными размерами.
 * @param figure Указатель на структуру фигуры.
 * @return 0 в случае успеха, RUNTIME_ERROR в случае ошибки.
 */
int createEmptyFigure(figure_t* figure) {
  int result = 0;
  figure->ul_row = 0;
  figure->ul_col = 0;
  figure->rows = 0;
  figure->cols = 0;
  result = AllocateArray(&(figure->matrix), NEXT_FIGURE_ROWS, NEXT_FIGURE_COLS);

  return result;
}