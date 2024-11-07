#define _GNU_SOURCE

#ifndef S21_CAT_H
#define S21_CAT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Flags {
  int flag_b;
  int flag_e;
  int flag_l;
  int flag_n;
  int flag_s;
  int flag_t;
  int flag_u;
  int flag_v;
};

void parse_long_flag(char* flag, struct Flags* flags);
void parse_short_flags(char* flag, struct Flags* flags);
int parse_args(int argc, char* argv[], struct Flags* flags, char** files);
void output(const char* filename, const struct Flags* flags, int* line_number);
void print_overchar(unsigned char ch);
void printline(char* line, int i, const struct Flags* flags);

#endif