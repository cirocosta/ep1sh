#include "ep1sh/commands/cd.h"

bool ep1sh_dir_exists_(const char* dirname)
{
  struct stat sb;

  if (!~stat(dirname, &sb)) {
    perror("(Error) - cd::dir_exists: ");
    return false;
  }

  if (!S_ISDIR(sb.st_mode))
    fprintf(stderr, "%s is not a directory", dirname);

  return true;
}

int ep1sh_command_cd(int argc, char** argv)
{
  char* alloc_home = NULL;
  char* ref_home = NULL;

  if (argc < 2) {
    ref_home = getenv("HOME");

    if (!ref_home) {
      alloc_home = strdup(getpwuid(getuid())->pw_dir);

      if (!ep1sh_dir_exists_(alloc_home)) {
        FREE(alloc_home);
        return EXIT_FAILURE;
      }
    }

  } else if (argc == 2) {
    alloc_home = strdup(argv[1]);
  } else {
    write(STDERR_FILENO, TOO_MANY_ARGS, strlen(TOO_MANY_ARGS));
    return EXIT_FAILURE;
  }

  if (ref_home)
    chdir(ref_home);
  else
    chdir(alloc_home);

  FREE(alloc_home);
  return EXIT_SUCCESS;
}

