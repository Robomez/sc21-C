#include "./backend_internal.h"

/**
 * @file memory_manager.c
 * @brief Функции для управления динамической памятью.
 */

/**
 * @brief Выделяет память для двумерного массива.
 * @param arr Указатель на двумерный массив.
 * @param rows Количество строк.
 * @param cols Количество столбцов.
 * @return 0 в случае успеха, RUNTIME_ERROR в случае ошибки.
 */
int AllocateArray(int ***arr, int rows, int cols) {
  if (rows <= 0 || cols <= 0) return RUNTIME_ERROR;

  int result = 0;
  *arr = calloc(rows, sizeof(int *));
  if (*arr == NULL) result = RUNTIME_ERROR;
  if (result == 0) {
    for (int ul_row = 0; ul_row < rows; ul_row++) {
      (*arr)[ul_row] = calloc(cols, sizeof(int));
      if ((*arr)[ul_row] == NULL) {
        result = RUNTIME_ERROR;

        FreeArray(*arr, ul_row);
        *arr = NULL;
        break;
      }
    }
  }

  return result;
}

/**
 * @brief Проверяет указатели на данные игры и фигуры.
 * @param game_info Указатель на структуру GameInfo_t.
 * @param figure Указатель на структуру figure_t.
 * @return 1, если указатели валидны, иначе 0.
 * @ingroup memory_management
 */
int CheckDataPointers(GameInfo_t *game_info, figure_t *figure) {
  return (!(game_info == NULL || game_info->field == NULL || figure == NULL ||
            figure->matrix == NULL));
}

/**
 * @brief Копирует содержимое одного двумерного массива в другой.
 * @param dst Указатель на массив-назначение.
 * @param src Указатель на исходный массив.
 * @param rows Количество строк.
 * @param cols Количество столбцов.
 * @ingroup memory_management
 */
void CopyField(int **dst, int **src, int rows, int cols) {
  for (int ul_row = 0; ul_row < rows; ul_row++) {
    for (int ul_col = 0; ul_col < cols; ul_col++) {
      dst[ul_row][ul_col] = src[ul_row][ul_col];
    }
  }
}

/**
 * @brief Удаляет фигуру с игрового поля.
 * @param field Указатель на игровое поле.
 * @param figure Указатель на фигуру.
 * @ingroup memory_management
 */
void DeleteFigure(int **field, figure_t *figure) {
  for (int ul_row = 0; ul_row < figure->rows; ul_row++) {
    for (int ul_col = 0; ul_col < figure->cols; ul_col++) {
      if (field[ul_row + figure->ul_row][ul_col + figure->ul_col] ==
          FIELD_SIGN_FIGURE)
        field[ul_row + figure->ul_row][ul_col + figure->ul_col] = 0;
    }
  }
}

/**
 * @brief Размещает фигуру на игровом поле.
 * @param field Указатель на игровое поле.
 * @param figure Указатель на фигуру.
 * @return 1, если произошло столкновение, иначе 0.
 * @ingroup memory_management
 */
int PositionFigure(int **field, figure_t *figure) {
  int collided = 0;

  for (int ul_row = 0; ul_row < figure->rows; ul_row++) {
    for (int ul_col = 0; ul_col < figure->cols; ul_col++) {
      field[ul_row + figure->ul_row][ul_col + figure->ul_col] +=
          figure->matrix[ul_row][ul_col];
      if (field[ul_row + figure->ul_row][ul_col + figure->ul_col] >
          FIELD_SIGN_FIGURE) {
        collided = 1;
        break;
      }
    }
    if (collided == 1) break;
  }

  return collided;
}

/**
 * @brief Копирует фигуру из источника в назначение.
 * @param dst Указатель на фигуру-назначение.
 * @param src Указатель на исходную фигуру.
 * @return 0 в случае успеха, RUNTIME_ERROR в случае ошибки.
 * @ingroup memory_management
 */
int DuplicateFigure(figure_t *dst, figure_t *src) {
  int result = 0;
  if (dst->matrix != NULL ||
      AllocateArray(&(dst->matrix), 4, 4) != RUNTIME_ERROR) {
    CopyMatrixToFigure(dst, src->matrix);
    dst->rows = src->rows;
    dst->cols = src->cols;
    dst->ul_row = src->ul_row;
    dst->ul_col = src->ul_col;
  } else {
    result = RUNTIME_ERROR;
  }
  return result;
}

/**
 * @brief Создает виртуальные данные (поле и фигуру) для проверки столкновений.
 * @param game_info Указатель на информацию об игре.
 * @param figure Указатель на текущую фигуру.
 * @param v_field Указатель на виртуальное поле.
 * @param v_figure Указатель на виртуальную фигуру.
 * @return 0 в случае успеха, RUNTIME_ERROR в случае ошибки.
 */
int MakeVirtualData(GameInfo_t *game_info, figure_t *figure, int ***v_field,
                    figure_t *v_figure) {
  if (!CheckDataPointers(game_info, figure)) return RUNTIME_ERROR;
  if (AllocateArray(v_field, FIELD_HEIGHT, FIELD_WIDTH) != RUNTIME_ERROR) {
    if (DuplicateFigure(v_figure, figure) != RUNTIME_ERROR) {
      CopyField(*v_field, game_info->field, FIELD_HEIGHT, FIELD_WIDTH);
    } else {
      FreeArray(*v_field, FIELD_HEIGHT);
    }
  }

  return 0;
}

/**
 * @brief Освобождает память, выделенную для виртуальных данных.
 * @param virtual_field Указатель на виртуальное поле.
 * @param figure Указатель на виртуальную фигуру.
 */
void FreeVirtualData(int **v_field, figure_t *figure) {
  if (v_field != NULL) FreeArray(v_field, FIELD_HEIGHT);
  if (figure->matrix != NULL) FreeArray(figure->matrix, 4);
  v_field = NULL;
  figure->matrix = NULL;
}

/**
 * @brief Освобождает память, выделенную для двумерного массива.
 * @param array Указатель на двумерный массив.
 * @param rows Количество строк.
 */
void FreeArray(int **arr, int rows) {
  if (arr != NULL && rows > 0) {
    for (int ul_row = 0; ul_row < rows; ul_row++) {
      free(arr[ul_row]);
      arr[ul_row] = NULL;
    }
    free(arr);
    arr = NULL;
  }
}

/**
 * @brief Освобождает всю память, выделенную для игры.
 * @param game_info Указатель на информацию об игре.
 * @param figure Указатель на текущую фигуру.
 * @param next Указатель на следующую фигуру.
 */
void FreeMemory(GameInfo_t *game_info, figure_t *figure, figure_t *next) {
  FreeArray(game_info->field, FIELD_HEIGHT);
  FreeArray(game_info->next, NEXT_FIGURE_ROWS);
  game_info->field = NULL;
  game_info->next = NULL;
  game_info->pause = 0;

  FreeArray(figure->matrix, 4);
  FreeArray(next->matrix, 4);
  figure->matrix = NULL;
  next->matrix = NULL;
}
