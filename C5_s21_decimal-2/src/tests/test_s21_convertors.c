#include "test_s21_decimal.h"

// s21_from_int_to_decimal

START_TEST(int_1) {
  s21_decimal dec1 = {{0, 0, 0, 0}};
  s21_decimal dec2 = {{1, 0, 0, 0}};
  int src = 1;
  s21_from_int_to_decimal(src, &dec1);
  ck_assert_int_eq(s21_is_equal(dec1, dec2), 1);
}
END_TEST

START_TEST(int_MAX) {
  s21_decimal dec1 = {{0, 0, 0, 0}};
  s21_decimal dec2 = {{2147483647, 0, 0, 0}};
  int src = 2147483647;
  s21_from_int_to_decimal(src, &dec1);
  ck_assert_int_eq(s21_is_equal(dec1, dec2), 1);
}
END_TEST

START_TEST(dec_NULL) {
  s21_decimal *dec1 = NULL;
  int src = 5;
  ck_assert_int_eq(s21_from_int_to_decimal(src, dec1), 1);
}
END_TEST

START_TEST(not_empt) {
  s21_decimal dec1 = {{0, 5, 0, 0}};
  int src = 5;
  ck_assert_int_eq(s21_from_int_to_decimal(src, &dec1), 0);
}
END_TEST

START_TEST(sign_int_1) {
  s21_decimal dec1 = {{0, 0, 0, 0}};
  s21_decimal dec2 = {{1, 0, 0, 0x80000000}};
  int src = -1;
  s21_from_int_to_decimal(src, &dec1);
  ck_assert_int_eq(s21_is_equal(dec1, dec2), 1);
}
END_TEST

// s21_from_decimal_to_int

START_TEST(int_123) {
  s21_decimal dec = {{123, 0, 0, 0}};
  int src = 0;
  s21_from_decimal_to_int(dec, &src);
  ck_assert_int_eq(src, 123);
}
END_TEST

START_TEST(int_sign_123) {
  s21_decimal dec = {{123, 0, 0, 0x80000000}};
  int src = 0;
  s21_from_decimal_to_int(dec, &src);
  ck_assert_int_eq(src, -123);
}
END_TEST

START_TEST(int_max1) {
  s21_decimal dec = {{2147483647, 1, 0, 0x00000000}};
  int src = 0;
  ck_assert_int_eq(s21_from_decimal_to_int(dec, &src), 1);
}
END_TEST

START_TEST(fail_ptr) {
  s21_decimal dec = {{2147483647, 1, 0, 0x00000000}};
  int *src = NULL;
  ck_assert_int_eq(s21_from_decimal_to_int(dec, src), 1);
}
END_TEST

START_TEST(big_scale) {
  s21_decimal dec = {{2147483647, 1, 0, 0x00ff0000}};
  int src = 0;
  ck_assert_int_eq(s21_from_decimal_to_int(dec, &src), 1);
}
END_TEST

START_TEST(norm_scale) {
  s21_decimal dec = {{2147483647, 0, 0, 0x00050000}};
  int src = 0;
  s21_from_decimal_to_int(dec, &src);
  ck_assert_int_eq(src, 21474);
}
END_TEST

START_TEST(dec_max) {
  s21_decimal dec = {{0xffffffff, 0xffffffff, 0xffffffff, 0}};
  s21_decimal_precision_set(&dec, 28);
  int src = 0;
  s21_from_decimal_to_int(dec, &src);
  ck_assert_int_eq(src, 7);
}
END_TEST

START_TEST(dec_over) {
  s21_decimal dec = {{0xffffffff, 0xffffffff, 0xffffffff, 0}};
  s21_decimal_precision_set(&dec, 19);
  int src = 0;
  int result = s21_from_decimal_to_int(dec, &src);
  ck_assert_int_eq(result, 1);
}
END_TEST

//------------------------------------------------------------------------s21_from_float_to_decimal

START_TEST(float_to_decimal_1) {
  float a = 1234567.0;
  float b = 0.0;
  int error = 0;
  int func_error = 0;
  s21_decimal dec = {0};
  func_error = s21_from_float_to_decimal(a, &dec);
  s21_from_decimal_to_float(dec, &b);
  ck_assert_int_eq(error, func_error);
  ck_assert_float_eq(a, b);
}
END_TEST

