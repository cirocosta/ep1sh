#include "ep1sh/cli.h"
#include "ep1sh/debug.h"

void test1()
{
  const char input[] = "/bin/ls -l";
  const char* expected[] = { "/bin/ls", "-l" };

  unsigned argc = 0;
  char** argv = NULL;
  argv = ep1sh_tokenize(input, &argc);

  for (unsigned i = 0; i < argc; i++)
    ASSERT(strcmp(argv[i], expected[i]) == 0, "%s != %s", argv[i], expected[i]);

  while (argc-- > 0)
    FREE(argv[argc]);
  FREE(argv);
}

void test2()
{
  const char input[] = "  cd  directory  ";
  const char* expected[] = { "cd", "directory" };

  unsigned argc = 0;
  char** argv = NULL;
  argv = ep1sh_tokenize(input, &argc);

  ASSERT(argc == 2, "%d != %d", argc, 2);
  for (unsigned i = 0; i < argc; i++)
    ASSERT(strcmp(argv[i], expected[i]) == 0, "%s != %s", argv[i], expected[i]);

  while (argc-- > 0)
    FREE(argv[argc]);
  FREE(argv);
}

void test3()
{
  const char input[] = "     ";
  const char* expected[] = { "" };

  unsigned argc = 0;
  char** argv = NULL;
  argv = ep1sh_tokenize(input, &argc);

  ASSERT(argc == 0, "%d != %d", argc, 0);
  for (unsigned i = 0; i < argc; i++)
    ASSERT(strcmp(argv[i], expected[i]) == 0, "%s != %s", argv[i], expected[i]);

  while (argc-- > 0)
    FREE(argv[argc]);
  FREE(argv);
}

int main()
{
  test1(); LOG("TEST1\tOK");
  test2(); LOG("TEST2\tOK");

  return EXIT_SUCCESS;
}
