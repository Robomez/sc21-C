#include "tests.h"

START_TEST(TIMER) {
  unsigned long long start = GetTime();
  unsigned long long end = GetTime();
  ck_assert_int_ge(end - start, 0);
}
END_TEST

TCase* tcase_timer(void) {
  TCase* tcase = tcase_create("TIMER");
  tcase_add_test(tcase, TIMER);
  return tcase;
}