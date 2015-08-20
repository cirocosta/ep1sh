#include "ep1sh/commands/pwd.h"

int ep1sh_command_pwd(int argc, char** argv)
{
  char buf[PATH_MAX] = { 0 };

  if (getcwd(buf, PATH_MAX)) {
    write(STDOUT_FILENO, buf, strlen(buf));
    write(STDOUT_FILENO, "\n", 2);
    return EXIT_SUCCESS;
  }

  perror("ep1sh_pwd:");
  return EXIT_FAILURE;
}
