#include "../../../s21_decimal.h"

/**
 * @brief Складывает мантиссы двух больших чисел (s21_big).
 *
 * Эта функция выполняет сложение мантисс двух больших чисел.
 * Числа должны быть нормализованы.
 * Это необходимо для умножения на 10 и при s21_add. В процессе сложения
 * проверяется, не превышает ли результирующая мантисса 96 бит. Если превышает,
 * в терминал выводится сообщение "WRONG"(потому что такого не может быть в
 * принципе). Функция возвращает результат сложения в формате s21_big.
 *
 * @param big1 Первое большое число (s21_big).
 * @param big2 Второе большое число (s21_big).
 * @return s21_big Результат сложения мантисс.
 */
s21_big s21_big_mantissa_add(s21_big big1, s21_big big2) {
  s21_big result = big1;
  uint32_t temp_number = 0;
  int carry = 0;
  int wrong = 0;

  for (int i = 0; i < 6; i++) {
    int carry_more = s21_numbers_add(big1.bits[i], big2.bits[i], &temp_number);
    wrong = s21_numbers_add(temp_number, carry, &(result.bits[i]));

    if (wrong) printf("WRONG!\n");

    carry = carry_more;
  }
  return result;
}