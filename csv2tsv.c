#include "csv2tsv.h"

int
main(int argc, char *argv[])
{
    char dummybuf1[4096];
    char dummybuf2[4096];

    csv2tsv(dummybuf1, dummybuf2);

    return 0;
}
