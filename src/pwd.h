#ifndef EP1SH__PWD_H
#define EP1SH__PWD_H

#include <linux/limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

inline int ep1sh_command_pwd(int argc, char** argv)
{
  char buf[PATH_MAX] = { 0 };

  if (getcwd(buf, PATH_MAX)) {
    write(STDOUT_FILENO, "\n", 1);
    write(STDOUT_FILENO, buf, strlen(buf));
    return EXIT_SUCCESS;
  }

  perror("ep1sh_pwd:");
  return EXIT_FAILURE;
}

#endif
