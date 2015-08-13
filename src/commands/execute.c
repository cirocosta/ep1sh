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

bool ep1sh_can_execute(const char* fname)
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

int ep1sh_command_execute(int argc, char** argv) { return EXIT_SUCCESS; }
