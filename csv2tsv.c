#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "csv2tsv.h"

int
main(int argc, char *argv[])
{
    char *csvdata, *tsvdata;
    int csvdata_bytes, tsvdata_bytes;

    csvdata = file2str(argv[1]);
    csvdata_bytes = strlen(csvdata);

    tsvdata_bytes = csvdata_bytes + 1;
    tsvdata = calloc(sizeof(char), tsvdata_bytes); 

    csv2tsv(csvdata, csvdata_bytes, tsvdata, csvdata_bytes);

    printf("%s", tsvdata);

    return 0;
}
