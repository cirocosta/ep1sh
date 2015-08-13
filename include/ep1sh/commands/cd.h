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

static inline bool dir_exists(const char* dirname)
{
  struct stat sb;

  if (!~stat(dirname, &sb)) {
    perror("cd::dir_exists: ");
    return false;
  }

  if (!S_ISDIR(sb.st_mode))
    fprintf(stderr, "%s is not a directory", dirname);

  return true;
}

static inline int ep1sh_command_cd(int argc, char** argv)
{
  char* homedir = NULL;
  char* str_ref = NULL;

  if (argc < 2) {
    str_ref = getenv("HOME");
    // duplicate so that we do not free the wrong thing
    if (str_ref != NULL)
      homedir = strdup(str_ref);
    else
      homedir = strdup(getpwuid(getuid())->pw_dir);
    if (!dir_exists(homedir)) {
      FREE(homedir);
      return EXIT_FAILURE;
    }
    str_ref = NULL;
  } else if (argc == 2) {
    homedir = realpath(argv[1], NULL);
    if (homedir == NULL) {
      perror("cd: ");
      return EXIT_FAILURE;
    }
  } else {
    write(STDERR_FILENO, TOO_MANY_ARGS, strlen(TOO_MANY_ARGS));
    return EXIT_FAILURE;
  }

  chdir(homedir);

  FREE(homedir);
  return EXIT_SUCCESS;
}

#endif
