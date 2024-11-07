#include "../../s21_decimal.h"

void s21_decimal_remove_zeros(s21_decimal *value) {
  s21_decimal c_value = *value;
  int precision = s21_decimal_precision_get(c_value);
  uint32_t remainder = 0;

  while (precision != 0 && remainder == 0) {
    if (s21_decimal_div10(&c_value, &remainder) == 0) {
      uint32_t b = 0;
      s21_decimal_div10(value, &b);
      precision--;
    }
  }

  s21_decimal_precision_set(value, precision);
}