START_TEST(float_to_decimal_2) {
  float a = 123456.8;
  float b = 0.0;
  int error = 0;
  int func_error = 0;
  s21_decimal dec = {0};
  func_error = s21_from_float_to_decimal(a, &dec);
  s21_from_decimal_to_float(dec, &b);
  ck_assert_int_eq(error, func_error);
  ck_assert_float_eq(a, b);
}
END_TEST

START_TEST(float_to_decimal_3) {
  float a = 12345.60;
  float b = 0.0;
  int error = 0;
  int func_error = 0;
  s21_decimal dec = {0};
  func_error = s21_from_float_to_decimal(a, &dec);
  s21_from_decimal_to_float(dec, &b);
  ck_assert_int_eq(error, func_error);
  ck_assert_float_eq(a, b);
}
END_TEST

START_TEST(float_to_decimal_4) {
  float a = 1.000000;
  float b = 0.0;
  int error = 0;
  int func_error = 0;
  s21_decimal dec = {0};
  func_error = s21_from_float_to_decimal(a, &dec);
  s21_from_decimal_to_float(dec, &b);
  ck_assert_int_eq(error, func_error);
  ck_assert_float_eq(a, b);
}
END_TEST

START_TEST(float_to_decimal_5) {
  float a = 1.00001;
  float b = 0.0;
  int error = 0;
  int func_error = 0;
  s21_decimal dec = {0};
  func_error = s21_from_float_to_decimal(a, &dec);
  s21_from_decimal_to_float(dec, &b);

  ck_assert_int_eq(error, func_error);
  ck_assert_float_eq(a, b);
}
END_TEST

START_TEST(float_to_decimal_6) {
  float a = 1.456780;
  float b = 0.0;
  int error = 0;
  int func_error = 0;
  s21_decimal dec = {0};
  func_error = s21_from_float_to_decimal(a, &dec);
  s21_from_decimal_to_float(dec, &b);
  ck_assert_int_eq(error, func_error);
  ck_assert_float_eq(a, b);
}
END_TEST

START_TEST(float_to_decimal_10) {
  float a = 0.123456;
  float b = 0.0;
  int error = 0;
  int func_error = 0;
  s21_decimal dec = {0};
  func_error = s21_from_float_to_decimal(a, &dec);
  s21_from_decimal_to_float(dec, &b);
  ck_assert_int_eq(error, func_error);
  ck_assert_float_eq(a, b);
}
END_TEST

START_TEST(float_to_decimal_13) {
  float a = 1.7891289;
  float b = 0.0;
  int error = 0;
  int func_error = 0;
  s21_decimal dec = {0};
  func_error = s21_from_float_to_decimal(a, &dec);
  s21_from_decimal_to_float(dec, &b);
  ck_assert_int_eq(error, func_error);
  ck_assert_float_eq_tol(a, b, 1e-6);
}
END_TEST

START_TEST(float_to_decimal_16) {
  float a = 123.456;
  float b = 0.0;
  int error = 0;
  int func_error = 0;
  s21_decimal dec = {0};
  func_error = s21_from_float_to_decimal(a, &dec);
  s21_from_decimal_to_float(dec, &b);
  ck_assert_int_eq(error, func_error);
  ck_assert_float_eq(a, b);
}
END_TEST

START_TEST(float_to_decimal_19) {
  float a = 123456.1;
  float b = 0;
  int error = 0;
  int func_error = 0;
  s21_decimal dec = {0};
  func_error = s21_from_float_to_decimal(a, &dec);
  s21_from_decimal_to_float(dec, &b);
  ck_assert_int_eq(error, func_error);
  ck_assert_float_eq(a, b);
}
END_TEST

START_TEST(float_to_decimal_29) {
  float a = 0.9;
  float b = 0.0;
  int error = 0;
  int func_error = 0;
  s21_decimal dec = {{0}};
  func_error = s21_from_float_to_decimal(a, &dec);
  s21_from_decimal_to_float(dec, &b);
  ck_assert_int_eq(error, func_error);
  ck_assert_float_eq(a, b);
}
END_TEST

