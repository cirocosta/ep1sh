#include "ep1sh/commands/execute.h"

bool ep1sh_file_ok(const char* fname)
{
  int rval;

  rval = access(fname, F_OK);

  if (!rval)
    return true;

  DLOGERR("The file %s can't be accessed.\n"
          "Internal Error (%d): %s",
          fname, errno, strerror(errno));

  return false;
}

bool ep1sh_is_executable(const char* fname)
{
  int rval;

  rval = access(fname, X_OK);

  if (!rval)
    return true;

  DLOGERR("The file %s can't be executed.\n"
          "Internal Error (%d): %s",
          fname, errno, strerror(errno));

  return false;
}

int ep1sh_command_execute(int argc, char** argv)
{
  const size_t arg0_size = strlen(argv[0]);
  pid_t pid = 0;
  int child_errcode = 1;

  if (arg0_size < 2)
    return EXIT_SUCCESS;

  if (argv[0][0] == '/' || (argv[0][0] == '.' && argv[0][1] == '/') ||
      (argv[0][0] == '.' && argv[0][1] == '.' && argv[0][2] == '/')) {
    if (ep1sh_file_ok(argv[0]) && ep1sh_is_executable(argv[0])) {
      switch (pid = fork()) {
        case -1:  // error
          // TODO
          break;
        case 0:   // child
          exit(child_errcode);
        default:  // parent
          wait(&child_errcode);
          break;
      }
    }
  } else {
    fprintf(stdout, "Not cool ... an executable name");
  }

  return EXIT_SUCCESS;
}
