#ifndef EP1SH__DEBUG_H
#define EP1SH__DEBUG_H

#include <stdio.h>
#include <stdlib.h>

#define LOG(message, ...)                                                      \
  do {                                                                         \
    fprintf(stdout, "\n(LOG)\t");                                              \
    fprintf(stdout, message, ##__VA_ARGS__);                                   \
  } while (0)

#define LOGERR(message, ...)                                                   \
  do {                                                                         \
    fprintf(stderr, "\n(LOGERR)\t");                                           \
    fprintf(stderr, message, ##__VA_ARGS__);                                   \
  } while (0)

#define ASSERT(condition, message, ...)                                        \
  do {                                                                         \
    if (!(condition)) {                                                        \
      fprintf(stderr, "\n" __BASE_FILE__ "%2d\n", __LINE__);                   \
      fprintf(stderr, "Assertion `%s` failed\n", #condition);                  \
      fprintf(stderr, "\t" message "\n", ##__VA_ARGS__);                       \
      exit(EXIT_FAILURE);                                                      \
    }                                                                          \
  } while (0)

#ifndef NDEBUG
#define DASSERT(condition, message, ...)                                       \
  ASSERT(condition, message, #__VA_ARGS__)
#define DLOG(message, ...) LOG(message, ##__VA_ARGS__)
#define DLOGERR(message, ...) LOGERR(message, ##__VA_ARGS__)
#define DPERROR(message)                                                       \
  do {                                                                         \
    perror(message)                                                            \
  } while (0)
#else
#define DASSERT(condition, message, ...)
#define DLOG(message, ...)
#define DLOGERR(message, ...)
#define DPERROR(message)
#endif // ! NDEBUG

#endif // ! EP1SH__DEBUG_H
