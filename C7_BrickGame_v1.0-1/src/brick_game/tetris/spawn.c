#include "backend_internal.h"

/**
 * @file spawn.c
 * @brief Функции для работы с появлением новых фигур.
 */

/**
 * @brief Переносит следующую фигуру в текущую и генерирует новую следующую.
 * @param game_info Указатель на структуру с игровой информацией.
 * @param current_figure Указатель на текущую фигуру.
 * @param next_figure Указатель на следующую фигуру.
 * @return 1 если произошло столкновение, 0 в противном случае.
 */
int SpawnFigure(GameInfo_t *game_info, figure_t *current_figure,
                figure_t *next_figure) {
  int collided = PositionFigure(game_info->field, next_figure);
  if (!collided) {
    DuplicateFigure(current_figure, next_figure);
    GenerateNextFigure(next_figure);
    CopyMatrixToMatrix(game_info->next, next_figure->matrix);
  }

  return collided;
}