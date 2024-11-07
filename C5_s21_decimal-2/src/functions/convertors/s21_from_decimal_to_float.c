#include <math.h>

#include "../../s21_decimal.h"

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  int ret = 0;

  if (dst == NULL) {
    ret = 1;
  } else {
    int sign = s21_decimal_sign_get(src);
    int precision = s21_decimal_precision_get(src);

    double result = 0.0;
    for (int i = 0; i < 96; i++) {
      if (s21_bit_get(src.bits[i / 32], i % 32)) {
        result += pow(2.0, i % 32);
      }
    }

    while (precision > 0) {
      unsigned rest = 0;
      s21_decimal_div10(&src, &rest);
      result /= 10.0;
      precision--;
    }

    if (sign) {
      result = -result;
    }
    *dst = (float)result;
  }

  return ret;
}