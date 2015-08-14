#include "ep1sh/common.h"
#include "ep1sh/debug.h"

void test1()
{
  const char input[] = "/bin/ls -l";
  const char* expected[] = { "/bin/ls", "-l", NULL };

  unsigned argc = 0;
  char** argv = NULL;
  argv = ep1sh_split_string(input, &argc, ' ');

  for (unsigned i = 0; i < argc; i++)
    ASSERT(strcmp(argv[i], expected[i]) == 0, "%s != %s", argv[i], expected[i]);
  ASSERT(argv[argc] == NULL, "Must end with a NULL");

  FREE_ARR(argv, argc);
}

void test2()
{
  const char input[] = "  cd  directory  ";
  const char* expected[] = { "cd", "directory", NULL };

  unsigned argc = 0;
  char** argv = NULL;
  argv = ep1sh_split_string(input, &argc, ' ');

  ASSERT(argc == 2, "%d != %d", argc, 2);
  for (unsigned i = 0; i < argc; i++)
    ASSERT(strcmp(argv[i], expected[i]) == 0, "%s != %s", argv[i], expected[i]);
  ASSERT(argv[argc] == NULL, "Must end with a NULL");

  FREE_ARR(argv, argc);
}

void test3()
{
  const char input[] = "     ";
  const char** expected = NULL;

  unsigned argc = 0;
  char** argv = NULL;
  argv = ep1sh_split_string(input, &argc, ' ');

  ASSERT(argc == 0, "%d != %d", argc, 0);
  for (unsigned i = 0; i < argc; i++)
    ASSERT(strcmp(argv[i], expected[i]) == 0, "%s != %s", argv[i], expected[i]);
  ASSERT(argv[argc] == NULL, "Must end with a NULL");

  FREE(argv);
}

void test4()
{
  const char input[] = "/home:/home/Hue:/home/Hue/BrBr";
  const char* expected[] = { "/home", "/home/Hue", "/home/Hue/BrBr", NULL };

  unsigned argc = 0;
  char** argv = NULL;
  argv = ep1sh_split_string(input, &argc, ':');

  ASSERT(argc == 3, "%d != %d", argc, 3);
  for (unsigned i = 0; i < argc; i++)
    ASSERT(strcmp(argv[i], expected[i]) == 0, "%s != %s", argv[i], expected[i]);
  ASSERT(argv[argc] == NULL, "Must end with a NULL");

  FREE_ARR(argv, argc);
}

int main()
{
  test1();
  LOG("TEST1\tOK");
  test2();
  LOG("TEST2\tOK");
  test3();
  LOG("TEST3\tOK");
  test4();
  LOG("TEST4\tOK");

  return EXIT_SUCCESS;
}
