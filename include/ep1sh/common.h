#ifndef EP1SH__COMMON_H
#define EP1SH__COMMON_H

#include <stdlib.h>
#include <string.h>

#define FREE(__ptr)                                                            \
  do {                                                                         \
    free(__ptr);                                                               \
    __ptr = 0;                                                                 \
  } while (0)

#define FREE_ARR(__ptr, __count)                                               \
  do {                                                                         \
    unsigned __i = 0;                                                          \
    while (__i < __count)                                                      \
      free(__ptr[__i++]);                                                      \
    free(__ptr);                                                               \
    __ptr = 0;                                                                 \
  } while (0)

#define LOG(__msg, ...)                                                        \
  do {                                                                         \
    fprintf(stdout, "\n(LOG)\t");                                              \
    fprintf(stdout, __msg, ##__VA_ARGS__);                                     \
  } while (0)

#define LOGERR(__msg, ...)                                                     \
  do {                                                                         \
    fprintf(stderr, "\n(LOGERR)\t");                                           \
    fprintf(stderr, __msg, ##__VA_ARGS__);                                     \
  } while (0)

#define ASSERT(__cond, __msg, ...)                                             \
  do {                                                                         \
    if (!(__cond)) {                                                           \
      fprintf(stderr, "\n" __BASE_FILE__ " %2d\n", __LINE__);                   \
      fprintf(stderr, "Assertion `%s` failed\n", #__cond);                     \
      fprintf(stderr, "\t" __msg "\n", ##__VA_ARGS__);                         \
      exit(EXIT_FAILURE);                                                      \
    }                                                                          \
  } while (0)

#endif // ! EP1SH__COMMON_H
