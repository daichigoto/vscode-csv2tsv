#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "main.h"

int main(int argc, char *argv[]) {
  char *csvdata, *tsvdata;
  int csvdata_bytes, tsvdata_bytes;

  csvdata = file2str(argv[1]);
  csvdata_bytes = strlen(csvdata);

  tsvdata_bytes = csvdata_bytes;
  tsvdata = calloc(sizeof(char), tsvdata_bytes + 1);

  csv2tsv(csvdata, csvdata_bytes, tsvdata, tsvdata_bytes);

  printf("%s", tsvdata);

  return 0;
}
