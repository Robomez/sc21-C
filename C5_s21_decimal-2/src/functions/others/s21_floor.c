#include "../../s21_decimal.h"

int s21_floor(s21_decimal value, s21_decimal *result) {
  int ret = 0;
  if (result == NULL) {
    ret = 1;
  } else {
    int sign = s21_decimal_sign_get(value);
    s21_decimal truncated;
    s21_truncate(value, &truncated);

    if (sign && !s21_is_equal(value, truncated)) {
      s21_decimal one = {{1, 0, 0, 0}};
      s21_decimal temp = {0};
      s21_sub(truncated, one, &temp);
      *result = temp;
    } else {
      *result = truncated;
    }

    s21_decimal_sign_set(result, sign);
  }

  return ret;
}