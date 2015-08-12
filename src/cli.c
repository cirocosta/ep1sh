#include "cli.h"

char** ep1sh_tokenize(const char* input, unsigned* size)
{
  unsigned count = 0;
  unsigned i = 0;
  size_t input_size = strlen(input);
  char** result = NULL;
  char* tmp = strndup(input, input_size);
  char* tmp_init = tmp;

  while (i < input_size) {
    while (isspace(tmp[i++]) && i < input_size)
      ;
    while (!isspace(tmp[i++]) && i < input_size)
      ;
    count++;
  }

  result = malloc(count * sizeof(*result));
  ASSERT(result, "Couldn't allocate memory during tokenization");
  count = 0;

  tmp = strtok(tmp, " ");
  while (tmp != NULL) {
    *(result + count) = strdup(tmp);
    ASSERT(result + count, "Couldn't allocate memory during tokenization");
    tmp = strtok(NULL, " ");
    count++;
  }

  *size = count;

  FREE(tmp_init);
  return result;
}