START_TEST(float_to_decimal_30) {
  float a = 1.200000e-27;
  float b = 0.0;
  int error = 0;
  int func_error = 0;
  s21_decimal dec = {{0}};
  func_error = s21_from_float_to_decimal(a, &dec);
  s21_from_decimal_to_float(dec, &b);
  ck_assert_int_eq(error, func_error);
  ck_assert_float_eq(a, b);
}
END_TEST

START_TEST(float_to_decimal_31) {
  float a = 1.2e-26;
  float b = 0.0;
  int error = 0;
  int func_error = 0;
  s21_decimal dec = {{0}};
  func_error = s21_from_float_to_decimal(a, &dec);
  s21_from_decimal_to_float(dec, &b);
  ck_assert_int_eq(error, func_error);
  ck_assert_float_eq(a, b);
}
END_TEST

START_TEST(float_to_decimal_32) {
  float a = 1.2e-25;
  float b = 0.0;
  int error = 0;
  int func_error = 0;
  s21_decimal dec = {{0}};
  func_error = s21_from_float_to_decimal(a, &dec);
  s21_from_decimal_to_float(dec, &b);
  ck_assert_int_eq(error, func_error);
  ck_assert_float_eq(a, b);
}
END_TEST

START_TEST(float_to_decimal_33) {
  float a = 1.2e-24;
  float b = 0.0;
  int error = 0;
  int func_error = 0;
  s21_decimal dec = {{0}};
  func_error = s21_from_float_to_decimal(a, &dec);
  s21_from_decimal_to_float(dec, &b);
  ck_assert_int_eq(error, func_error);
  ck_assert_float_eq(a, b);
}
END_TEST

START_TEST(float_to_decimal_34) {
  float a = 1.2e-23;
  float b = 0.0;
  int error = 0;
  int func_error = 0;
  s21_decimal dec = {{0}};
  func_error = s21_from_float_to_decimal(a, &dec);
  s21_from_decimal_to_float(dec, &b);
  ck_assert_int_eq(error, func_error);
  ck_assert_float_eq(a, b);
}
END_TEST

START_TEST(float_to_decimal_35) {
  float a = 1.2e-22;
  float b = 0.0;
  int error = 0;
  int func_error = 0;
  s21_decimal dec = {{0}};
  func_error = s21_from_float_to_decimal(a, &dec);
  s21_from_decimal_to_float(dec, &b);
  ck_assert_int_eq(error, func_error);
  ck_assert_float_eq(a, b);
}
END_TEST

START_TEST(float_to_decimal_36) {
  float a = 1.2e-21;
  float b = 0.0;
  int error = 0;
  int func_error = 0;
  s21_decimal dec = {{0}};
  func_error = s21_from_float_to_decimal(a, &dec);
  s21_from_decimal_to_float(dec, &b);
  ck_assert_int_eq(error, func_error);
  ck_assert_float_eq(a, b);
}
END_TEST

START_TEST(float_to_decimal_52) {
  float a = 0.0;
  float b = 0.0;
  int error = 0;
  int func_error = 0;
  s21_decimal dec = {{0}};
  func_error = s21_from_float_to_decimal(a, &dec);
  s21_from_decimal_to_float(dec, &b);
  ck_assert_int_eq(error, func_error);
  ck_assert_float_eq(a, b);
}
END_TEST

START_TEST(float_to_decimal_53) {
  float a = powf(2.0f, 96.0f) - 1.0;
  float b = 0.0;
  int error = 0;
  int func_error = 0;
  s21_decimal dec = {{0}};
  func_error = s21_from_float_to_decimal(a, &dec);
  s21_from_decimal_to_float(dec, &b);
  ck_assert_int_eq(error, func_error);
}
END_TEST

START_TEST(float_to_decimal_54) {
  s21_decimal val = {0};
  float fl1 = 3.000000;
  float fl2 = 127.1234;
  float fl1_res = 0;
  float fl2_res = 0;
  s21_from_float_to_decimal(fl1, &val);
  s21_from_decimal_to_float(val, &fl1_res);
  s21_decimal_to_zero(&val);
  ck_assert_double_eq(fl1, fl1_res);
  s21_from_float_to_decimal(fl2, &val);
  s21_from_decimal_to_float(val, &fl2_res);

  ck_assert_double_eq(fl2, fl2_res);
}
END_TEST

