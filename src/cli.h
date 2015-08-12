#ifndef EP1SH__CLI_H
#define EP1SH__CLI_H 

#include "common.h"
#include "debug.h"

#include <ctype.h>
#include <string.h>
#include <limits.h>
#include <stdio.h>
#include <stdbool.h>


struct command {
  char* name;
  size_t min_argc;
  size_t max_argc;
  bool built_in;
}; 

static const char* internal_procedures[] = {
  "pwd",
  "cd"
};

char** ep1sh_tokenize(const char* input, unsigned* size);

#endif // ! EP1SH_CLI_H
