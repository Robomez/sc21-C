#include "../../s21_decimal.h"

/**
 * @brief Преобразует десятичное число (s21_decimal) в большое число (s21_big).
 *
 * Эта функция принимает десятичное число и копирует его значение в структуру
 * большого числа. При этом старший элемент массива bits в `s21_big` (6)
 * заполняется значением из старшего элемента массива bits в `s21_decimal` (3),
 * а остальные элементы массива bits копируются непосредственно (1-2).
 *
 * @param decimal Десятичное число (s21_decimal), которое нужно преобразовать.
 * @return s21_big Структура большого числа, полученная в результате
 * преобразования.
 */
s21_big s21_decimal_to_big(s21_decimal decimal) {
  s21_big big = {{0}};
  big.bits[NUMBER_BIG_FLAGS] = decimal.bits[NUMBER_FLAGS];
  big.bits[NUMBER_LOW] = decimal.bits[NUMBER_LOW];
  big.bits[NUMBER_MID] = decimal.bits[NUMBER_MID];
  big.bits[NUMBER_HI] = decimal.bits[NUMBER_HI];
  return big;
}