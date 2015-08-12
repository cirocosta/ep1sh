#include "debug.h"
#include "cli.h"

#include <linux/limits.h>
#include <unistd.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

int main()
{
  char* input;
  char prompt[100];
  char pwd[PATH_MAX];

  rl_bind_key('\t', rl_complete);

  while (1) {
    // FIXME what if 100 is not sufficient? [1]
    snprintf(prompt, sizeof(prompt), "[%s] ", getcwd(pwd, PATH_MAX - 1));

    input = readline(prompt);

    if (!input)
      break;

    add_history(input);

    free(input);
  }

  return 0;
}

/**
 * Resources:
 *
 * [1] :
 *http://insanecoding.blogspot.com.br/2014/06/memory-management-in-c-and-auto.html
 *
 */
