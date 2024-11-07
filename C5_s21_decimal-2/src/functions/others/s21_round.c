#include "../../s21_decimal.h"

int banking(s21_decimal *temp);

int s21_round(s21_decimal value, s21_decimal *result) {
  int ret = 0;
  s21_decimal temp = value;

  if (result == NULL) {
    ret = 1;
  } else {
    int scale = s21_decimal_precision_get(value);
    int sign = s21_decimal_sign_get(value);

    if (scale == 0) {
      *result = value;
      ret = 0;
    } else {
      unsigned remainder = 0;

      while (scale > 1) {
        s21_decimal_div10(&temp, &remainder);
        scale--;
      }

      s21_decimal_div10(&temp, &remainder);

      if (remainder >= 5) {
        banking(&temp);
      }
    }

    *result = temp;
    s21_decimal_sign_set(result, sign);
    s21_decimal_precision_set(result, 0);
  }

  return ret;
}

int banking(s21_decimal *temp) {
  int carry = 1, ret = 0;
  for (int i = 0; i < 96 && carry; i++) {
    int bit = s21_bit_get(temp->bits[i / 32], i % 32);
    if (bit == 0) {
      s21_bit_set(&temp->bits[i / 32], i % 32, 1);
      carry = 0;
    } else {
      s21_bit_set(&temp->bits[i / 32], i % 32, 0);
    }
  }

  if (carry) {
    ret = 2;
  }
  return ret;
}