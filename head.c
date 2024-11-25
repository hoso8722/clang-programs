#include <stdio.h>
#include <stdlib.h>

static void do_head(FILE *f, long nlines);

int main(int argc, char *argv[])
{
  if (argc != 2)
  {
    fprintf(stderr, "Usage: %s n\n", argv[0]);
    exit(1);
  }
}