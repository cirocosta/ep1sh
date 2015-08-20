#ifndef EP1SH__CLI_H
#define EP1SH__CLI_H

#include "ep1sh/common.h"

#include "ep1sh/commands/pwd.h"
#include "ep1sh/commands/cd.h"
#include "ep1sh/commands/execute.h"

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

const static ep1sh_command_t EP1SH_PROCEDURES[] = { { "cd", &ep1sh_command_cd },
                                                    { "pwd",
                                                      &ep1sh_command_pwd } };

#define EP1SH_PROCEDURES_SIZE                                                  \
  (sizeof(EP1SH_PROCEDURES) / sizeof(EP1SH_PROCEDURES[0]))

void ep1sh_init_commands_table();
void ep1sh_destroy();
void ep1sh_command_ep1sh(int argc, char** argv, char** envp);
char** ep1sh_tokenize_cli(const char* input, unsigned* size);
char** ep1sh_tokenize_PATH(const char* input, unsigned* size);

#endif // ! EP1SH_CLI_H
