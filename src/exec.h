#ifndef EP1SH__EXEC_H
#define EP1SH__EXEC_H

#include <errno.h>
#include <unistd.h>
#include "debug.h"

bool check_file(const char* fname) { 
  int rval;

  rval = access(fname, F_OK);
  if (!rval)
    return true;

  switch (rval) {
    case ENOENT:
      LOGERR("");
      break;

    case EACCES:
      LOGERR("");
      break;
    default:
      LOGERR("");
  }

  return false;
}

#endif
