#include "../../../s21_decimal.h"

/**
 * @brief Проверяет, больше ли мантисса первого большого числа (s21_big) чем
 * мантисса второго.
 *
 * @param biga Первое большое число (s21_big) для проверки.
 * @param bigb Второе большое число (s21_big) для сравнения.
 * @return int Результат проверки:
 *  - 1: Если мантисса biga больше.
 *  - 0: Если мантисса bigb больше или мантиссы равны.
 */
int s21_big_is_mantissa_greater(s21_big biga, s21_big bigb) {
  int result = 2;

  for (int i = NUMBER_BIG_HI; i >= 0 && result == 2; i--) {
    if (biga.bits[i] < bigb.bits[i]) result = 0;
    if (biga.bits[i] > bigb.bits[i]) result = 1;
  }
  if (result == 2) result = 0;

  return result;
}