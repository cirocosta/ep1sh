#include "ep1sh/cli.h"

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv, char** envp)
{
  ep1sh_command_ep1sh(argc, argv, envp);

  return EXIT_SUCCESS;
}

