#include "../../s21_decimal.h"

int s21_is_less(s21_decimal deca, s21_decimal decb) {
  int result = 2;
  result = s21_is_greater(decb, deca);
  return result;
}