#include "../s21_string.h"
// by deannecu

char *s21_strstr(const char *haystack, const char *needle) {
  if (!*needle)  // если пернвый символ needle пуст возфращяем haystack
    return (char *)haystack;

  const char *hay;  // указатель на haystack

  for (hay = haystack; *hay != '\0'; hay++) {  // двигаемся по haystack
    const char *hay1 =
        hay;  // временный указатель чтобы сравнивать haystack с needle
    const char *nedl = needle;  // указатель на needle
    // двигаемся по временному haystack и needle и сравниваем *символы
    while (*hay1 && *nedl && *hay1 == *nedl) {
      hay1++;
      nedl++;
    }
    // после прохода смотрим дошли ли до конца needle
    // если да то возвращяем первый указатель на haystack
    if (*nedl == '\0') return (char *)hay;
  }
  return S21_NULL;
}