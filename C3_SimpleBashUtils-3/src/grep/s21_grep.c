#include "s21_grep.h"

int main(int argc, char *argv[]) {
  int result = 0;
  if (argc == 1) result = 1;

  if (result == 0) {
    result = parse_args(argc, argv, &Arguments);

    if (result == 0) {
      for (int i = optind; i < argc; i++) {
        FILE *file = fopen(argv[i], "r");
        if (file == NULL) {
          // S FLAG
          if (!Arguments.s) perror(argv[i]);
          continue;
        } else
          get_line(argc, argv[i], &Arguments, file);

        fclose(file);
      }
    }

    free(Arguments.pattern);
    result = 0;
  } else
    result = 2;

  return result;
}

int parse_args(int argc, char *argv[], args *Arguments) {
  int opt = 0;
  int result = 0;

  while ((opt = getopt_long(argc, argv, "e:ivclnhsf:o", NULL, NULL)) != -1) {
    switch (opt) {
      case 'e':
        Arguments->e = 1;
        pattern_add(Arguments, optarg);
        break;
      case 'i':
        Arguments->i = 1;
        break;
      case 'v':
        Arguments->v = 1;
        break;
      case 'c':
        Arguments->c = 1;
        break;
      case 'l':
        Arguments->l = 1;
        break;
      case 'n':
        Arguments->n = 1;
        break;
      case 'h':
        Arguments->h = 1;
        break;
      case 's':
        Arguments->s = 1;
        break;
      case 'f':
        Arguments->f = 1;
        result = pattern_from_file(Arguments, optarg);
        break;
      case 'o':
        Arguments->o = 1;
        break;
      default:
        printf("error\n");
        break;
    }
  }

  if (Arguments->len_pattern == 0 && argc - optind != 0) {
    pattern_add(Arguments, argv[optind]);
    optind++;
  }
  return result;
}

int pattern_from_file(args *Arguments, char *filename) {
  int result = 0;
  FILE *file = fopen(filename, "r");

  if (file == NULL) {
    if (!Arguments->s) {
      perror(filename);
    }
    result = 1;
  }

  if (result == 0) {
    char *line = NULL;
    size_t mem_line = 0;

    int read = getline(&line, &mem_line, file);

    while (read != -1) {
      if (line[read - 1] == '\n') line[read - 1] = '\0';
      pattern_add(Arguments, line);
      read = getline(&line, &mem_line, file);
    }

    free(line);
    fclose(file);
  }
  return result;
}

void pattern_add(args *Arguments, char *pattern) {
  int n = strlen(pattern);

  if (Arguments->pattern == 0) {
    Arguments->pattern = malloc(1024 * sizeof(char));
    Arguments->mem_pattern = 1024;
  }

  if (Arguments->mem_pattern < Arguments->len_pattern + n) {
    Arguments->pattern =
        realloc(Arguments->pattern, Arguments->mem_pattern * 2);
  }

  if (Arguments->len_pattern != 0) {
    strcat(Arguments->pattern + Arguments->len_pattern, "|");
    Arguments->len_pattern++;
  }

  Arguments->len_pattern +=
      sprintf(Arguments->pattern + Arguments->len_pattern, "(%s)", pattern);
}

void get_line(int argc, char *filename, args *Arguments, FILE *file) {
  int filecount = argc - optind, read = 0, error = 0, line_count = 1,
      count_matches = 0;
  char *line = NULL;
  size_t mem_line = 0;

  // I FLAG
  if (Arguments->i)
    error = regcomp(&re, Arguments->pattern, REG_EXTENDED | REG_ICASE);
  else
    error = regcomp(&re, Arguments->pattern, REG_EXTENDED | 0);
  if (error) perror("Error");

  while ((read = getline(&line, &mem_line, file)) != -1) {
    int result = regexec(&re, line, 0, NULL, 0);

    // V FLAG
    if ((result == 0 && !Arguments->v) || (Arguments->v && result != 0)) {
      if (!Arguments->c && !Arguments->l && !Arguments->o) {
        if (filecount > 1 && !Arguments->h) printf("%s:", filename);

        // N + H FLAGS
        if (Arguments->n) printf("%d:", line_count);
        print_line(line, read);
      }
      count_matches += 1;
    }

    // O FLAG
    if (result == 0 && Arguments->o && !Arguments->c /* FOR LINUX */ &&
        !Arguments->l /* LINUX */) {
      /* FOR LINUX */
      if (Arguments->v) {
      } /* LINUX */
      else
        print_flag_o(Arguments, &re, line, filename, filecount, line_count);
    }
    line_count += 1;
  }

  // C FLAG
  if (Arguments->c /* FOR LINUX */ && !Arguments->l /* LINUX */)
    print_flag_c(Arguments, count_matches, filecount, filename);

  // L FLAG
  if (Arguments->l && count_matches > 0) printf("%s\n", filename);

  free(line);
  regfree(&re);
}

void print_flag_c(args *Arguments, int count_matches, int filecount,
                  char *filename) {
  if (Arguments->l && count_matches > 0) count_matches = 1;

  // H FLAG
  if (filecount > 1 && !Arguments->h) {
    printf("%s:%d\n", filename, count_matches);
  } else {
    printf("%d\n", count_matches);
  }
}

void print_line(char *line, int read) {
  for (int i = 0; i < read; i++) {
    printf("%c", line[i]);
  }
  if (line[read - 1] != '\n') {
    printf("\n");
  }
}

void print_flag_o(args *Arguments, regex_t *re, char *line, char *filename,
                  int filecount, int line_count) {
  regmatch_t match;
  int offset = 0;

  while (1) {
    int result = regexec(re, line + offset, 1, &match, 0);

    if (result != 0) {
      break;
    }

    if (filecount > 1 && !Arguments->h) {
      printf("%s:", filename);
    }

    if (Arguments->n) {
      printf("%d:", line_count);
    }

    for (int i = match.rm_so; i < match.rm_eo; i++) {
      printf("%c", line[offset + i]);
    }
    printf("\n");

    offset += match.rm_eo;
  }
}