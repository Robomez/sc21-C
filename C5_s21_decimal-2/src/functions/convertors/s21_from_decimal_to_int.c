#include "../../s21_decimal.h"

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  s21_big temp_big = s21_decimal_to_big(src);

  int flag = 0;
  if (!dst) {
    flag = 1;
  } else {
    *dst = 0;
    int sign = s21_decimal_sign_get(src);
    int scale = s21_decimal_precision_get(src);
    if (scale > 28) {
      flag = 1;
    } else {
      for (int i = scale; i > 0; i--) {
        s21_big_div10(&temp_big);
      }
      for (int i = NUMBER_BIG_HI; i > NUMBER_LOW; i--) {
        if (temp_big.bits[i] != 0) flag = 1;
      }
      if ((temp_big.bits[NUMBER_LOW] >> 31) & 1) flag = 1;
      if (flag != 1) {
        *dst = sign ? -temp_big.bits[NUMBER_LOW] : temp_big.bits[NUMBER_LOW];
      }
    }
  }
  return flag;
}
