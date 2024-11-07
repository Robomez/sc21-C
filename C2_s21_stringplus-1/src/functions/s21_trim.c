#include "../s21_string.h"

// by deannecu

// проверям есть ли символ в масиве трим
int is_trim(char c, const char *trim) {
  int result = 0;
  while (*trim) {
    if (c == *trim) result = 1;
    trim++;
  }
  return result;
}

void *s21_trim(const char *src,
               const char *trim_chars) {  // если строки пусты возвращаем нулл
  if (!src || !trim_chars) {
    return S21_NULL;
  }

  // указатель для поиска стартовой позиции
  const char *start = src;
  // пока есть символ и этот символо в масиве трим
  while (*start && is_trim(*start, trim_chars)) {
    start++;
  }

  // длина строки для поиска конечной позиции
  int src_len = s21_strlen(src);
  // укозатель на конец строки
  const char *end = src + src_len - 1;
  // пока указатель на энд больше укозателя на старт и символ в масиве трим
  while (end >= start && is_trim(*end, trim_chars)) {
    end--;
  }
  // находим длину новой стрки вычетая адреса
  int new_len = end >= start ? end - start + 1 : 0;

  // выделяем память для новой строки
  char *trimmed_str = (char *)malloc(new_len + 1);
  if (!trimmed_str) {
    trimmed_str = S21_NULL;
  }
  if (trimmed_str) {
    // заполняем выеленую память
    s21_strncpy(trimmed_str, start, new_len);
    trimmed_str[new_len] = '\0';
  }
  return trimmed_str;
}
