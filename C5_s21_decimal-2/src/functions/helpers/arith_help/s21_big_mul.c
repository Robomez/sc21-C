#include "../../../s21_decimal.h"

/**
 * @brief Умножает два числа типа s21_big и сохраняет результат.
 *
 * Функция выполняет побитовое умножение мантисс чисел value_1 и value_2.
 * Знак результата вычисляется с помощью XOR, а точность складывается.
 * Результат сохраняется в *result.
 *
 * @param value_1 Первое число для умножения.
 * @param value_2 Второе число для умножения.
 * @param result Указатель на результат умножения.
 * @return void
 */

void s21_big_mul(s21_big value_1, s21_big value_2, s21_big *result) {
  // получили итоговые знак и показатель степени
  int sign_res = s21_big_sign_get(value_1) ^ s21_big_sign_get(value_2);
  int precision_res =
      s21_big_precision_get(value_1) + s21_big_precision_get(value_2);

  s21_big sdvigaemoe = value_1;
  s21_big_precision_set(&sdvigaemoe, 0);
  s21_big temp_result = {{0}};
  for (int j = NUMBER_LOW; j <= NUMBER_BIG_HI; j++) {
    for (int i = 0; i < 32; i++) {
      if ((value_2.bits[j] >> i) & 1) {
        s21_big temptemp = temp_result;
        temp_result = s21_big_mantissa_add(temptemp, sdvigaemoe);
      }
      s21_big_shift_left(&sdvigaemoe);
    }
  }

  // устанавливаем биг результату знак и степень
  s21_big_sign_set(&temp_result, sign_res);
  s21_big_precision_set(&temp_result, precision_res);
  *result = temp_result;
}