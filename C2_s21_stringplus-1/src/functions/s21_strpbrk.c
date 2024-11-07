#include "../s21_string.h"
// by deannecu

char *s21_strpbrk(const char *str1, const char *str2) {
  const char *c1, *c2;  // указатели для строк которые будем сравнивать
  // пока разыменованый указатель(певый символ) ! = \0 потом смещаем указатель
  // на один
  char *result = S21_NULL;
  for (c1 = str1; *c1 != '\0' && result == S21_NULL; c1++) {
    for (c2 = str2; *c2 != '\0' && result == S21_NULL; c2++) {
      // сравниваем разыменованые указатели если равны то возвращаем первый
      if (*c1 == *c2)
        result = (char *)c1;  // приводим тип к указателю на символ
    }
  }
  return result;
}