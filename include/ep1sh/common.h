#ifndef EP1SH__COMMON_H
#define EP1SH__COMMON_H

#include "ep1sh/debug.h"
#include <stdlib.h>
#include <string.h>

#define FREE(ptr)                                                              \
  do {                                                                         \
    free(ptr);                                                                 \
    ptr = 0;                                                                   \
  } while (0)

#define FREE_ARR(ptr, count)                                                   \
  do {                                                                         \
    unsigned i = 0;                                                            \
    while (i < count)                                                          \
      free(ptr[i++]);                                                          \
    free(ptr);                                                                 \
    ptr = 0;                                                                   \
  } while (0)

const static char MEM_ALOC_ERR_MSG[] =
    "Couldn't allocate memory during tokenization";

/**
 * Splits a string in an array of strings.
 * TODO maybe the best is to just return something like
 *      [{&start, count} ...] so that we avoid all of those
 *      strdup and stuff that must be freed later 
 *
 * Returns an array of allocated mem (n*strdup) that must be freed after use.
 */
static inline char** ep1sh_split_string(const char* input, unsigned* size,
                                        const char delimiter)
{
  size_t input_size = strlen(input);
  unsigned count = 0;
  unsigned i = 0;

  char** result = NULL;
  char* tmp = strndup(input, input_size);
  char* tmp_init = tmp;

  char token_delimiter[2] = { delimiter, '\0' };

  while (i < input_size) {
    while (tmp[i++] == delimiter && i < input_size)
      ;
    while (tmp[i++] != delimiter && i < input_size)
      ;
    count++;
  }

  result = malloc((count + 1) * sizeof(*result));
  ASSERT(result, "%s", MEM_ALOC_ERR_MSG);
  count = 0;

  tmp = strtok(tmp, token_delimiter);
  while (tmp != NULL) {
    *(result + count) = strdup(tmp);
    ASSERT(result + count, "%s", MEM_ALOC_ERR_MSG);
    tmp = strtok(NULL, token_delimiter);
    count++;
  }

  result[count] = NULL;

  if (size)
    *size = count;

  FREE(tmp_init);
  return result;
}

#endif // ! EP1SH__COMMON_H
