#include "../../s21_decimal.h"

int s21_is_greater(s21_decimal deca, s21_decimal decb) {
  int result = 2;

  s21_big biga = s21_decimal_to_big(deca);
  s21_big bigb = s21_decimal_to_big(decb);
  s21_big_normalize(&biga, &bigb);

  int signa = s21_big_sign_get(biga);
  int signb = s21_big_sign_get(bigb);

  switch (signa) {
    case 0:
      if (signb == 1)
        result = 1;
      else if (s21_big_is_mantissa_greater(biga, bigb))
        result = 1;
      else
        result = 0;
      break;
    case 1:
      if (signb == 0)
        result = 0;
      else if (s21_big_is_mantissa_greater(bigb, biga))
        result = 1;
      else
        result = 0;
      break;
  }

  return result;
}