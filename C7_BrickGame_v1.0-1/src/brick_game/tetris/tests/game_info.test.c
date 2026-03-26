#include "tests.h"
START_TEST(SPEED) {
  int level = -10;
  int result = GetSpeedFromLevel(level);
  ck_assert_int_eq(result, SPEED_BASE);

  level = 0;
  result = GetSpeedFromLevel(level);
  ck_assert_int_eq(result, SPEED_BASE);

  level = 1;
  result = GetSpeedFromLevel(level);
  ck_assert_int_eq(result, SPEED_BASE);

  level = MAX_LEVEL;
  result = GetSpeedFromLevel(level);
  ck_assert_int_eq(result, SPEED_BASE - SPEED_STEP * (level - 1));

  level = MAX_LEVEL + 1;
  result = GetSpeedFromLevel(level);
  ck_assert_int_eq(result, SPEED_BASE - SPEED_STEP * (MAX_LEVEL - 1));
}

START_TEST(LEVEL) {
  int result;
  int input_score;
  int expected_level;

  input_score = LEVEL_SCORE - 1;
  expected_level = 1;

  result = GetLevelFromScore(input_score);
  ck_assert_int_eq(result, expected_level);

  input_score = LEVEL_SCORE;
  expected_level = 2;

  result = GetLevelFromScore(input_score);
  ck_assert_int_eq(result, expected_level);
}

END_TEST

START_TEST(UPDATE_HIGH_SCORE) {
  GameInfo_t game_info = {0};

  game_info.score = 1000;
  UpdateHighScore(&game_info);
  ck_assert_int_eq(game_info.high_score, 1000);

  game_info.score = 500;
  game_info.high_score = 1000;
  UpdateHighScore(&game_info);
  ck_assert_int_eq(game_info.high_score, 1000);
}
END_TEST

START_TEST(COUNT_SCORE_BY_LINES) {
  int result;
  int lines_count;

  lines_count = 0;
  result = CountScore(lines_count);
  ck_assert_int_eq(result, 0);

  lines_count = 1;
  result = CountScore(lines_count);
  ck_assert_int_eq(result, POINTS_1_LINE);

  lines_count = 2;
  result = CountScore(lines_count);
  ck_assert_int_eq(result, POINTS_2_LINES);

  lines_count = 3;
  result = CountScore(lines_count);
  ck_assert_int_eq(result, POINTS_3_LINES);

  lines_count = 4;
  result = CountScore(lines_count);
  ck_assert_int_eq(result, POINTS_4_LINES);
}

START_TEST(UPDATE_GAME_INFO) {
  GameInfo_t game_info = {0};
  AllocateArray(&(game_info.field), FIELD_HEIGHT, FIELD_WIDTH);

  for (int i = FIELD_HEIGHT - 2; i < FIELD_HEIGHT; i++) {
    for (int j = 0; j < FIELD_WIDTH; j++) {
      game_info.field[i][j] = FIELD_SIGN_TERRAIN;
    }
  }

  UpdateGameInfo(&game_info);

  for (int i = FIELD_HEIGHT - 2; i < FIELD_HEIGHT; i++) {
    for (int j = 0; j < FIELD_WIDTH; j++) {
      ck_assert_int_eq(game_info.field[i][j], 0);
    }
  }
  ck_assert_int_eq(game_info.score, POINTS_2_LINES);
  ck_assert_int_eq(game_info.level, 1);
  ck_assert_int_eq(game_info.speed, SPEED_BASE);
  ck_assert_int_eq(game_info.high_score, POINTS_2_LINES);

  FreeArray(game_info.field, FIELD_HEIGHT);
}

TCase* tcase_game_info(void) {
  TCase* tcase = tcase_create("GAME_INFO");
  tcase_add_test(tcase, SPEED);
  tcase_add_test(tcase, LEVEL);
  tcase_add_test(tcase, UPDATE_HIGH_SCORE);
  tcase_add_test(tcase, COUNT_SCORE_BY_LINES);
  tcase_add_test(tcase, UPDATE_GAME_INFO);
  return tcase;
}