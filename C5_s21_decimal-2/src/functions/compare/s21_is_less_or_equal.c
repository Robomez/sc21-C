#include "../../s21_decimal.h"

int s21_is_less_or_equal(s21_decimal deca, s21_decimal decb) {
  int result = 0;
  result = s21_is_equal(deca, decb);
  if (result != 1) result = s21_is_less(deca, decb);
  return result;
}