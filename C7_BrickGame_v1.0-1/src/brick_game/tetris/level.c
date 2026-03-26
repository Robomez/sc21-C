#include "./backend_internal.h"

/**
 * @file level.c
 * @brief Функции для работы с уровнями и скоростью игры.
 */

/**
 * @brief Определяет уровень игры на основе набранных очков.
 * @param score Текущий счет.
 * @return Текущий уровень игры.
 */
int GetLevelFromScore(int score) {
  int level = score / LEVEL_SCORE + 1;
  return level > MAX_LEVEL ? MAX_LEVEL : level;
}

/**
 * @brief Определяет скорость падения фигуры в зависимости от уровня.
 * @param level Текущий уровень игры.
 * @return Скорость в миллисекундах.
 */
int GetSpeedFromLevel(int level) {
  level = level < 1 ? 1 : level > MAX_LEVEL ? MAX_LEVEL : level;

  int speed = SPEED_BASE - SPEED_STEP * (level - 1);
  return speed;
}
