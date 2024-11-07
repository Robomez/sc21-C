#include "../../s21_decimal.h"

/* Сложение двух децималов.
На вход принимаются два слагаемых и адрес результата.
На выходе int 0 — OK;
              1 — число слишком велико или равно бесконечности;
              2 — число слишком мало или равно отрицательной бесконечности;*/
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int salut = 0;
  s21_big big_result = {0};
  // переводим в биги
  s21_big big1 = s21_decimal_to_big(value_1);
  s21_big big2 = s21_decimal_to_big(value_2);
  // нормализуем. вообще по идее экспонента не может быть более 28?
  s21_big_normalize(&big1, &big2);
  // смотрим знаки, если + то просто сложить
  int sign1 = s21_big_sign_get(big1);
  int sign2 = s21_big_sign_get(big2);
  // если минус, то у кого мантисса больше, из той вычесть вторую. знак итоговый
  // от этого сравнения тоже
  if (sign1 != sign2) {
    int is_greater = s21_big_is_mantissa_greater(big1, big2);
    if (is_greater)
      big_result = s21_big_mantissa_sub(big1, big2);
    else
      big_result = s21_big_mantissa_sub(big2, big1);
  } else {
    big_result = s21_big_mantissa_add(big1, big2);
  }

  // привести результат в decimal
  int conversion_result = s21_big_to_decimal(big_result, result);
  int sign = s21_big_sign_get(big_result);
  if (conversion_result == 1 && sign == 0)
    salut = 1;
  else if (conversion_result == 1 && sign == 1)
    salut = 2;

  return salut;
}
