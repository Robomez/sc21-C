#include "../../s21_decimal.h"

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  int result = 0;
  if (dst == NULL) {
    result = 1;
  } else {
    s21_decimal_to_zero(dst);
    if (src < 0) {
      s21_decimal_sign_set(dst, 1);
      dst->bits[NUMBER_LOW] = -src;
    } else {
      dst->bits[NUMBER_LOW] = src;
    }
  }
  return result;
}