START_TEST(float_to_decimal_55) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  float fl1 = -128.023;
  float fl2 = 12345.4;
  float fl1_res = 0;
  float fl2_res = 0;

  s21_from_float_to_decimal(fl1, &val1);
  s21_from_decimal_to_float(val1, &fl1_res);

  ck_assert_double_eq_tol(fl1, fl1_res, 1e-6);

  s21_from_float_to_decimal(fl2, &val2);
  s21_from_decimal_to_float(val2, &fl2_res);

  ck_assert_double_eq_tol(fl2, fl2_res, 1e-6);
}
END_TEST

START_TEST(float_to_decimal_56) {
  s21_decimal val = {0};
  float num = -2147483;
  s21_from_float_to_decimal(num, &val);

  ck_assert_int_eq(val.bits[0], 2147483);
  ck_assert_int_eq(val.bits[1], 0);
  ck_assert_int_eq(val.bits[2], 0);
  ck_assert_int_eq(val.bits[3], 2147483648);
}
END_TEST

START_TEST(float_to_decimal_58) {
  s21_decimal val = {0};
  s21_from_float_to_decimal(1.02E+09, &val);

  ck_assert_int_eq(val.bits[0], 1020000000);
  ck_assert_int_eq(val.bits[1], 0);
  ck_assert_int_eq(val.bits[2], 0);
  ck_assert_int_eq(val.bits[3], 0);
}
END_TEST

START_TEST(float_to_decimal_60) {
  s21_decimal val = {0};
  float a = 1.0 / 0.0;
  s21_from_float_to_decimal(a, &val);
  ck_assert_int_eq(val.bits[0], 0);
  ck_assert_int_eq(val.bits[1], 0);
  ck_assert_int_eq(val.bits[2], 0);
  ck_assert_int_eq(val.bits[3], 0);
}
END_TEST

START_TEST(float_to_decimal_61) {
  s21_decimal val = {0};
  float a = -1.0 / 0.0;
  s21_from_float_to_decimal(a, &val);
  s21_from_decimal_to_float(val, &a);

  ck_assert_int_eq(val.bits[0], 0);
  ck_assert_int_eq(val.bits[1], 0);
  ck_assert_int_eq(val.bits[2], 0);
  ck_assert_int_eq(val.bits[3], 0);
}
END_TEST

START_TEST(float_to_decimal_62) {
  s21_decimal val = {0};
  float a = 1e-30;
  s21_from_float_to_decimal(a, &val);
  ck_assert_int_eq(val.bits[0], 0);
  ck_assert_int_eq(val.bits[1], 0);
  ck_assert_int_eq(val.bits[2], 0);
  ck_assert_int_eq(val.bits[3], 0);
}
END_TEST

START_TEST(float_to_decimal_63) {
  s21_decimal dec = {0};
  float tmp = 0;
  float tmp1 = 0.03;
  s21_from_float_to_decimal(tmp1, &dec);
  s21_from_decimal_to_float(dec, &tmp);
  ck_assert_float_eq_tol(tmp, tmp1, 1e-06);
}
END_TEST

START_TEST(float_to_decimal_64) {
  s21_decimal dec = {0};
  s21_from_float_to_decimal(-128.023, &dec);
  float tmp = 0;
  s21_from_decimal_to_float(dec, &tmp);
  ck_assert_float_eq_tol(tmp, -128.023, 1e-06);
}
END_TEST

START_TEST(float_to_decimal_65) {
  s21_decimal dec = {0};
  s21_from_float_to_decimal(-2.147483E+09, &dec);
  float tmp = 0;
  s21_from_decimal_to_float(dec, &tmp);
  ck_assert_float_eq_tol(tmp, -2.147483E+09, 1e-06);
}
END_TEST

START_TEST(float_to_decimal_66) {
  s21_decimal dec = {0};
  s21_from_float_to_decimal(22.14836E+03, &dec);
  float tmp = 0;
  s21_from_decimal_to_float(dec, &tmp);

  ck_assert_float_eq_tol(tmp, 22148.36, 1e-06);
}
END_TEST

START_TEST(float_to_decimal_67) {
  s21_decimal dec = {0};
  s21_from_float_to_decimal(1.02E+08, &dec);
  float tmp = 0;
  s21_from_decimal_to_float(dec, &tmp);
  ck_assert_float_eq_tol(tmp, 1.02E+08, 1e-06);
}
END_TEST

