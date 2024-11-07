#include "test_s21_decimal.h"

START_TEST(s21_add1) {
  s21_decimal deca = {{0, 1, 1, 0}};
  s21_decimal decb = {{0, 1, 1, 0}};
  s21_decimal decres = {{0}};
  s21_add(deca, decb, &decres);
  s21_decimal dectest = {{0, 2, 2, 0}};
  for (int i = NUMBER_FLAGS; i >= NUMBER_LOW; i--) {
    ck_assert_int_eq(decres.bits[i], dectest.bits[i]);
  }
}
END_TEST

START_TEST(s21_add2) {
  s21_decimal deca = {{0, 1, 1, 0}};
  s21_decimal decb = {{0, 1, 1, 0x80000000}};
  s21_decimal decres = {{0}};
  s21_add(deca, decb, &decres);
  s21_decimal dectest = {{0, 0, 0, 0x80000000}};
  for (int i = NUMBER_FLAGS; i >= NUMBER_LOW; i--) {
    ck_assert_int_eq(decres.bits[i], dectest.bits[i]);
  }
}
END_TEST

START_TEST(s21_add3) {
  s21_decimal deca = {{2, 0, 1, 0}};
  s21_decimal decb = {{1, 0, 1, 0x80000000}};
  s21_decimal decres = {{0}};
  s21_add(deca, decb, &decres);
  s21_decimal dectest = {{1, 0, 0, 0}};
  for (int i = NUMBER_FLAGS; i >= NUMBER_LOW; i--) {
    ck_assert_int_eq(decres.bits[i], dectest.bits[i]);
  }
}
END_TEST

