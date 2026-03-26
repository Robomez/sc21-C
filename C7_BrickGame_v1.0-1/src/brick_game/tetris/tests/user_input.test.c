#include "tests.h"

START_TEST(USER_INPUT_START) {
  int high_score_init = 55555;
  FILE* fp = fopen(HIGH_SCORE_FILE, "w+");
  fprintf(fp, "%d", high_score_init);
  fclose(fp);

  userInput(Start, false);
  GameInfo_t game_info = updateCurrentState();

  ck_assert_int_eq(game_info.pause, 0);
  ck_assert_ptr_nonnull(game_info.field);
  ck_assert_ptr_nonnull(game_info.next);
  ck_assert_int_eq(game_info.score, 0);
  ck_assert_int_eq(game_info.high_score, high_score_init);
  ck_assert_int_eq(game_info.level, 1);
  ck_assert_int_eq(game_info.speed, SPEED_BASE);
  ck_assert_int_eq(game_info.high_score, high_score_init);

  game_info = updateCurrentState();
  int sum_next = 0;
  int sum_field = 0;
  int figure_cols = 0;
  int current_row = 0;

  for (int i = 0; i < 4; i++) {
    int col_sum = 0;
    for (int j = 0; j < 4; j++) {
      sum_next += game_info.next[i][j];

      if (game_info.next[i][j]) col_sum += 1;
    }
    if (col_sum > figure_cols) figure_cols += 1;
  }

  game_info = updateCurrentState();
  for (int i = 0; i < FIELD_HEIGHT; i++) {
    for (int j = 0; j < FIELD_WIDTH; j++) {
      sum_field += game_info.field[i][j];
    }
  }
  ck_assert_int_eq(sum_next, sum_field);

  userInput(Pause, false);
  game_info = updateCurrentState();
  ck_assert_int_eq(game_info.pause, 1);

  userInput(Up, false);
  game_info = updateCurrentState();

  userInput(Pause, false);
  game_info = updateCurrentState();
  ck_assert_int_eq(game_info.pause, 0);

  int field_copy[FIELD_HEIGHT][FIELD_WIDTH];
  for (int i = 0; i < FIELD_HEIGHT; i++) {
    for (int j = 0; j < FIELD_WIDTH; j++) {
      field_copy[i][j] = game_info.field[i][j];
    }
  }

  userInput(Left, false);
  game_info = updateCurrentState();

  userInput(Right, false);
  game_info = updateCurrentState();

  for (int i = 0; i < FIELD_HEIGHT; i++) {
    for (int j = 0; j < FIELD_WIDTH; j++) {
      ck_assert_int_eq(game_info.field[i][j], field_copy[i][j]);
    }
  }

  struct timespec start, now;
  clock_gettime(CLOCK_MONOTONIC, &start);

  do {
    struct timespec req = {0, 1000000L};
    nanosleep(&req, NULL);

    clock_gettime(CLOCK_MONOTONIC, &now);
  } while ((now.tv_sec - start.tv_sec) * 1000 +
               (now.tv_nsec - start.tv_nsec) / 1000000 <
           SPEED_BASE + 1);

  game_info = updateCurrentState();
  game_info = updateCurrentState();
  for (int i = 0; i < FIELD_WIDTH; i++) {
    ck_assert_int_eq(game_info.field[current_row][i], 0);
  }

  userInput(Down, false);
  game_info = updateCurrentState();
  current_row++;
  for (int j = 0; j < FIELD_WIDTH; j++) {
    ck_assert_int_eq(game_info.field[current_row][j], 0);
  }

  for (int i = 0; i < 4; i++) {
    userInput(Action, false);
    game_info = updateCurrentState();
  }

  for (int i = 0; i < FIELD_WIDTH; i++) {
    userInput(Left, false);
    game_info = updateCurrentState();
  }

  userInput(Down, true);
  game_info = updateCurrentState();

  int sum = 0;
  for (int i = FIELD_HEIGHT - 4; i < FIELD_HEIGHT; i++) {
    for (int j = 0; j < 4; j++) {
      sum += game_info.field[i][j];
    }
  }
  ck_assert_int_eq(sum, sum_next);

  game_info = updateCurrentState();

  sum = 0;
  for (int i = FIELD_HEIGHT - 4; i < FIELD_HEIGHT; i++) {
    for (int j = 0; j < 4; j++) {
      sum += game_info.field[i][j];
    }
  }
  ck_assert_int_eq(sum, sum_next / FIELD_SIGN_FIGURE);

  userInput(Terminate, false);
  game_info = updateCurrentState();

  ck_assert_ptr_eq(game_info.field, NULL);
  ck_assert_ptr_eq(game_info.next, NULL);
}

END_TEST

TCase* user_input(void) {
  TCase* tcase = tcase_create("USER_INPUT");
  tcase_add_test(tcase, USER_INPUT_START);
  return tcase;
}