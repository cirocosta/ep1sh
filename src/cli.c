#include "ep1sh/cli.h"

void ep1sh_command_ep1sh(int cli_argc, char** cli_argv)
{
  int command_errcode = 0;
  char* input = NULL;
  char prompt[100];
  char pwd[PATH_MAX] = { 0 };
  char** argv = NULL;
  unsigned argc = 0;
  ENTRY e, *ep;

  ep1sh_init_commands_table();
  rl_bind_key('\t', rl_complete);

  while (1) {
    // FIXME what if 100 is not sufficient? [1]
    snprintf(prompt, sizeof(prompt), "[%s] ", getcwd(pwd, PATH_MAX - 1));

    input = readline(prompt);
    if (!input)
      break;

    add_history(input);
    argv = ep1sh_split_string(input, &argc, ' ');

    if (!argc) {
      FREE(input);
      FREE(argv);
      continue;
    }

    e.key = argv[0];
    ep = hsearch(e, FIND);

    if (ep) // internal command
      command_errcode = (*(ep1sh_command)ep->data)(argc, argv);
    else // executable
      command_errcode = ep1sh_command_execute(argc, argv);

    FREE(input);
    FREE_ARR(argv, argc);
    // TODO HANDLE QUIT SIGNAL
  }

  ep1sh_destroy();
}

void ep1sh_init_commands_table()
{
  ENTRY e, *ep;
  int i = 0;

  hcreate(EP1SH_PROCEDURES_SIZE);

  for (; i < EP1SH_PROCEDURES_SIZE; i++) {
    e.key = EP1SH_PROCEDURES[i].key;
    e.data = EP1SH_PROCEDURES[i].command;
    ep = hsearch(e, ENTER);
    ASSERT(ep != NULL, "Couldn't insert EP1SH_PROCEDURE to HTABLE");
  }
}

void ep1sh_destroy() { hdestroy(); }
