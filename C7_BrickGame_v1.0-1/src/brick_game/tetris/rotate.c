#include "backend_internal.h"
/**
 * @file rotate.c
 * @brief Функции для вращения фигуры.
 */

/**
 * @brief Вращает матрицу фигуры на 90 градусов по часовой стрелке.
 * @param figure Указатель на структуру фигуры.
 * @return 0 в случае успеха, RUNTIME_ERROR в случае ошибки.
 */
int Rotate(figure_t *figure) {
  if (figure == NULL || figure->matrix == NULL) return RUNTIME_ERROR;

  int new_matrix[4][4] = {0};
  int rows = figure->rows;
  int cols = figure->cols;

  for (int ul_row = 0; ul_row < rows; ul_row++) {
    for (int ul_col = 0; ul_col < cols; ul_col++) {
      new_matrix[ul_col][rows - ul_row - 1] = figure->matrix[ul_row][ul_col];
    }
  }

  CopyMatrixToFigure(figure, new_matrix);
  figure->rows = cols;
  figure->cols = rows;

  return 0;
}

/**
 * @brief Вращает фигуру в поле.
 * @param game_info Указатель на информацию об игре.
 * @param figure Указатель на текущую фигуру.
 * @return 0 в случае успеха, RUNTIME_ERROR в случае ошибки.
 */
int RotateInField(GameInfo_t *game_info, figure_t *figure) {
  if (!CheckDataPointers(game_info, figure) ||
      (figure->ul_row + figure->cols >= FIELD_HEIGHT)) {
    return RUNTIME_ERROR;
  }

  int **virtual_field = NULL;
  figure_t virtual_figure = {0};
  int collided = 0;
  if (MakeVirtualData(game_info, figure, &virtual_field, &virtual_figure) !=
      -1) {
    DeleteFigure(virtual_field, figure);
    if (figure->ul_col + figure->rows > FIELD_WIDTH) {
      virtual_figure.ul_col = FIELD_WIDTH - figure->rows;
    }
    Rotate(&virtual_figure);
    collided = PositionFigure(virtual_field, &virtual_figure);
    if (!collided) {
      CopyField(game_info->field, virtual_field, FIELD_HEIGHT, FIELD_WIDTH);
      DuplicateFigure(figure, &virtual_figure);
    }
    FreeVirtualData(virtual_field, &virtual_figure);
  }

  return collided;
}
