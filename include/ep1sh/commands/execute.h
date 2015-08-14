#ifndef EP1SH__EXEC_H
#define EP1SH__EXEC_H

#include "ep1sh/debug.h"
#include "ep1sh/common.h"

#include <linux/limits.h>
#include <sys/wait.h>
#include <stdbool.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>

int ep1sh_command_execute(int argc, char* argv[]);
bool file_ok_(const char* fname);
bool can_execute_(const char* fname);
int get_executable_path_(const char* ename, char* dest);

#endif
