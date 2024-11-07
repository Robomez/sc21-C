#ifndef SRC_S21_MATRIX_H_
#define SRC_S21_MATRIX_H_

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define OK 0
#define INCORRECT_MATRIX 1
#define CALCULATION_ERROR 2

#define SUCCESS 1
#define FAILURE 0

#define EPSILON 1e-07

/**
 * @brief Структура для представления матрицы.
 * 
 * Поля:
 * 
 * - matrix: (double **) указатель на double значений в матрице
 * 
 * - rows, columns: (int) размер матрицы рядов, колонок.
 */
typedef struct matrix_struct {
  double** matrix;
  int rows;
  int columns;
} matrix_t;

int s21_matrix_ok( matrix_t *A);

void s21_print_matrix(matrix_t result);
void s21_initialize_matrix(matrix_t *A, double start_value, double iteration_step);

int s21_matrices_same_size(matrix_t *A, matrix_t *B);

matrix_t *s21_make_minor(int excluded_row, int excluded_column, matrix_t *A);
void calc_determ(int *temp, double *result, int i, matrix_t *A, int *sign);

int s21_create_matrix(int rows, int columns, matrix_t *result);
void s21_remove_matrix(matrix_t *A);
int s21_eq_matrix(matrix_t *A, matrix_t *B);
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_mult_number(matrix_t *A, double number, matrix_t *result);
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_transpose(matrix_t *A, matrix_t *result);
int s21_determinant(matrix_t *A, double *result);
int s21_calc_complements(matrix_t *A, matrix_t *result);
int s21_inverse_matrix(matrix_t *A, matrix_t *result);


#endif