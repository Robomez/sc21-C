#include "backend_internal.h"

/**
 * @file move_down.c
 * @brief Функции для управления движением фигуры вниз.
 */

/**
 * @brief Передвигает фигуру на одну клетку вниз.
 * @param game_info Указатель на информацию об игре.
 * @param figure Указатель на текущую фигуру.
 * @return 0, если движение возможно, 1, если фигура достигла дна или другой
 * фигуры.
 */
int MoveDown(GameInfo_t *game_info, figure_t *figure) {
  if (!CheckDataPointers(game_info, figure) ||
      (figure->ul_row + figure->rows >= FIELD_HEIGHT)) {
    return RUNTIME_ERROR;
  }

  int **v_field = NULL;
  figure_t v_figure = {0};
  int collided = 0;

  if (MakeVirtualData(game_info, figure, &v_field, &v_figure) !=
      RUNTIME_ERROR) {
    DeleteFigure(v_field, figure);
    v_figure.ul_row += 1;
    collided = PositionFigure(v_field, &v_figure);
    if (!collided) {
      CopyField(game_info->field, v_field, FIELD_HEIGHT, FIELD_WIDTH);
      figure->ul_row = v_figure.ul_row;
    }
    FreeVirtualData(v_field, &v_figure);
  }

  return collided;
}

/**
 * @brief Быстро опускает фигуру до самого низа.
 * @param game_info Указатель на информацию об игре.
 * @param figure Указатель на текущую фигуру.
 */
void Drop(GameInfo_t *game_info, figure_t *figure) {
  while (MoveDown(game_info, figure) == 0) {
  }
}