START_TEST(float_to_decimal_68) {
  s21_decimal dec = {0};
  s21_from_float_to_decimal(-333.2222, &dec);
  float tmp = 0;
  s21_from_decimal_to_float(dec, &tmp);

  ck_assert_float_eq_tol(tmp, -333.2222, 1e-06);
}
END_TEST

START_TEST(float_to_decimal_69) {
  s21_decimal dec = {0};
  float a = 1.0 / 0.0;
  int ret = s21_from_float_to_decimal(a, &dec);
  ck_assert_int_eq(ret, 1);
}
END_TEST

START_TEST(float_to_decimal_70) {
  s21_decimal dec = {0};
  float a = -1.0 / 0.0;
  s21_from_float_to_decimal(a, &dec);
  ck_assert_int_eq(dec.bits[0], 0);
  ck_assert_int_eq(dec.bits[1], 0);
  ck_assert_int_eq(dec.bits[2], 0);
  ck_assert_int_eq(dec.bits[3], 0);
}
END_TEST

START_TEST(float_to_decimal_73) {
  float f = 1.0 / 0.0;
  s21_decimal result = {0};
  s21_decimal check = {{0, 0, 0, 0}};
  int return_value = s21_from_float_to_decimal(f, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, 1);
}
END_TEST

//------------------------------------------------------------------------s21_from_decimal_to_float

START_TEST(from_decimal_to_float_1) {
  s21_decimal val = {{123456789, 0, 0, 0}};
  s21_decimal_sign_set(&val, 1);
  s21_decimal_precision_set(&val, 5);
  float res = -1234.56789;
  float tmp = 0.;
  float *dst = &tmp;
  s21_from_decimal_to_float(val, dst);
  ck_assert_float_eq(*dst, res);
}
END_TEST

START_TEST(from_decimal_to_float_2) {
  s21_decimal var = {{0, 0, 0, 0}};
  float value = 0;
  s21_from_float_to_decimal(5.0, &var);
  s21_from_decimal_to_float(var, &value);
  ck_assert_float_eq_tol(5.0, value, 10e-5);
}
END_TEST

START_TEST(from_decimal_to_float_3) {
  float n = s21_rand_float(-8388608, 8388608);
  s21_decimal var = {{0, 0, 0, 0}};
  float value = 0;
  s21_from_float_to_decimal(n, &var);
  s21_from_decimal_to_float(var, &value);
  ck_assert_float_eq_tol(n, value, 10);
}
END_TEST

START_TEST(from_decimal_to_float_4) {
  float n = s21_rand_float(-1e-6 / 3, 1e-6 / 3);
  s21_decimal var = {{0, 0, 0, 0}};
  float value = 0;
  s21_from_float_to_decimal(n, &var);
  s21_from_decimal_to_float(var, &value);
  ck_assert_float_eq_tol(n, value, 10);
}
END_TEST

START_TEST(s21_from_decimal_to_float_1) {
  s21_decimal var = {0};
  float value = 0;
  s21_from_float_to_decimal(5.0, &var);
  s21_from_decimal_to_float(var, &value);
  ck_assert_float_eq_tol(5.0, value, 10e-5);
}
END_TEST

START_TEST(s21_from_decimal_to_float_2) {
  float n = s21_rand_float(-8388608, 8388608);
  s21_decimal var = {0};
  float value = 0;
  s21_from_float_to_decimal(n, &var);
  s21_from_decimal_to_float(var, &value);
  ck_assert_float_eq_tol(n, value, 10);
}
END_TEST

START_TEST(s21_from_decimal_to_float_3) {
  float n = s21_rand_float(-1e-6 / 3, 1e-6 / 3);
  s21_decimal var = {0};
  float value = 0;
  s21_from_float_to_decimal(n, &var);
  s21_from_decimal_to_float(var, &value);
  ck_assert_float_eq_tol(n, value, 10);
}
END_TEST

