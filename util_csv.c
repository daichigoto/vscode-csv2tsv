#include <stdbool.h>

static bool record_outputed;

static char gettsvchar(const char);

int csv2tsv(const char *ibuf, int ibufsize, char *obuf, int obufsize) {
  // When the target is empty, no processing is done.
  if (0 == ibufsize)
    return 0;

  const char *p_i, *end_i;
  char *p_o;
  int tsv_len = 0;

  p_i = ibuf;
  end_i = &ibuf[ibufsize - 1];

  p_o = obuf;

  // Indicates the state during parsing.
  typedef enum FIELD_STATUS {
    FIELD_END,
    IN_FIELD,
    IN_QUOTED_FIELD
  } record_status;
  record_status rs = FIELD_END;

  record_outputed = false;
  while (1) {
    if ('\n' == *p_i) {
      if (!record_outputed) {
        // nothing
      }
      rs = FIELD_END;
      *p_o = gettsvchar('\n');
      ++p_o;
      ++tsv_len;
    } else {
      switch (rs) {
      case FIELD_END:
        if (',' == *p_i) {
          // nothing
        } else if ('"' == *p_i) {
          rs = IN_QUOTED_FIELD;
        } else {
          rs = IN_FIELD;
          *p_o = gettsvchar(*p_i);
          ++p_o;
          ++tsv_len;
        }
        break;
      case IN_FIELD:
        if (',' == *p_i) {
          rs = FIELD_END;
        } else {
          *p_o = gettsvchar(*p_i);
          ++p_o;
          ++tsv_len;
        }
        break;
      case IN_QUOTED_FIELD:
        if ('"' == *p_i) {
          if (p_i == end_i) {
            rs = FIELD_END;
          } else if (',' == *(p_i + 1)) {
            rs = FIELD_END;
            ++p_i;
          } else if ('"' == *(p_i + 1)) {
            *p_o = gettsvchar(*p_i);
            ++p_o;
            ++tsv_len;
            ++p_i;
          }
        } else {
          *p_o = gettsvchar(*p_i);
          ++p_o;
          ++tsv_len;
        }
        break;
      }

      switch (rs) {
      case FIELD_END:
        *p_o = '\t';
        ++p_o;
        ++tsv_len;
        record_outputed = false;
        break;
      case IN_FIELD:
      case IN_QUOTED_FIELD:
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

static char gettsvchar(const char c) {
  record_outputed = true;
  if ('\t' == c) {
    return ' ';
  } else {
    return c;
  }
}
