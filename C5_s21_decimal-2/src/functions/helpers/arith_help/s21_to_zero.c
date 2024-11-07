#include "../../../s21_decimal.h"

/**
 * @brief Обнуляет decimal, включая последний бит с степенью и знаком
 * @param decimal (s21_decimal *) адрес децимала.
 * @return void
 */
void s21_decimal_to_zero(s21_decimal *decimal) {
  for (int i = NUMBER_LOW; i <= NUMBER_FLAGS; i++) {
    decimal->bits[i] = 0;
  }
}

/**
 * @brief Обнуляет big, включая последний бит с степенью и знаком
 * @param big (s21_big *) адрес децимала.
 * @return void
 */
void s21_big_to_zero(s21_big *big) {
  for (int i = NUMBER_LOW; i <= NUMBER_BIG_FLAGS; i++) {
    big->bits[i] = 0;
  }
}