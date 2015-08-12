#include "cli.h"

void ep1sh_command_ep1sh(int cli_argc, char** cli_argv)
{
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
    argv = ep1sh_tokenize(input, &argc);

    if (!argc) {
      FREE(input);
      FREE(argv);
      continue;
    }

    e.key = argv[0];
    ep = hsearch(e, FIND);
    if (!ep) {
      LOGERR("Command %s not found :(", argv[0]);
      FREE(input);
      FREE(argv);
      continue;
    }

    (*(ep1sh_command)ep->data)(argc, argv);


    FREE(input);
    FREE(argv); // FIXME WRONG. Must free each of them. Create a ARR_FREE macro

    // TODO HANDLE QUIT SIGNAL
  }

  ep1sh_destroy();
}

char** ep1sh_tokenize(const char* input, unsigned* size)
{
  unsigned count = 0;
  unsigned i = 0;
  size_t input_size = strlen(input);
  char** result = NULL;
  char* tmp = strndup(input, input_size);
  char* tmp_init = tmp;

  while (i < input_size) {
    while (isspace(tmp[i++]) && i < input_size)
      ;
    while (!isspace(tmp[i++]) && i < input_size)
      ;
    count++;
  }

  result = malloc(count * sizeof(*result));
  ASSERT(result, "Couldn't allocate memory during tokenization");
  count = 0;

  tmp = strtok(tmp, " ");
  while (tmp != NULL) {
    *(result + count) = strdup(tmp);
    ASSERT(result + count, "Couldn't allocate memory during tokenization");
    tmp = strtok(NULL, " ");
    count++;
  }

  *size = count;

  FREE(tmp_init);
  return result;
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
