#include "../../../s21_decimal.h"

/**
 * @brief Уменьшает мантиссу децимал числа (s21_decimal).
 *
 * Остаток от деления записывает по адресу. Возвращает также остаток.
 *
 * @param in Указатель на децимал число (s21_decimal), мантисса которого должна
 * быть уменьшена.
 * @param rest Указатель на int адрес остатка, куда записать.
 * @return int остаток от деления на 10.
 */
int s21_decimal_div10(s21_decimal *in, unsigned *rest) {
  uint64_t p_rest = 0;
  int div = 10;
  *rest = 0;
  for (int i = NUMBER_HI; i >= 0; i--) {
    p_rest = *rest * 4294967296 + in->bits[i];
    in->bits[i] = p_rest / div;
    *rest = p_rest - div * in->bits[i];
  }
  return *rest;
}