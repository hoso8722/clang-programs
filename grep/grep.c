#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

static void do_grep(regex_t *pat, FILE *f);

int main(int argc, char *argv[]) {
  regex_t pattern;
  int err;
  int i;

  if (argc < 2) {
    fputs("no pattern\n", stderr);
    exit(1);
  }
  err = regcomp(&pattern, argv[1], REG_EXTENDED | REG_NOSUB | REG_NEWLINE);
  if (err != 0) {
    char buf[1024];

    regerror(err, &pattern, buf, sizeof buf);
    puts(buf);
    exit(1);
  }
  if (argc == 2) {
    do_grep(&pattern, stdin);
  } else {
    for (i = 2; i < argc; i++) {
      FILE *f;

      f = fopen(argv[i], "r");
      if (!f) {
        perror(argv[i]);
        exit(1);
      }
      do_grep(&pattern, f);
      fclose(f);
    }
  }
  regfree(&pattern);
  exit(0);
}

static void do_grep(regex_t *pattern, FILE *src) {
  char buf[4096];

  while (fgets(buf, sizeof buf, src)) {
    if (regexec(pattern, buf, 0, NULL, 0) == 0) {
      fputs(buf, stdout);
    }
  }
}