#include "linux/macro_storage.h"

#if defined(__APPLE__) || defined(__MACH__) || defined(__LINUX__) || defined(__unix__)

  char* getHomeDir() {
    struct passwd* info = getpwuid(getuid()); // get the user's info NOT PASSWORD!!
    return info->pw_dir;
  }

#endif
