
#include "tests.h"
START_TEST(HIGH_SCORE) {
  int score = 999;
  WriteHighScore(score);

  int high_score = ReadHighScore();
  ck_assert_int_eq(high_score, 999);
}

START_TEST(HIGH_SCORE_FAILING) {
  char filename[] = HIGH_SCORE_FILE;
  remove(filename);

  int high_score = ReadHighScore();
  ck_assert_int_eq(high_score, 0);
}

TCase* tcase_high_score(void) {
  TCase* tcase = tcase_create("HIGH_SCORE");
  tcase_add_test(tcase, HIGH_SCORE);
  tcase_add_test(tcase, HIGH_SCORE_FAILING);
  return tcase;
}