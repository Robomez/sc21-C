#ifndef TESTS_S21_DECIMAL_H
#define TESTS_S21_DECIMAL_H

#include <check.h>

#include "../s21_decimal.h"

Suite *suite_getset(void);
Suite *suite_compare(void);
Suite *suite_print(void);
Suite *suite_shift(void);
Suite *suite_helpers(void);
Suite *suite_arith_help(void);

Suite *suite_s21_arithmetics(void);
Suite *suite_s21_compare(void);
Suite *suite_s21_others(void);
Suite *suite_s21_convertors(void);

#endif