#include "backend_internal.h"

/**
 * @file score.c
 * @brief Функции для работы с очками и рекордами.
 */

/**
 * @brief Подсчитывает количество очков за удалённые линии.
 * @param lines_number Количество удалённых линий (0-4).
 * @return Количество начисленных очков.
 */
int CountScore(int lines_number) {
  int scores[] = {0, POINTS_1_LINE, POINTS_2_LINES, POINTS_3_LINES,
                  POINTS_4_LINES};

  return scores[lines_number];
}

/**
 * @brief Читает рекорд из файла.
 * @return Текущий рекорд, или 0 если файл не существует.
 */
int ReadHighScore() {
  int high_score = 0;
  FILE *file = fopen(HIGH_SCORE_FILE, "r+");
  if (file != NULL) {
    fscanf(file, "%d", &high_score);
    fclose(file);
  }
  return high_score;
}

/**
 * @brief Записывает рекорд в файл.
 * @param high_score Новое значение рекорда.
 */
void WriteHighScore(int high_score) {
  FILE *file = fopen(HIGH_SCORE_FILE, "w+");
  fprintf(file, "%d", high_score);
  fclose(file);
}

/**
 * @brief Обновляет рекорд, если текущий счёт его превышает.
 * @param game_info Указатель на структуру с игровой информацией.
 */
void UpdateHighScore(GameInfo_t *game_info) {
  if (game_info->score > game_info->high_score) {
    game_info->high_score = game_info->score;
    WriteHighScore(game_info->high_score);
  }
}