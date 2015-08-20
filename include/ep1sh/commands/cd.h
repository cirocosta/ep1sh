#ifndef EP1SH__CD_H
#define EP1SH__CD_H

#include "ep1sh/common.h"

#include <sys/types.h>
#include <sys/stat.h>

#include <pwd.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <stdbool.h>

#include <stdlib.h>
#include <unistd.h>

static const char* TOO_MANY_ARGS = "\nError: Too many arguments supplied.\n"
                                   "Usage: cd [pathname]\n";


bool ep1sh_dir_exists_(const char* dirname);
int ep1sh_command_cd(int argc, char** argv);

#endif