START_TEST(s21_from_decimal_to_float_4) {
  s21_decimal value = {{1812, 0, 0, 0}};
  s21_decimal_sign_set(&value, 1);
  float result = 0;
  float check = -1812;
  int return_value = s21_from_decimal_to_float(value, &result);
  ck_assert_float_eq(result, check);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(s21_from_decimal_to_float_5) {
  s21_decimal value = {{18122, 0, 0, 0}};
  s21_decimal_precision_set(&value, 3);
  s21_decimal_sign_set(&value, 1);
  float result = 0;
  float check = -18.122;
  int return_value = s21_from_decimal_to_float(value, &result);
  ck_assert_float_eq(result, check);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(s21_from_decimal_to_float_6) {
  s21_decimal value = {{0xFFFFFF, 0, 0, 0}};
  float result = 0;
  float check = 16777215;
  int return_value = s21_from_decimal_to_float(value, &result);
  ck_assert_float_eq(result, check);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

Suite *suite_s21_convertors(void) {
  Suite *s = suite_create("suite_s21_convertors");
  TCase *tc = tcase_create("s21_compare");

  tcase_add_test(tc, int_1);
  tcase_add_test(tc, int_MAX);
  tcase_add_test(tc, dec_NULL);
  tcase_add_test(tc, not_empt);
  tcase_add_test(tc, sign_int_1);
  tcase_add_test(tc, int_123);
  tcase_add_test(tc, int_sign_123);
  tcase_add_test(tc, int_max1);
  tcase_add_test(tc, fail_ptr);
  tcase_add_test(tc, big_scale);
  tcase_add_test(tc, norm_scale);
  tcase_add_test(tc, dec_max);
  tcase_add_test(tc, dec_over);

  tcase_add_test(tc, float_to_decimal_1);
  tcase_add_test(tc, float_to_decimal_2);
  tcase_add_test(tc, float_to_decimal_3);
  tcase_add_test(tc, float_to_decimal_4);
  tcase_add_test(tc, float_to_decimal_5);
  tcase_add_test(tc, float_to_decimal_6);
  tcase_add_test(tc, float_to_decimal_10);
  tcase_add_test(tc, float_to_decimal_13);
  tcase_add_test(tc, float_to_decimal_16);
  tcase_add_test(tc, float_to_decimal_19);
  tcase_add_test(tc, float_to_decimal_29);
  tcase_add_test(tc, float_to_decimal_30);
  tcase_add_test(tc, float_to_decimal_31);
  tcase_add_test(tc, float_to_decimal_32);
  tcase_add_test(tc, float_to_decimal_33);
  tcase_add_test(tc, float_to_decimal_34);
  tcase_add_test(tc, float_to_decimal_35);
  tcase_add_test(tc, float_to_decimal_36);
  tcase_add_test(tc, float_to_decimal_52);
  tcase_add_test(tc, float_to_decimal_53);
  tcase_add_test(tc, float_to_decimal_54);
  tcase_add_test(tc, float_to_decimal_55);
  tcase_add_test(tc, float_to_decimal_56);
  tcase_add_test(tc, float_to_decimal_58);
  tcase_add_test(tc, float_to_decimal_60);
  tcase_add_test(tc, float_to_decimal_61);
  tcase_add_test(tc, float_to_decimal_62);
  tcase_add_test(tc, float_to_decimal_63);
  tcase_add_test(tc, float_to_decimal_64);
  tcase_add_test(tc, float_to_decimal_65);
  tcase_add_test(tc, float_to_decimal_66);
  tcase_add_test(tc, float_to_decimal_67);
  tcase_add_test(tc, float_to_decimal_68);
  tcase_add_test(tc, float_to_decimal_69);
  tcase_add_test(tc, float_to_decimal_70);
  tcase_add_test(tc, float_to_decimal_73);

  tcase_add_test(tc, from_decimal_to_float_1);
  tcase_add_test(tc, from_decimal_to_float_2);
  tcase_add_loop_test(tc, from_decimal_to_float_3, 0, 100);
  tcase_add_loop_test(tc, from_decimal_to_float_4, 0, 100);
  tcase_add_test(tc, s21_from_decimal_to_float_1);
  tcase_add_loop_test(tc, s21_from_decimal_to_float_2, 0, 100);
  tcase_add_loop_test(tc, s21_from_decimal_to_float_3, 0, 100);
  tcase_add_test(tc, s21_from_decimal_to_float_4);
  tcase_add_test(tc, s21_from_decimal_to_float_5);
  tcase_add_test(tc, s21_from_decimal_to_float_6);

  suite_add_tcase(s, tc);
  return s;
}