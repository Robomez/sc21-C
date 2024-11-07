#include "../../s21_decimal.h"

/**
 * @brief Преобразует большое число (s21_big) в десятичное число (s21_decimal).
 *
 * Эта функция делит мантиссу big на 10 и уменьшает экспоненту на 1, пока оно не
 * влезет в decimal Если экспонента дошла до -1 и big всё ещё не влезает, это
 * означает, что число слишком велико и должно быть представлено как
 * бесконечность.
 *
 * @param big Указатель на большое число, которое нужно преобразовать.
 * @param decimal Указатель на десятичное число, в которое будет записан
 * результат.
 * @return int Код ошибки:
 * 0 - OK
 * 1 - число слишком велико и представлено как бесконечность
 */
int s21_big_to_decimal(s21_big big, s21_decimal *decimal) {
  s21_big temp_big = big;

  int cur_precision = s21_big_precision_get(big);
  int result = 0;
  int fits_dec_before = 1;
  int temp_remainder = -1;

  if (!(temp_big.bits[NUMBER_BIG_HI] == 0 &&
        temp_big.bits[NUMBER_BIG_MID] == 0 &&
        temp_big.bits[NUMBER_BIG_LOW] == 0))
    fits_dec_before = 0;

  while (!(temp_big.bits[NUMBER_BIG_HI] == 0 &&
           temp_big.bits[NUMBER_BIG_MID] == 0 &&
           temp_big.bits[NUMBER_BIG_LOW] == 0) &&
         cur_precision > -1) {
    temp_remainder = s21_big_div10(&temp_big);
    cur_precision--;
  }

  // если экспонента уже 0, а за границы decimal вышли,
  // значит оно большое в бесконечность
  if (cur_precision == -1)
    result = 1;
  else {
    decimal->bits[NUMBER_FLAGS] = temp_big.bits[NUMBER_BIG_FLAGS];
    for (int i = 0; i < NUMBER_FLAGS; i++) {
      decimal->bits[i] = temp_big.bits[i];
    }
    result = 0;
  }

  // Банковское округление. 1)Если последний остаток от деления 0-4 не делаем
  // ничего, уже ушло вниз. 2)Если остаток больше 5, округляем bits[0] вверх.
  // 4)Если остаток 5, смотрим последнюю цифру bits[0]. 4а)Если она нечётная,
  // ничего не делаем, уже ушло вниз. 4б)Если чётная, округляем bits[0] вверх
  if (result == 0) {
    if (fits_dec_before == 0) {
      if (temp_remainder > 5)
        decimal->bits[0]++;
      else if (temp_remainder == 5) {
        int last_digit = decimal->bits[0] % 10;
        if (last_digit % 2 != 0) decimal->bits[0]++;
      }
    }
  }

  return result;
}