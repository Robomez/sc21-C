#include <ctype.h>
#include <stdarg.h>

#include "../s21_string.h"

typedef struct {
  int spec_flag;
  int suppress_flag;
  int width;
  int length;
  long int pointer;
  int eof_flag;
  int err_flag;
} FORMAT;

int s21_sscanf(const char *str, const char *format, ...);
void skip_space(char **str_copy, FORMAT *flags);
int spec_init(FORMAT *flags, const char *format);
int process_str(va_list args, FORMAT *flags, char **str_copy,
                const char *format);
void check_str(char **str_copy, FORMAT *flags, const char *format);
int check_args(va_list args, FORMAT *flags, char **str_copy,
               const char *format);
int format_c(va_list args, FORMAT *flags, char **str_copy);
int format_d(va_list args, FORMAT *flags, char **str_copy, int calc_sys);
int format_f(va_list args, FORMAT *flags, char **str_copy);
int format_u(va_list args, FORMAT *flags, char **str_copy, int calc_sys);
int format_s(va_list args, FORMAT *flags, char **str_copy);
int space_check(char str_copy);
int format_p(va_list args, FORMAT *flags, char **str_copy);
void format_n(va_list args, FORMAT *flags);
void format_prcnt(char **str_copy, FORMAT *flags, const char *format);

int s21_sscanf(const char *str, const char *format, ...) {
  int res = 0;
  FORMAT flags = {0, 0, 0, 0, 0, 0, 0};
  char *str_copy = malloc(s21_strlen(str) * sizeof(char) + 1);
  s21_strncpy(str_copy, str, s21_strlen(str) + 1);

  skip_space(&str_copy, &flags);
  if (!*str_copy) {
    flags.eof_flag = 1;
  }
  str_copy = str_copy - flags.pointer;
  flags.pointer = 0;
  va_list args;
  va_start(args, format);
  for (; *format; format++) {
    if (spec_init(&flags, format)) {
      continue;
    }
    if (flags.spec_flag) {
      if ((int)*format > 47 && (int)*format < 58) {
        flags.width = flags.width * 10 + (int)*format - 48;
        continue;
      }
      res += process_str(args, &flags, &str_copy, format);
    } else {
      check_str(&str_copy, &flags, format);
    }
    if (check_args(args, &flags, &str_copy, format)) {
      if (!res && flags.eof_flag) {
        res = -1;
      }
      break;
    }
  }
  free(str_copy - flags.pointer);
  va_end(args);
  return res;
}

// пропуск пробельных и управляющих символов в строке ввода
void skip_space(char **str_copy, FORMAT *flags) {
  while ((**str_copy >= 9 && **str_copy <= 13) || **str_copy == 32) {
    (*str_copy)++;
    flags->pointer++;
  }
}

// проверка начала спецификатора
int spec_init(FORMAT *flags, const char *format) {
  int res = 0;
  if (*format == '%' && !flags->spec_flag) {
    res++;
    flags->spec_flag = 1;
    flags->suppress_flag = 0;
    flags->length = 0;
    flags->width = 0;
  }
  return res;
}

// обработка форматной строки и строки ввода, с последующим присваиванием
// значений переменным
int process_str(va_list args, FORMAT *flags, char **str_copy,
                const char *format) {
  int res = 0;
  switch (*format) {
    case 'c':
      res += format_c(args, flags, str_copy);
      break;
    case 'd':
      res += format_d(args, flags, str_copy, 10);
      break;
    case 'i':
      res += format_d(args, flags, str_copy, 0);
      break;
    case 'e':
    case 'E':
    case 'f':
    case 'g':
    case 'G':
      res += format_f(args, flags, str_copy);
      break;
    case 'o':  // беззнаковое восмеричное число
      res += format_u(args, flags, str_copy, 8);
      break;
    case 's':
      res += format_s(args, flags, str_copy);
      break;
    case 'u':  // беззнаковое десятичное число
      res += format_u(args, flags, str_copy, 10);
      break;
    case 'x':
    case 'X':  // беззнаковое шестнадцатеричное число
      res += format_u(args, flags, str_copy, 16);
      break;
    case 'p':  // адрес
      res += format_p(args, flags, str_copy);
      break;
    case 'n':
      format_n(args, flags);
      break;
    case '%':
      format_prcnt(str_copy, flags, format);
      break;
    case '*':
      flags->suppress_flag = 1;
      break;
    case 'h':
      flags->length = 1;
      break;
    case 'l':
      flags->length = 2;
      break;
    case 'L':
      flags->length = 3;
      break;
  }

  return res;
}

// проверка соответствия строки ввода формату
void check_str(char **str_copy, FORMAT *flags, const char *format) {
  if ((*format >= 9 && *format <= 13) || *format == 32) {
    while (*format == **str_copy) {
      (*str_copy)++;
      flags->pointer++;
    }
  } else if (**str_copy == *format) {
    (*str_copy)++;
    flags->pointer++;
  } else {
    flags->err_flag = 1;
  }
}

// проверка наличия следующих аргументов, а также наличия спецификатора %n в
// текущем положении строки format
int check_args(va_list args, FORMAT *flags, char **str_copy,
               const char *format) {
  int res = 0;
  va_list copy;
  va_copy(copy, args);
  if ((!**str_copy && (s21_strstr(format, "%n") != s21_strchr(format, '%') ||
                       !s21_strstr(format, "%n"))) ||
      !va_arg(copy, void *) || flags->err_flag) {
    res = 1;
  }
  va_end(copy);
  return res;
}

