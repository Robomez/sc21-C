// #include "s21_matrix.h"

// int main(void) {
//   // matrix_t A = {};
//   // s21_create_matrix(3, 3, &A);
//   // A.matrix[0][0] = 1;
//   // A.matrix[0][1] = 2;
//   // A.matrix[0][2] = 3;
//   // A.matrix[1][0] = 0;
//   // A.matrix[1][1] = 4;
//   // A.matrix[1][2] = 2;
//   // A.matrix[2][0] = 5;
//   // A.matrix[2][1] = 2;
//   // A.matrix[2][2] = 1;

//   // s21_print_matrix(A);
//   // matrix_t resu = {};
//   // int total = s21_calc_complements(&A, &resu);;
//   // printf("resu %d \n", total);
//   // s21_print_matrix(resu);

//   // A.matrix[0][0] = 1;
//   // A.matrix[0][1] = -2;
//   // A.matrix[0][2] = 3;
//   // A.matrix[1][0] = 4;
//   // A.matrix[1][1] = 0;
//   // A.matrix[1][2] = 6;
//   // A.matrix[2][0] = -7;
//   // A.matrix[2][1] = 8;
//   // A.matrix[2][2] = 9;

//   // s21_print_matrix(A);
//   // double kipa = 0;
//   // int supa = s21_determinant(&A, &kipa);
//   // printf("supa %d kipa %f\n", supa, kipa);

//   matrix_t B = {};
//   s21_create_matrix(3, 3, &B);
//   B.matrix[0][0] = 2;
//   B.matrix[0][1] = 5;
//   B.matrix[0][2] = 7;
//   B.matrix[1][0] = 6;
//   B.matrix[1][1] = 3;
//   B.matrix[1][2] = 4;
//   B.matrix[2][0] = 5;
//   B.matrix[2][1] = -2;
//   B.matrix[2][2] = 3;

//   // B.matrix[0][0] = 1;
//   // B.matrix[0][1] = 2;
//   // B.matrix[0][2] = 3;
//   // B.matrix[1][0] = 4;
//   // B.matrix[1][1] = 5;
//   // B.matrix[1][2] = 6;
//   // B.matrix[2][0] = 7;
//   // B.matrix[2][1] = 8;
//   // B.matrix[2][2] = 9;

//   s21_print_matrix(B);
//   matrix_t rese = {};
//   int kopto = s21_inverse_matrix(&B, &rese);
//   printf("kopto %d\n", kopto);
//   s21_print_matrix(rese);
// }