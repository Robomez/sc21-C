#include "../../s21_decimal.h"

int s21_is_greater_or_equal(s21_decimal deca, s21_decimal decb) {
  int result = 0;
  result = s21_is_equal(deca, decb);
  if (result != 1) result = s21_is_greater(deca, decb);
  return result;
}