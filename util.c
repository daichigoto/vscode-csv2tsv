#include "csv2tsv.h"

static bool record_outputed;

char gettsvchar(const char);

int
csv2tsv(const char *ibuf, int ibufsize, char *obuf, int obufsize)
{
	// When the target is empty, no processing is done.
	if (0 == ibufsize)
		return 0;

	const char	*p_i, *end_i;
	char		*p_o;
	int		tsv_len = 0;

	p_i = ibuf;
	end_i = &ibuf[ibufsize - 1];

	p_o = obuf;

	// Indicates the state during parsing.
	typedef enum RECORD_STATUS { 
		RECORD_END,
		IN_RECORD,
		IN_QUOTED_RECORD
	} record_status;
	record_status	rs = RECORD_END;

	record_outputed = false;
	while (1) {
		if ('\n' == *p_i) {
			if (! record_outputed) {
				// nothing
			}
			rs = RECORD_END;
			*p_o = gettsvchar('\n');
			++p_o;
			++tsv_len;
		}
		else {
			switch (rs) {
			case RECORD_END:
				if (',' == *p_i) {
					// nothing
				}
				else if ('"' == *p_i) {
					rs = IN_QUOTED_RECORD;
				}
				else {
					rs = IN_RECORD;
					*p_o = gettsvchar(*p_i);
					++p_o;
					++tsv_len;
				}
				break;
			case IN_RECORD:
				if (',' == *p_i) {
					rs = RECORD_END;
				}
				else {
					*p_o = gettsvchar(*p_i);
					++p_o;
					++tsv_len;
				}
				break;
			case IN_QUOTED_RECORD:
				if ('"' == *p_i) {
					if (p_i == end_i) {
						rs = RECORD_END;
					}
					else if (',' == *(p_i+1)) {
						rs = RECORD_END;
						++p_i;
					}
					else if ('"' == *(p_i+1)) {
						*p_o = gettsvchar(*p_i);
						++p_o;
						++tsv_len;
						++p_i;
					}
				}
				else {
					*p_o = gettsvchar(*p_i);
					++p_o;
					++tsv_len;
				}
				break;
			}

			switch (rs) {
			case RECORD_END:
				*p_o = gettsvchar('\t');
				++p_o;
				++tsv_len;
				record_outputed = false;
				break;
			case IN_RECORD:
			case IN_QUOTED_RECORD:
				break;
			}
		}

		if (p_i == end_i || tsv_len == obufsize)
			break;
		else
			++p_i;
	}

	return tsv_len;
}

static char 
gettsvchar(const char c)
{
	record_outputed = true;
	if ('\t' == c) {
		return ' ';
	}
	else {
		return c;
	}
}
