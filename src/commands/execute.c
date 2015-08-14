#include "ep1sh/commands/execute.h"

bool file_ok_(const char* fname)
{
  int rval;

  rval = access(fname, F_OK);

  if (!rval)
    return true;
  return false;
}

bool is_executable_(const char* fname)
{
  int rval;

  rval = access(fname, X_OK);

  if (!rval)
    return true;
  return false;
}

int get_executable_path_(const char* ename, char* dest)
{
  char** paths = NULL;
  unsigned paths_size = 0;
  unsigned i = 0;

  if (ename[0] == '/' || (ename[0] == '.' && ename[1] == '/') ||
      (ename[0] == '.' && ename[1] == '.' && ename[2] == '/')) {
    if (!(file_ok_(ename) && is_executable_(ename)))
      return -1;

    strcpy(dest, ename);
    return 0;
  }

  paths = ep1sh_split_string(getenv("PATH"), NULL, ':');
  if (!paths[0]) {
    FREE(paths);
    return -1;
  }

  while (paths[i]) {
    strcpy(dest, paths[i]);
    strcat(dest, "/");
    strcat(dest, ename);
    if (file_ok_(dest) && is_executable_(dest)) {
      FREE_ARR(paths, paths_size);
      return 0;
    }
    i++;
  }

  FREE_ARR(paths, paths_size);
  return -1;
}

int ep1sh_command_execute(int argc, char** argv, char** envp)
{
  char executable_path[PATH_MAX] = {0};
  const size_t arg0_size = strlen(argv[0]);
  pid_t pid = 0;
  int child_errcode = 0;

  if (arg0_size < 2)
    return EXIT_SUCCESS;

  if (!~get_executable_path_(argv[0], executable_path)) {
    fprintf(stderr, "%s is not an executable :(\n", argv[0]);
    return EXIT_SUCCESS;
  }

  switch (pid = fork()) {
    case -1: // error
      perror("(Error) ep1sh_command_execute: ");
      return EXIT_FAILURE;
    case 0: // child
      child_errcode = execve(executable_path, argv, envp);
      exit(child_errcode);
    default: // parent
      wait(&child_errcode);
      break;
  }

  return EXIT_SUCCESS;
}
