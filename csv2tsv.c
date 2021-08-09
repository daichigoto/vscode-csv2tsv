#include "csv2tsv.h"

int
main(int argc, char *argv[])
{
    const int bufsize = 1024*1024*10;
    char buf[bufsize];
    int len;
    FILE *fp;

    fp = fopen(argv[1], "r");
    len = fread(buf, 1, bufsize, fp);
    
    csv2tsv(buf, len);

    fclose(fp);

    return 0;
}
