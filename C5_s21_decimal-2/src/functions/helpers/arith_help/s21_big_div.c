#include "../../../s21_decimal.h"

/**
 * @brief Деление двух чисел типа s21_big.
 *
 * Функция выполняет побитное деление двух больших чисел типа s21_big.
 * Сначала выравнивает старшие биты делимого и делителя, затем выполняет
 * побитное деление, сдвигая и уменьшая делимое. Остаток после деления
 * сохраняется в переменной rem.
 *
 * @param value_1 Делимое (число типа s21_big).
 * @param value_2 Делитель (число типа s21_big).
 * @param result Указатель на результат деления (частное).
 * @return int Остаток после деления:
 *  - 5: Если остаток равен 5, используется для банковского округления.
 *  - 1: Если есть ненулевой остаток.
 *  - 0: Если результат деления точный (остаток равен нулю).
 */

// Делим биги
int s21_big_div(s21_big value_1, s21_big value_2, s21_big *result) {
  s21_big_to_zero(result);

  s21_big temp_result = {{0}}, sub = value_1;
  int bit_value_2 = 0, bit_value_1 = 0, rem = 0;

  // Находим, разницу в количестве битов у бигов
  for (int i = 0; i < 192; i++) {
    if (s21_bit_get(value_1.bits[i / 32], i % 32) == 1) bit_value_1 = i;
    if (s21_bit_get(value_2.bits[i / 32], i % 32) == 1) bit_value_2 = i;
  }
  int i = bit_value_1 - bit_value_2, flag = 0;

  // Смещаем делимое по битам на разницу, чтобы старший бит был одинаковым
  for (int y = i; y > 0; y--) s21_big_shift_right(&sub);

  // Само деление
  while (i >= 0) {
    if (!s21_big_is_mantissa_greater(value_2, sub)) {
      s21_big_shift_left(&temp_result);
      s21_bit_set(&temp_result.bits[0], 0, 1);
      sub = s21_big_mantissa_sub(sub, value_2);
      flag = 1;
    } else {
      i--;
      if (flag == 0)
        s21_big_shift_left(&temp_result);
      else
        flag = 0;
      s21_big_shift_left(&sub);
      s21_bit_set(&sub.bits[0], 0, s21_bit_get(value_1.bits[i / 32], i % 32));
    }
  }

  if (sub.bits[0] == 5) rem = 5;
  if (!s21_big_is_zero(sub)) rem = 1;
  if (s21_big_is_mantissa_greater(value_2, value_1)) rem = 1;
  if (s21_big_is_zero(value_1)) rem = 0;

  *result = temp_result;

  return rem;
}