#include "s21_cat.h"

int main(int argc, char *argv[]) {
  struct Flags flags = {0};
  char **files = (char **)malloc(argc * sizeof(char *));

  int filecount = parse_args(argc, argv, &flags, files);
  int line_number = 1;

  for (int i = 0; i < filecount; i++) {
    output(files[i], &flags, &line_number);
  }

  for (int i = 0; i < filecount; i++) {
    free(files[i]);
  }
  free(files);

  return 0;
}

int parse_args(int argc, char *argv[], struct Flags *flags, char **files) {
  int filenum = 0;
  for (int i = 1; i < argc; i++) {
    if (argv[i][0] == '-') {
      // It's a flag
      if (argv[i][1] == '-') {
        // long flag
        parse_long_flag(argv[i], flags);
      } else {
        parse_short_flags(argv[i], flags);
      }
    } else {
      // it's a filename
      files[filenum] = (char *)malloc((strlen(argv[i]) + 1) * sizeof(char));
      strcpy(files[filenum], argv[i]);
      filenum++;
    }
  }
  return filenum;
}

void parse_long_flag(char *flag, struct Flags *flags) {
  if (strcmp(flag, "--number-nonblank") == 0) {
    flags->flag_b = 1;
  } else if (strcmp(flag, "--number") == 0) {
    flags->flag_n = 1;
  } else if (strcmp(flag, "--squeeze-blank") == 0) {
    flags->flag_s = 1;
  } else if (strcmp(flag, "--show-nonprinting") == 0) {
    flags->flag_v = 1;
  }
}

void parse_short_flags(char *flag, struct Flags *flags) {
  int j = 1;
  while (flag[j] != '\0') {
    switch (flag[j]) {
      case 'b':
        flags->flag_b = 1;
        break;
      case 'e':
        flags->flag_e = 1;
        flags->flag_v = 1;
        break;
      case 'l':
        flags->flag_l = 1;
        break;
      case 'n':
        flags->flag_n = 1;
        break;
      case 's':
        flags->flag_s = 1;
        break;
      case 't':
        flags->flag_t = 1;
        flags->flag_v = 1;
        break;
      case 'u':
        flags->flag_u = 1;
        break;
      case 'v':
        flags->flag_v = 1;
        break;
      case 'E':
        flags->flag_e = 1;
        break;
      case 'T':
        flags->flag_t = 1;
        break;
      default:
        break;
    }
    j++;
  }
}

void output(const char *filename, const struct Flags *flags, int *line_number) {
  FILE *file = fopen(filename, "r");
  if (file == NULL) {
    printf("unable to open file %s\n", filename);
    return;
  }

  char *line = NULL;
  size_t line_size = 0;
  ssize_t line_read = 0;
  int repeated_blank = 0;

  while ((line_read = getline(&line, &line_size, file)) != -1) {
    if (line[0] == '\n')
      repeated_blank++;
    else
      repeated_blank = 0;
    // S FLAG
    if (flags->flag_s && repeated_blank > 1) continue;

    // B FLAG
    if (flags->flag_b) {
      if (strcmp(line, "\n") != 0) printf("%6d\t", *line_number);
    }

    // N FLAG (WITHOUT B)
    if (flags->flag_n && !flags->flag_b) printf("%6d\t", *line_number);

    // E FLAG
    int len_line = line_read;
    for (int i = 0; i < len_line; i++) {
      printline(line, i, flags);
    }

    if (!(flags->flag_b && strcmp(line, "\n") == 0)) {
      *line_number += 1;
    }
  }

  free(line);
  fclose(file);
}

void printline(char *line, int i, const struct Flags *flags) {
  unsigned char ch = line[i];
  if (line[i] == '\n' && flags->flag_e && flags->flag_v) {
    if (i == 0 && flags->flag_b) {
      printf("$\n");
      // FOR MAC?
      // printf("      \t$\n");
    } else {
      printf("$\n");
    }
  }
  // T FLAG
  else if (ch == '\t' && flags->flag_t && flags->flag_v) {
    printf("^I");
    // V FLAG
  } else if (flags->flag_v) {
    print_overchar(ch);
  } else
    printf("%c", ch);
}

void print_overchar(unsigned char ch) {
  if (ch < 32 && ch != '\t' && ch != '\n')
    printf("^%c", (ch + 64));
  else if (ch == 127)
    printf("^?");
  else if (ch > 127) {
    printf("M-");
    print_overchar(ch - 128);
  } else
    printf("%c", ch);
}
