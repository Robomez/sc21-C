#define _GNU_SOURCE

#ifndef S21_GREP_H
#define S21_GREP_H

#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Arguments {
  int e;
  int i;
  int v;
  int c;
  int l;
  int n;
  int h;
  int s;
  int f;
  int o;

  char *pattern;
  int len_pattern;
  int mem_pattern;
} args;

int parse_args(int argc, char *argv[], args *Arguments);
int pattern_from_file(args *Arguments, char *filename);
void pattern_add(args *Arguments, char *pattern);
void get_line(int argc, char *filename, args *Arguments, FILE *file);
void print_flag_c(args *Arguments, int count_matches, int filecount,
                  char *filename);
void print_flag_o(args *Arguments, regex_t *re, char *line, char *filename,
                  int filecount, int line_count);
void print_line(char *line, int read);

args Arguments = {0};
regex_t re;

#endif