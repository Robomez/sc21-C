#include "../../s21_decimal.h"

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int flag = 0;
  s21_decimal c_result = {{0}};

  // проверили данные
  if (result != NULL || s21_decimal_is_ok(value_1) ||
      s21_decimal_is_ok(value_2)) {
    // если данные нормальные, запускаем умножение
    // перевели в биг
    s21_big big_value_1 = s21_decimal_to_big(value_1);
    s21_big big_value_2 = s21_decimal_to_big(value_2);

    int sign_res =
        s21_big_sign_get(big_value_1) ^ s21_big_sign_get(big_value_2);
    // обнулить результат
    s21_big big_result = {{0}};
    s21_decimal_to_zero(result);

    // если множимые не равны нулю, продолжаем, иначе вернём 0.
    if (!s21_decimal_is_zero(value_1) && !s21_decimal_is_zero(value_2)) {
      // Нормализуем к одной степени биги
      // s21_big_normalize(&big_value_1, &big_value_2);

      // умножаем биги
      s21_big_mul(big_value_1, big_value_2, &big_result);

      // переводим биг результ в дец
      int itog = s21_big_to_decimal(big_result, &c_result);

      // если не влез и знак 0, то бесконечность(вернём 1)
      // если не влез и знак 1, то отрицательная бесконечность (вернём 2);
      if (itog == 1 && sign_res == 0)
        flag = 1;
      else if (itog == 1 && sign_res == 1)
        flag = 2;

      // Если влез, тогда результату присваиваем значение
      if (flag == 0) {
        *result = c_result;
      }
    } else {
      flag = 0;
    }
  }

  s21_decimal_remove_zeros(result);

  return flag;
}
