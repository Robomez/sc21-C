#include "../../s21_decimal.h"

int s21_negate(s21_decimal value, s21_decimal *result) {
  int result_code = 0;
  if (s21_decimal_is_ok(value) && result != NULL) {
    *result = value;
    s21_bit_reverse(&(result->bits[NUMBER_FLAGS]), POSITION_SIGN);
    result_code = 0;
  } else {
    result_code = 1;
  }
  return result_code;
}