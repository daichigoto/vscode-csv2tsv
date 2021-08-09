#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>

char *
file2str(const char *filepath)
{
	struct stat st;
	int	filesize, c;

	char	*buf, *p;

	FILE *fp;

	stat(filepath, &st);
	filesize = st.st_size;

	buf = calloc(sizeof(char), filesize + 1);
	p = buf;

	fp = fopen(filepath, "r");
	for (int i = 0; i < filesize; i++) {
	 c = fgetc(fp);
	 if (EOF == c) {
	  break;
	 }
	 *p = (char)c;
	  ++p;
	}

	return buf;
}
