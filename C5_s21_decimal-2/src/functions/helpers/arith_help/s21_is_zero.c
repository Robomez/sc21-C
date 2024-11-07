#include "../../../s21_decimal.h"

/**
 * @brief Проверяет, является ли мантисса decimal равной нулю
 * @param value (s21_decimal).
 * @return int Код результата:
 *  - 1: Если верно, что пустой (только 0).
 *  - 0: Если не верно (есть данные внутри мантиссы).
 */
int s21_decimal_is_zero(s21_decimal value) {
  return !value.bits[0] && !value.bits[1] && !value.bits[2];
}

/**
 * @brief Проверяет, является ли мантисса big равной нулю
 * @param value (s21_big).
 * @return int Код результата:
 *  - 1: Если верно, что пустой (только 0).
 *  - 0: Если не верно (есть данные внутри мантиссы).
 */
int s21_big_is_zero(s21_big value) {
  int result = 1;
  for (int i = NUMBER_LOW; i < NUMBER_BIG_FLAGS && result == 1; i++) {
    if (value.bits[i] != 0) result = 0;
  }
  return result;
}