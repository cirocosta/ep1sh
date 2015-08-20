#include "ep1sh/cli.h"

void ep1sh_command_ep1sh(int cli_argc, char** cli_argv, char** envp)
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
    // FIXME what if 100 is not sufficient? [1] -- asprintf
    snprintf(prompt, sizeof(prompt), "[%s] ", getcwd(pwd, PATH_MAX - 1));

    input = readline(prompt);
    if (!input)
      break;

    add_history(input);
    argv = ep1sh_tokenize_cli(input, &argc);

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
      command_errcode = ep1sh_command_execute(argc, argv, envp);

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

char** ep1sh_tokenize_cli(const char* input, unsigned* size)
{
  char** argv = NULL;
  int register i = 0;
  argv = history_tokenize(input);

  if (!size)
    return argv;

  if (!argv) {
    *size = 0;
    ASSERT((argv = malloc(sizeof(char*))), "Couldn't allocate");
    argv[0] = NULL;

    return argv;
  }

  for (; argv[i]; i++)
    ;
  *size = i;

  return argv;
}

char** ep1sh_tokenize_PATH(const char* input, unsigned* size)
{
  char** argv = NULL;
  char** argv2 = NULL;
  char* tmp_history_word_delimiters = history_word_delimiters;
  int register i = 0;
  int register k = 0;

  history_word_delimiters = ":";
  argv = history_tokenize(input);
  history_word_delimiters = tmp_history_word_delimiters;

  // count size of the new argv and allocate
  for (; argv[i]; i++)
    if (argv[i][0] != ':')
      k++;
  ASSERT((argv2 = malloc(sizeof(*argv2) * (k + 1))),
         "Couldn't allocate memory for new argv");

  k = 0;
  // populate new argv2 and free old argv
  for (i = 0; argv[i]; i++)
    if (argv[i][0] != ':')
      argv2[k++] = strdup(argv[i]);
  argv2[k] = NULL;
  FREE_ARR(argv, i);

  if (size)
    *size = (unsigned)k;
  return argv2;
}

void ep1sh_destroy() { hdestroy(); }
