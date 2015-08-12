#ifndef EP1SH__COMMON_H
#define EP1SH__COMMON_H

#define FREE(ptr)                                                              \
  do {                                                                         \
    free(ptr);                                                                 \
    ptr = 0;                                                                   \
  } while (0)

#endif // ! EP1SH__COMMON_H
