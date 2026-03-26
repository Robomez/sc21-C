#include "backend_internal.h"

/**
 * @file timekeep.c
 * @brief Функции для работы с временем в игре.
 */

/**
 * @brief Получает текущее время в миллисекундах.
 * @return Текущее время в миллисекундах с момента эпохи Unix.
 */
unsigned long long GetTime() {
  struct timeval current;
  gettimeofday(&current, NULL);
  return current.tv_sec * 1000 + current.tv_usec / 1000;
}