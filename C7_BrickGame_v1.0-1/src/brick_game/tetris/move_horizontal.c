#include "backend_internal.h"

/**
 * @file move_horizontal.c
 * @brief Функции для горизонтального перемещения фигуры.
 */

/**
 * @brief Передвигает фигуру влево или вправо на одну клетку.
 * @param direction Направление движения (DirectionLeft или DirectionRight).
 * @param game_info Указатель на информацию об игре.
 * @param figure Указатель на текущую фигуру.
 * @return 0 в случае успеха, RUNTIME_ERROR в случае ошибки.
 */
int MoveHorizontal(direction_t direction, GameInfo_t *game_info,
                   figure_t *figure) {
  int **v_field = NULL;
  figure_t v_figure = {0};
  int d_col = 0;
  int can_move = 0;
  int has_collisions = 0;

  if (direction == DirectionLeft) {
    d_col = -1;
  } else if (direction == DirectionRight) {
    d_col = 1;
  }

  if (!CheckDataPointers(game_info, figure)) has_collisions = RUNTIME_ERROR;

  if (d_col != 0 && !has_collisions) {
    if (direction == DirectionLeft && figure->ul_col + d_col >= 0) {
      can_move = 1;
    } else if (direction == DirectionRight &&
               figure->ul_col + figure->cols + d_col <= FIELD_WIDTH) {
      can_move = 1;
    }
  }

  if (can_move) {
    if (MakeVirtualData(game_info, figure, &v_field, &v_figure) !=
        RUNTIME_ERROR) {
      DeleteFigure(v_field, figure);
      v_figure.ul_col += d_col;

      has_collisions = PositionFigure(v_field, &v_figure);
      if (!has_collisions) {
        CopyField(game_info->field, v_field, FIELD_HEIGHT, FIELD_WIDTH);
        figure->ul_col = v_figure.ul_col;
      }

      FreeVirtualData(v_field, &v_figure);
    }
  }

  return has_collisions;
}