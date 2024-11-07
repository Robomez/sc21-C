#include "../../s21_decimal.h"

int s21_truncate(s21_decimal value, s21_decimal *result) {
  int res = 0;

  if (result == NULL) res = 1;

  if (res == 0) {
    int scale = s21_decimal_precision_get(value);
    int sign = s21_decimal_sign_get(value);

    s21_decimal temp = value;
    uint32_t remainder = 0;

    for (int i = 0; i < scale; i++) {
      s21_decimal_div10(&temp, &remainder);
    }

    *result = temp;
    s21_decimal_sign_set(result, sign);
    s21_decimal_precision_set(result, 0);
  }

  return res;
}
