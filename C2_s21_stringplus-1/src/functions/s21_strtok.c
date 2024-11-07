#include "../s21_string.h"

char *s21_strtok(char *str, const char *delim) {
  static char *ended_pointer = S21_NULL;
  char *token;
  int result = 0;

  if (str != S21_NULL) {
    ended_pointer = str;
  }

  if (ended_pointer == S21_NULL || *ended_pointer == '\0') {
    token = S21_NULL;
    result = 1;
  }

  if (result == 0) {
    while (*ended_pointer != '\0' &&
           s21_strchr(delim, *ended_pointer) != S21_NULL) {
      ended_pointer++;
    }

    // Конец строки, больше токенов нет
    if (*ended_pointer == '\0') {
      result = 1;
      ended_pointer = S21_NULL;
      token = S21_NULL;
    }
  }

  if (result == 0) {
    token = ended_pointer;
    ended_pointer = s21_strpbrk(token, delim);
    if (ended_pointer != S21_NULL) {
      *ended_pointer++ = '\0';
    } else {
      ended_pointer = S21_NULL;
    }
  }

  return token;
}