START_TEST(s21_add4) {
  s21_decimal deca = {{0xffffffff, 0xffffffff, 0xffffffff, 0}};
  s21_decimal decb = {{0xffffffff, 0xffffffff, 0xffffffff, 0}};
  s21_decimal decres = {{0}};
  int result = s21_add(deca, decb, &decres);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(s21_add5) {
  s21_decimal deca = {{0xffffffff, 0xffffffff, 0xffffffff, 0x80000000}};
  s21_decimal decb = {{0xffffffff, 0xffffffff, 0xffffffff, 0x80000000}};
  s21_decimal decres = {{0}};
  int result = s21_add(deca, decb, &decres);
  ck_assert_int_eq(result, 2);
}
END_TEST

START_TEST(s21_sub1) {
  s21_decimal deca = {{0, 1, 1, 0}};
  s21_decimal decb = {{0, 1, 1, 0}};
  s21_decimal decres = {{0}};
  int result = s21_sub(deca, decb, &decres);
  s21_decimal dectest = {{0}};
  ck_assert_int_eq(result, 0);
  for (int i = NUMBER_FLAGS; i >= NUMBER_LOW; i--) {
    ck_assert_int_eq(decres.bits[i], dectest.bits[i]);
  }
}
END_TEST

START_TEST(s21_sub2) {
  s21_decimal deca = {{0xffffffff, 0xffffffff, 0xffffffff, 0}};
  s21_decimal decb = {{0xffffffff, 0xffffffff, 0xffffffff, 0x80000000}};
  s21_decimal decres = {{0}};
  int result = s21_sub(deca, decb, &decres);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(s21_sub3) {
  s21_decimal deca = {{0xffffffff, 0xffffffff, 0xffffffff, 0x80000000}};
  s21_decimal decb = {{0xffffffff, 0xffffffff, 0xffffffff, 0}};
  s21_decimal decres = {{0}};
  int result = s21_sub(deca, decb, &decres);
  ck_assert_int_eq(result, 2);
}
END_TEST

START_TEST(s21_sub4) {
  s21_decimal deca = {{0xffffffff, 0, 0xffffffff, 0}};
  s21_decimal decb = {{0xffffffff, 0xffffffff, 0xffffffff, 0}};
  s21_decimal decres = {{0}};
  int result = s21_sub(deca, decb, &decres);
  s21_decimal dectest = {{0, 0xffffffff, 0, 0x80000000}};
  ck_assert_int_eq(result, 0);
  for (int i = NUMBER_FLAGS; i >= NUMBER_LOW; i--) {
    ck_assert_int_eq(dectest.bits[i], decres.bits[i]);
  }
}
END_TEST

START_TEST(s21_sub5) {
  s21_decimal deca = {{0xffffffff, 0, 0xffffffff, 0x80000000}};
  s21_decimal decb = {{0xffffffff, 0xffffffff, 0xffffffff, 0x80000000}};
  s21_decimal decres = {{0}};
  int result = s21_sub(deca, decb, &decres);
  s21_decimal dectest = {{0, 0xffffffff, 0, 0}};
  ck_assert_int_eq(result, 0);
  for (int i = NUMBER_FLAGS; i >= NUMBER_LOW; i--) {
    ck_assert_int_eq(dectest.bits[i], decres.bits[i]);
  }
}
END_TEST

//------------------------------------------------------------------------s21_mul

START_TEST(mul_0) {
  s21_decimal val1 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal test = {{4, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res;
  int chapa = s21_mul(val1, val2, &res);
  ck_assert_int_eq(0, chapa);
  for (int i = NUMBER_FLAGS; i >= NUMBER_LOW; i--) {
    ck_assert_int_eq(test.bits[i], res.bits[i]);
  }
}
END_TEST

START_TEST(mul_1) {
  s21_decimal val1 = {{2, 0, 0, 0}};
  s21_decimal val2 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res;
  s21_decimal test = {{4, 0, 0, ~(UINT_MAX / 2)}};
  int chapa = s21_mul(val1, val2, &res);
  ck_assert_int_eq(0, chapa);
  for (int i = NUMBER_FLAGS; i >= NUMBER_LOW; i--) {
    ck_assert_int_eq(test.bits[i], res.bits[i]);
  }
}
END_TEST

START_TEST(mul_2) {
  s21_decimal val1 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res;
  s21_decimal test = {{4, 0, 0, 0}};
  int chapa = s21_mul(val1, val2, &res);
  ck_assert_int_eq(0, chapa);
  for (int i = NUMBER_FLAGS; i >= NUMBER_LOW; i--) {
    ck_assert_int_eq(test.bits[i], res.bits[i]);
  }
}
END_TEST

START_TEST(mul_4) {
  s21_decimal val1 = {{8, 0, 0, 0}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res = {{0}};
  s21_decimal test = {{16, 0, 0, 0}};
  int chapa = s21_mul(val1, val2, &res);
  ck_assert_int_eq(0, chapa);
  for (int i = NUMBER_FLAGS; i >= NUMBER_LOW; i--) {
    ck_assert_int_eq(test.bits[i], res.bits[i]);
  }
}
END_TEST

START_TEST(mul_5) {
  s21_decimal val1 = {{2, 0, 0, 0}};
  s21_decimal val2 = {{8, 0, 0, 0}};
  s21_decimal res = {{0}};
  s21_decimal test = {{16, 0, 0, 0}};
  int chapa = s21_mul(val1, val2, &res);
  ck_assert_int_eq(0, chapa);
  for (int i = NUMBER_FLAGS; i >= NUMBER_LOW; i--) {
    ck_assert_int_eq(test.bits[i], res.bits[i]);
  }
}
END_TEST

START_TEST(mul_6) {
  s21_decimal val1 = {{8, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res = {{0}};
  s21_decimal test = {{16, 0, 0, ~(UINT_MAX / 2)}};
  int chapa = s21_mul(val1, val2, &res);
  ck_assert_int_eq(0, chapa);
  for (int i = NUMBER_FLAGS; i >= NUMBER_LOW; i--) {
    ck_assert_int_eq(test.bits[i], res.bits[i]);
  }
}
END_TEST

START_TEST(mul_7) {
  s21_decimal val1 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{8, 0, 0, 0}};
  s21_decimal res = {{0}};
  s21_decimal test = {{16, 0, 0, ~(UINT_MAX / 2)}};
  int chapa = s21_mul(val1, val2, &res);
  ck_assert_int_eq(0, chapa);
  for (int i = NUMBER_FLAGS; i >= NUMBER_LOW; i--) {
    ck_assert_int_eq(test.bits[i], res.bits[i]);
  }
}
END_TEST

START_TEST(mul_8) {
  s21_decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res = {{0}};
  int chapa = s21_mul(val1, val2, &res);
  ck_assert_int_eq(1, chapa);
}
END_TEST

START_TEST(mul_9) {
  s21_decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(2, s21_mul(val1, val2, &res));
}
END_TEST

START_TEST(mul_10) {
  s21_decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(1, s21_mul(val1, val2, &res));
}
END_TEST

START_TEST(mul_11) {
  s21_decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{0, 0, 0, 0}};
  s21_decimal res = {{0}};
  s21_decimal test = {{0, 0, 0, 0}};
  int chapa = s21_mul(val1, val2, &res);
  ck_assert_int_eq(0, chapa);
  for (int i = NUMBER_FLAGS; i >= NUMBER_LOW; i--) {
    ck_assert_int_eq(test.bits[i], res.bits[i]);
  }
}
END_TEST

START_TEST(mul_12) {
  s21_decimal value_1 = {{5, 0, 0, 0}};
  s21_decimal value_2 = {{7, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal check = {{35, 0, 0, 0}};
  int return_value = s21_mul(value_1, value_2, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, 0);
}
END_TEST
START_TEST(mul_13) {
  s21_decimal value_1 = {{0xFFFFFFFF, 0, 0, 0}};
  s21_decimal value_2 = {{0xFFFFFFFF, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal check = {{1, 0xFFFFFFFE, 0, 0}};
  int return_value = s21_mul(value_1, value_2, &result);

  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(mul_14) {
  s21_decimal value_1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal value_2 = {{2, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal check = {{0, 0, 0, 0}};
  int return_value = s21_mul(value_1, value_2, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, 1);
}
END_TEST

START_TEST(mul_15) {
  s21_decimal value_1 = {{123456u, 123u, 0, 0}};
  s21_decimal value_2 = {{654321u, 654u, 0, 0}};
  s21_decimal_sign_set(&value_2, 1);
  s21_decimal_precision_set(&value_1, 2);
  s21_decimal_precision_set(&value_2, 3);
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal check = {{0x148B6E80, 0x60187BAA, 0xC4644, 0x80030000}};
  int return_value = s21_mul(value_1, value_2, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 0);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(mul_16) {
  s21_decimal value_1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal value_2 = {{2, 0, 0, 0}};
  s21_decimal_sign_set(&value_2, 1);
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal check = {{0, 0, 0, 0}};
  int return_value = s21_mul(value_1, value_2, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, 2);
}
END_TEST

START_TEST(mul_17) {
  s21_decimal value_1 = {{17, 0, 0, 0}};
  s21_decimal_sign_set(&value_1, 1);
  s21_decimal value_2 = {{0, 0, 0, 0}};
  s21_decimal result = {0};
  s21_decimal check = {{0, 0, 0, 0}};
  int return_value = s21_mul(value_1, value_2, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(mul_19) {
  s21_decimal src1 = {{0}};
  s21_decimal src2 = {{0}};
  int a = -32768;
  int b = 32768;
  int res_our_dec = 0;
  s21_from_int_to_decimal(a, &src1);
  s21_from_int_to_decimal(b, &src2);
  int res_origin = -1073741824;
  s21_decimal res_od = {0};
  s21_mul(src1, src2, &res_od);
  s21_from_decimal_to_int(res_od, &res_our_dec);
  ck_assert_int_eq(res_our_dec, res_origin);
}
END_TEST

START_TEST(mul_test_1) {
  int num1 = -10;
  int num2 = -10;
  int prod_int = 100;
  s21_decimal a = {0};
  s21_decimal b = {0};
  s21_from_int_to_decimal(num1, &a);
  s21_from_int_to_decimal(num2, &b);
  s21_decimal res_dec = {0};
  int res_int = 0;
  s21_mul(a, b, &res_dec);
  s21_from_decimal_to_int(res_dec, &res_int);
  ck_assert_int_eq(res_int, prod_int);
}
END_TEST

START_TEST(mul_test_2) {
  int num1 = 10;
  int num2 = 20;
  int prod_int = 200;
  s21_decimal a = {0};
  s21_decimal b = {0};
  s21_from_int_to_decimal(num1, &a);
  s21_from_int_to_decimal(num2, &b);
  s21_decimal res_dec = {0};
  int res_int = 0;
  s21_mul(a, b, &res_dec);
  s21_from_decimal_to_int(res_dec, &res_int);

  ck_assert_int_eq(res_int, prod_int);
}
END_TEST

START_TEST(mul_test_3) {
  int num1 = -10;
  int num2 = 20;
  int prod_int = -200;
  s21_decimal a = {0};
  s21_decimal b = {0};
  s21_from_int_to_decimal(num1, &a);
  s21_from_int_to_decimal(num2, &b);
  s21_decimal res_dec = {0};
  int res_int = 0;
  s21_mul(a, b, &res_dec);
  s21_from_decimal_to_int(res_dec, &res_int);
  ck_assert_int_eq(res_int, prod_int);
}
END_TEST

START_TEST(mul_test_4) {
  int num1 = 9403;
  int num2 = 202;
  int res_origin = 1899406;
  s21_decimal a = {0};
  s21_decimal b = {0};
  s21_from_int_to_decimal(num1, &a);
  s21_from_int_to_decimal(num2, &b);
  s21_decimal res_dec = {0};
  int res_int = 0;
  s21_mul(a, b, &res_dec);
  s21_from_decimal_to_int(res_dec, &res_int);
  ck_assert_int_eq(res_int, res_origin);
}
END_TEST

START_TEST(mul_test_5) {
  int num1 = -32768;
  int num2 = 2;
  int res_origin = -65536;
  s21_decimal a = {0};
  s21_decimal b = {0};
  s21_from_int_to_decimal(num1, &a);
  s21_from_int_to_decimal(num2, &b);
  s21_decimal res_dec = {0};
  int res_int = 0;
  s21_mul(a, b, &res_dec);
  s21_from_decimal_to_int(res_dec, &res_int);
  ck_assert_int_eq(res_int, res_origin);
}
END_TEST

START_TEST(mul_test_6) {
  int num1 = -32768;
  int num2 = 32768;
  int res_origin = -1073741824;
  s21_decimal a = {0};
  s21_decimal b = {0};
  s21_from_int_to_decimal(num1, &a);
  s21_from_int_to_decimal(num2, &b);
  s21_decimal res_dec = {0};
  int res_int = 0;
  s21_mul(a, b, &res_dec);
  s21_from_decimal_to_int(res_dec, &res_int);
  ck_assert_int_eq(res_int, res_origin);
}
END_TEST

START_TEST(mul_test_7) {
  s21_decimal dec1 = {{0xffffffff, 0xffffffff, 0xffffffff, 0}};
  s21_decimal dec2 = {{0xffffffff, 0xffffffff, 0xffffffff, 0}};
  s21_decimal res = {{0}};
  int chipi = s21_mul(dec1, dec2, &res);
  ck_assert_int_eq(chipi, 1);
}
END_TEST

START_TEST(mul_test_8) {
  s21_decimal dec1 = {{100, 0, 0, 0}};
  s21_decimal_precision_set(&dec1, 1);
  s21_decimal dec2 = {{2, 0, 0, 0}};
  s21_decimal_precision_set(&dec2, 3);
  s21_decimal res;
  s21_decimal test = {{2, 0, 0, 0}};
  s21_decimal_precision_set(&test, 2);
  int chipi = s21_mul(dec1, dec2, &res);
  ck_assert_int_eq(chipi, 0);
  for (int i = 0; i <= NUMBER_FLAGS; i++) {
    ck_assert_int_eq(test.bits[i], res.bits[i]);
  }
}
END_TEST

//------------------------------------------------------------------------s21_div

START_TEST(div_0) {
  s21_decimal val1 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(0, s21_div(val1, val2, &res));
}
END_TEST

START_TEST(div_1) {
  s21_decimal val1 = {{2, 0, 0, 0}};
  s21_decimal val2 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_div(val1, val2, &res));
}
END_TEST

START_TEST(div_2) {
  s21_decimal val1 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(0, s21_div(val1, val2, &res));
}
END_TEST

START_TEST(div_3) {
  s21_decimal val1 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{0, 0, 0, 0}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(3, s21_div(val1, val2, &res));
}
END_TEST

START_TEST(div_4) {
  s21_decimal val1 = {{2, 0, 0, 0}};
  s21_decimal val2 = {{0, 0, 0, 0}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(3, s21_div(val1, val2, &res));
}
END_TEST

START_TEST(div_5) {
  s21_decimal value_1 = {{35, 0, 0, 0}};
  s21_decimal value_2 = {{5, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal check = {{70, 0, 0, 0}};
  s21_decimal_precision_set(&value_1, 1);
  s21_decimal_precision_set(&value_2, 2);
  int return_value = s21_div(value_1, value_2, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(div_6) {
  s21_decimal value_1 = {{0x88888888, 0x88888888, 0x88888888, 0}};
  s21_decimal value_2 = {{0x2, 0, 0, 0}};
  s21_decimal_sign_set(&value_2, 1);
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal check = {{0x44444444, 0x44444444, 0x44444444, 0}};
  s21_decimal_sign_set(&check, 1);
  s21_decimal_precision_set(&check, 1);
  int return_value = s21_div(value_1, value_2, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(div_7) {
  s21_decimal value_1 = {{10, 0, 0, 0}};
  s21_decimal_sign_set(&value_1, 1);
  s21_decimal value_2 = {{8, 0, 0, 0}};
  s21_decimal_sign_set(&value_2, 1);
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal check = {{125, 0, 0, 0}};
  s21_decimal_precision_set(&check, 2);
  int return_value = s21_div(value_1, value_2, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(div_8) {
  s21_decimal value_1 = {{15, 0, 0, 0}};
  s21_decimal_sign_set(&value_1, 1);
  s21_decimal value_2 = {{0, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal check = {{0, 0, 0, 0}};
  int return_value = s21_div(value_1, value_2, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, 3);
}
END_TEST

START_TEST(div_9) {
  s21_decimal value_1 = {{10, 0, 0, 0}};
  s21_decimal value_2 = {{1, 0, 0, 0}};
  s21_decimal_precision_set(&value_2, 2);
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal check = {{1000u, 0, 0, 0}};
  int return_value = s21_div(value_1, value_2, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

Suite *suite_s21_arithmetics(void) {
  Suite *s = suite_create("suite_s21_arithmetics");
  TCase *tc = tcase_create("s21_arithmetics");

  tcase_add_test(tc, s21_add1);
  tcase_add_test(tc, s21_add2);
  tcase_add_test(tc, s21_add3);
  tcase_add_test(tc, s21_add4);
  tcase_add_test(tc, s21_add5);

  tcase_add_test(tc, s21_sub1);
  tcase_add_test(tc, s21_sub2);
  tcase_add_test(tc, s21_sub3);
  tcase_add_test(tc, s21_sub4);
  tcase_add_test(tc, s21_sub5);

  tcase_add_test(tc, mul_0);
  tcase_add_test(tc, mul_1);
  tcase_add_test(tc, mul_2);
  tcase_add_test(tc, mul_4);
  tcase_add_test(tc, mul_5);
  tcase_add_test(tc, mul_6);
  tcase_add_test(tc, mul_7);
  tcase_add_test(tc, mul_8);
  tcase_add_test(tc, mul_9);
  tcase_add_test(tc, mul_10);
  tcase_add_test(tc, mul_11);
  tcase_add_test(tc, mul_12);
  tcase_add_test(tc, mul_13);
  tcase_add_test(tc, mul_14);
  tcase_add_test(tc, mul_15);
  tcase_add_test(tc, mul_16);
  tcase_add_test(tc, mul_17);
  tcase_add_test(tc, mul_19);
  tcase_add_test(tc, mul_test_1);
  tcase_add_test(tc, mul_test_2);
  tcase_add_test(tc, mul_test_3);
  tcase_add_test(tc, mul_test_4);
  tcase_add_test(tc, mul_test_5);
  tcase_add_test(tc, mul_test_6);
  tcase_add_test(tc, mul_test_7);
  tcase_add_test(tc, mul_test_8);

  tcase_add_test(tc, div_0);
  tcase_add_test(tc, div_1);
  tcase_add_test(tc, div_2);
  tcase_add_test(tc, div_3);
  tcase_add_test(tc, div_4);
  tcase_add_test(tc, div_5);
  tcase_add_test(tc, div_6);
  tcase_add_test(tc, div_7);
  tcase_add_test(tc, div_8);
  tcase_add_test(tc, div_9);

  suite_add_tcase(s, tc);
  return s;
}