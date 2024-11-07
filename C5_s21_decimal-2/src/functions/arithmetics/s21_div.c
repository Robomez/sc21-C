#include "../../s21_decimal.h"

int s21_big_div_remain(s21_big temp_result, s21_big value_1, s21_big value_2,
                       s21_big *result, int precision);

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  s21_decimal temp_result = {{0}};
  int flag = 0, precision = 0;
  int rem = 0, precision_rem = 0;
  s21_big big_value_1 = s21_decimal_to_big(value_1);
  s21_big big_value_2 = s21_decimal_to_big(value_2);
  s21_big big_result = {{0}}, result_rem = {{0}};

  // проверили данные
  if (result != NULL || s21_decimal_is_ok(value_1) ||
      s21_decimal_is_ok(value_2)) {
    //  на 0 делить нельзя
    if (s21_decimal_is_zero(value_2))
      flag = 3;
    else if (s21_decimal_is_zero(value_1))
      flag = 4;

    if (flag == 0) {
      int sign = s21_decimal_sign_get(value_1) ^ s21_decimal_sign_get(value_2);

      s21_decimal_to_zero(result);

      s21_big_normalize(&big_value_1, &big_value_2);
      precision = s21_big_precision_get(big_value_1);

      rem = s21_big_div(big_value_1, big_value_2, &big_result);
      precision = 0;
      if (rem)
        // if (topa)
        precision_rem = s21_big_div_remain(big_result, big_value_1, big_value_2,
                                           &result_rem, precision);

      precision = precision_rem;

      for (int i = precision_rem; i > 0; i--) s21_big_mul10(&big_result);

      big_result = s21_big_mantissa_add(big_result, result_rem);
      int itog = s21_big_to_decimal(big_result, &temp_result);

      if (itog == 1 && sign == 0)
        flag = 1;
      else if (itog == 1 && sign == 1)
        flag = 2;

      if (flag == 0) {
        s21_decimal_precision_set(&temp_result, precision);
        s21_decimal_sign_set(&temp_result, sign);

        *result = temp_result;
      }

    } else if (flag == 4)
      flag = 0;
  } else
    flag = 4;

  return flag;
}

// Делим остаток от первого деления бигов
int s21_big_div_remain(s21_big temp_result, s21_big value_1, s21_big value_2,
                       s21_big *result, int precision) {
  s21_big src = {{0}}, c_res = {{0}};
  int precision_rem = 0, rem = 1;

  while (rem != 0 && (precision + precision_rem != 40)) {
    s21_big_mul(temp_result, value_2, &src);
    src = s21_big_mantissa_sub(value_1, src);
    s21_big_mul10(&src);
    value_1 = src;
    rem = s21_big_div(src, value_2, &src);

    if (!s21_big_is_zero(c_res)) {
      s21_big_mul10(&c_res);
      c_res = s21_big_mantissa_add(c_res, src);
    } else
      c_res = src;

    temp_result = src;
    s21_big_to_zero(&src);
    precision_rem++;
  }

  *result = c_res;

  return precision_rem;
}