// формат %c
int format_c(va_list args, FORMAT *flags, char **str_copy) {
  int res = 0;
  if (!flags->suppress_flag) {
    res++;
    *(char *)va_arg(args, char *) = **str_copy;
  }
  (*str_copy)++;
  flags->pointer++;
  flags->spec_flag = 0;
  return res;
}

// формат %d
int format_d(va_list args, FORMAT *flags, char **str_copy, int calc_sys) {
  int res = 0;
  char *end = S21_NULL;
  if (strtol(*str_copy, S21_NULL, calc_sys) || **str_copy == '0') {
    if (!flags->suppress_flag) {
      res++;
      if (flags->length == 1)
        *(short int *)va_arg(args, void *) = strtol(*str_copy, &end, calc_sys);
      else if (flags->length == 2)
        *(long int *)va_arg(args, void *) = strtol(*str_copy, &end, calc_sys);
      else
        *(int *)va_arg(args, void *) = strtol(*str_copy, &end, calc_sys);
    } else {
      strtol(*str_copy, &end, calc_sys);
    }
    flags->pointer += end - *str_copy;
    *str_copy = end;
  } else {
    flags->err_flag = 1;
  }
  flags->spec_flag = 0;
  return res;
}

// вызывается при наличие в строке формата %e %E %g %G %f
int format_f(va_list args, FORMAT *flags, char **str_copy) {
  int res = 0;
  char *end = S21_NULL;
  if (strtold(*str_copy, S21_NULL) || **str_copy == '0') {
    if (!flags->suppress_flag) {
      res++;
      if (flags->length == 3)
        *(long double *)va_arg(args, void *) = strtold(*str_copy, &end);
      else if (flags->length == 2)
        *(double *)va_arg(args, void *) = strtod(*str_copy, &end);
      else
        *(float *)va_arg(args, void *) = strtof(*str_copy, &end);
    } else {
      strtof(*str_copy, &end);
    }
    flags->pointer += end - *str_copy;
    *str_copy = end;
  } else {
    flags->err_flag = 1;
  }
  flags->spec_flag = 0;
  return res;
}

// вызывается при наличие в строке формата %x %X %u %o
int format_u(va_list args, FORMAT *flags, char **str_copy, int calc_sys) {
  int res = 0;
  char *end = S21_NULL;
  if (strtoul(*str_copy, S21_NULL, calc_sys) || **str_copy == '0') {
    if (!flags->suppress_flag) {
      if (strtoul(*str_copy, S21_NULL, calc_sys) || **str_copy == '0') res++;
      if (flags->length == 1)
        *(short unsigned *)va_arg(args, void *) =
            strtoul(*str_copy, &end, calc_sys);
      else if (flags->length == 2)
        *(long unsigned *)va_arg(args, void *) =
            strtoul(*str_copy, &end, calc_sys);
      else
        *(unsigned *)va_arg(args, void *) = strtoul(*str_copy, &end, calc_sys);
    } else {
      strtoul(*str_copy, &end, calc_sys);
    }
    flags->pointer += end - *str_copy;
    *str_copy = end;
  } else {
    flags->err_flag = 1;
  }
  flags->spec_flag = 0;
  return res;
}

int space_check(char str_copy) {
  int res = 1;
  if (str_copy == ' ' || str_copy == '\n' || str_copy == '\v' ||
      str_copy == '\t' || str_copy == '\r' || str_copy == '\f') {
    res = 0;
  }
  return res;
}

int format_s(va_list args, FORMAT *flags, char **str_copy) {
  int res = 0;
  char *str = malloc(sizeof(char));
  skip_space(str_copy, flags);
  int index = 0;
  if (!**str_copy) {
    flags->err_flag = 1;
  } else {
    for (; **str_copy && space_check(**str_copy) &&
           (flags->width == 0 || index < flags->width);
         index++, (*str_copy)++) {
      str[index] = **str_copy;
      str = realloc(str, (index + 2) * sizeof(char));
    }
    str[index] = '\0';
    if (!flags->suppress_flag) {
      s21_strncpy(va_arg(args, char *), str, index + 1);
    }
    free(str);
    if (!flags->suppress_flag) {
      res++;
    }
    flags->pointer += index;
    flags->spec_flag = 0;
  }

  return res;
}

int format_p(va_list args, FORMAT *flags, char **str_copy) {
  int res = 0;
  char *end = S21_NULL;
  if (strtoul(*str_copy, S21_NULL, 16) || **str_copy == '0') {
    if (!flags->suppress_flag) {
      res++;
      *(void **)va_arg(args, void **) = (void *)strtoul(*str_copy, &end, 16);
    }
    flags->pointer += end - *str_copy;
    *str_copy = end;
  } else {
    flags->err_flag = 1;
  }
  flags->spec_flag = 0;
  return res;
}

void format_n(va_list args, FORMAT *flags) {
  if (!flags->suppress_flag) {
    if (flags->length == 1)
      *(short int *)va_arg(args, void *) = flags->pointer;
    else if (flags->length == 2)
      *(long int *)va_arg(args, void *) = flags->pointer;
    else
      *(int *)va_arg(args, void *) = flags->pointer;
  }
  flags->spec_flag = 0;
}

void format_prcnt(char **str_copy, FORMAT *flags, const char *format) {
  skip_space(str_copy, flags);
  if (*format == **str_copy) {
    flags->pointer++;
    (*str_copy)++;
  } else {
    flags->err_flag = 1;
  }
  flags->spec_flag = 0;
}