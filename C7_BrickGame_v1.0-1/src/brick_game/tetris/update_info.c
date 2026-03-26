#include "backend_internal.h"

/**
 * @file update_info.c
 * @brief Функции для обновления игрового состояния.
 */

/**
 * @brief Преобразует значение клетки поля в бинарное (0 или 1).
 * @param game_info Указатель на структуру с игровой информацией.
 * @param ul_row Индекс строки клетки.
 * @param ul_col Индекс столбца клетки.
 */
void BindFieldCell(GameInfo_t *game_info, int ul_row, int ul_col) {
  game_info->field[ul_row][ul_col] =
      game_info->field[ul_row][ul_col] != FIELD_SIGN_EMPTY ? FIELD_SIGN_TERRAIN
                                                           : FIELD_SIGN_EMPTY;
}

/**
 * @brief Обрабатывает заполненные линии на игровом поле.
 * @param game_info Указатель на структуру с игровой информацией.
 * @return Количество удалённых линий.
 */
int CollapseGameField(GameInfo_t *game_info) {
  int lines_number = 0;
  int **new_field = {0};
  AllocateArray(&new_field, FIELD_HEIGHT, FIELD_WIDTH);

  int dest_row = FIELD_HEIGHT - 1;
  for (int i = FIELD_HEIGHT - 1; i >= 0; i--) {
    int row_sum = 0;
    for (int j = 0; j < FIELD_WIDTH; j++) {
      BindFieldCell(game_info, i, j);
      row_sum += game_info->field[i][j];
      new_field[dest_row][j] = game_info->field[i][j];
    }

    if (row_sum == FIELD_WIDTH) {
      lines_number++;
      dest_row++;
    }
    dest_row--;
  }

  CopyField(game_info->field, new_field, FIELD_HEIGHT, FIELD_WIDTH);

  FreeArray(new_field, FIELD_HEIGHT);
  return lines_number;
}

/**
 * @brief Обновляет игровую информацию после хода.
 * @param game_info Указатель на структуру с игровой информацией.
 * @note Обновляет:
 * - Счёт (учитывая удалённые линии)
 * - Рекорд (если текущий счёт его превышает)
 * - Уровень (на основе текущего счёта)
 * - Скорость игры (на основе уровня)
 */
void UpdateGameInfo(GameInfo_t *game_info) {
  int lines_number = CollapseGameField(game_info);

  game_info->score += CountScore(lines_number);
  UpdateHighScore(game_info);
  game_info->level = GetLevelFromScore(game_info->score);
  game_info->speed = GetSpeedFromLevel(game_info->level);
}