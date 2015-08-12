#ifndef EP1SH__EXEC_H
#define EP1SH__EXEC_H

#include <stdbool.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include "debug.h"

bool ep1sh_file_ok(const char* fname);
bool ep1sh_can_execute(const char* fname);
int ep1sh_command_execute(int argc, char* argv[]);

#endif
