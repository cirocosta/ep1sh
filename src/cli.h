#ifndef EP1SH__CLI_H
#define EP1SH__CLI_H

#include "common.h"
#include "debug.h"
#include "pwd.h"
#include "cd.h"
#include "execute.h"

#include <linux/limits.h>
#include <readline/readline.h>
#include <readline/history.h>

#include <search.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>

typedef int (*ep1sh_command)(int argc, char** argv);

typedef struct ep1sh_command_t {
  char* key;
  ep1sh_command command;
} ep1sh_command_t;


static ep1sh_command_t EP1SH_PROCEDURES[] = {
  { "cd", &ep1sh_command_cd },
  { "pwd", &ep1sh_command_pwd },
  { "source", &ep1sh_command_execute },
};

#define EP1SH_PROCEDURES_SIZE                                                  \
  (sizeof(EP1SH_PROCEDURES) / sizeof(EP1SH_PROCEDURES[0]))

char** ep1sh_tokenize(const char* input, unsigned* size);
void ep1sh_init_commands_table();
void ep1sh_destroy();
void ep1sh_command_ep1sh();

#endif // ! EP1SH_CLI_H
