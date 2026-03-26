#include "tests.h"

START_TEST(COPY_MATRIX) {
  const int src[4][4] = {
      {0, 1, 2, 3}, {4, 5, 6, 7}, {8, 9, 10, 11}, {12, 13, 14, 15}};
  int** srcPtr = NULL;

  figure_t dest = {0};

  AllocateArray(&(dest.matrix), 4, 4);
  AllocateArray(&(srcPtr), 4, 4);

  CopyMatrixToFigure(&dest, src);

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      ck_assert_int_eq(dest.matrix[i][j], src[i][j]);
    }
  }
  FreeArray(dest.matrix, 4);
  FreeArray(srcPtr, 4);
}
END_TEST

START_TEST(COPY_MATRIX_2X_POINTER) {
  const int src[4][4] = {
      {0, 1, 2, 3}, {4, 5, 6, 7}, {8, 9, 10, 11}, {12, 13, 14, 15}};
  int** srcPtr = NULL;

  figure_t dest = {0};

  AllocateArray(&(dest.matrix), 4, 4);
  AllocateArray(&(srcPtr), 4, 4);

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      srcPtr[i][j] = src[i][j];
    }
  }

  int result = CopyMatrixToFigure(&dest, srcPtr);
  ck_assert_int_eq(result, 0);

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      ck_assert_int_eq(dest.matrix[i][j], src[i][j]);
    }
  }
  FreeArray(dest.matrix, 4);
  FreeArray(srcPtr, 4);
}

END_TEST

START_TEST(COPY_MATRIX_FAIL) {
  const int src[4][4] = {
      {0, 1, 2, 3}, {4, 5, 6, 7}, {8, 9, 10, 11}, {12, 13, 14, 15}};
  figure_t dest = {0};

  int result = 0;

  dest.matrix = (int**)1;
  result = CopyMatrixToFigure(&dest, (int**)NULL);
  ck_assert_int_eq(result, RUNTIME_ERROR);

  result = CopyMatrixToFigure(&dest, (int(*)[4])NULL);
  ck_assert_int_eq(result, RUNTIME_ERROR);

  result = CopyMatrixToFigure((figure_t*)NULL, (int**)NULL);
  ck_assert_int_eq(result, RUNTIME_ERROR);

  result = CopyMatrixToFigure((figure_t*)NULL, src);
  ck_assert_int_eq(result, RUNTIME_ERROR);

  dest.matrix = NULL;
  result = CopyMatrixToFigure(&dest, src);
  ck_assert_int_eq(result, RUNTIME_ERROR);

  result = CopyMatrixToFigure(&dest, (int**)src);
  ck_assert_int_eq(result, RUNTIME_ERROR);
}

END_TEST

TCase* tcase_copy_matrix(void) {
  TCase* tcase = tcase_create("COPY_MATRIX");
  tcase_add_test(tcase, COPY_MATRIX);
  tcase_add_test(tcase, COPY_MATRIX_2X_POINTER);
  tcase_add_test(tcase, COPY_MATRIX_FAIL);
  return tcase;
}