#ifndef S21_DECIMAL_H
#define S21_DECIMAL_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define NUMBER_LOW 0
#define NUMBER_MID 1
#define NUMBER_HI 2
#define NUMBER_FLAGS 3
#define NUMBER_BIG_LOW 3
#define NUMBER_BIG_MID 4
#define NUMBER_BIG_HI 5
#define NUMBER_BIG_FLAGS 6

#define POSITION_SIGN 31
#define POSITION_PRECISION 16

/**
 * @brief Структура для представления десятичного числа.
 * Поля:
 * - bits[0] - bits[2]: инты мантиссы
 * - bits[3]: Дополнительная информация, такая как знак и масштаб.
 */
typedef struct {
  uint32_t bits[4]; /**< Массив битов для хранения десятичного числа. */
} s21_decimal;

/**
 * @brief Структура для представления увеличенного десятичного числа .
 * 7 битовых полей вместо 4
 * Поля:
 * - bits[0] - bits[6]: инты мантиссы
 * - bits[7]: знак и экспонента.
 */
typedef struct {
  unsigned int bits[7];
} s21_big;

// Основные функции
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

int s21_is_less(s21_decimal, s21_decimal);
int s21_is_less_or_equal(s21_decimal, s21_decimal);
int s21_is_greater(s21_decimal, s21_decimal);
int s21_is_greater_or_equal(s21_decimal, s21_decimal);
int s21_is_equal(s21_decimal, s21_decimal);
int s21_is_not_equal(s21_decimal, s21_decimal);
int s21_compare(s21_big, s21_big);

int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);

int s21_floor(s21_decimal value, s21_decimal *result);
int s21_round(s21_decimal value, s21_decimal *result);
int s21_truncate(s21_decimal value, s21_decimal *result);
int s21_negate(s21_decimal value, s21_decimal *result);

// Дополнительные функции
int s21_numbers_add(uint32_t number1, uint32_t number2, uint32_t *result);
s21_big s21_big_mantissa_add(s21_big big1, s21_big big2);
s21_big s21_big_mantissa_sub(s21_big big1, s21_big big2);
void s21_big_mul(s21_big value_1, s21_big value_2, s21_big *result);
int s21_big_div(s21_big value_1, s21_big value_2, s21_big *result);
int s21_big_mul10(s21_big *big);
int s21_big_div10(s21_big *big);
int s21_decimal_div10(s21_decimal *in, unsigned *rest);
int s21_decimal_is_zero(s21_decimal value);
int s21_big_is_zero(s21_big value);
void s21_decimal_to_zero(s21_decimal *decimal);
void s21_big_to_zero(s21_big *big);

int s21_big_is_mantissa_greater(s21_big biga, s21_big bigb);

int s21_bit_get(uint32_t number, int position);
void s21_bit_set(uint32_t *number, int position, int value);
void s21_bit_reverse(uint32_t *number, int position);
int s21_decimal_sign_get(s21_decimal);
void s21_decimal_sign_set(s21_decimal *decimal, int sign);
int s21_decimal_precision_get(s21_decimal);
void s21_decimal_precision_set(s21_decimal *decimal, int precision);
int s21_big_sign_get(s21_big);
void s21_big_sign_set(s21_big *big, int sign);
int s21_big_precision_get(s21_big);
void s21_big_precision_set(s21_big *, int);

void s21_big_print_binary(s21_big big);
void s21_big_print_denary(s21_big big);
void s21_big_print_hex(s21_big big);
void s21_big_print_hex_oneline(s21_big big);
void s21_decimal_print_binary(s21_decimal decimal);
void s21_decimal_print_denary(s21_decimal decimal);
void s21_decimal_print_hex(s21_decimal decimal);
void s21_decimal_print_hex_oneline(s21_decimal decimal);
void s21_number_print_binary(uint32_t number);
void s21_number_print_denary(uint32_t numer);
void s21_number_print_hex(uint32_t numer);

int s21_big_shift_left(s21_big *big);
int s21_big_shift_right(s21_big *big);
int s21_decimal_shift_left(s21_decimal *decimal);
int s21_decimal_shift_right(s21_decimal *decimal);
int s21_number_shift_left(uint32_t *number);
int s21_number_shift_right(uint32_t *number);

s21_big s21_decimal_to_big(s21_decimal);
int s21_big_to_decimal(s21_big big, s21_decimal *decimal);
int s21_decimal_is_ok(s21_decimal);
int s21_big_normalize(s21_big *, s21_big *);
float s21_rand_float(float a, float b);
void s21_decimal_remove_zeros(s21_decimal *value);

#endif