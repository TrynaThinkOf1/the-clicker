#ifndef UNIX_MACRO_STORAGE_H
#define UNIX_MACRO_STORAGE_H

#if defined(__APPLE__) || defined(__MACH__) || defined(__LINUX__) || defined(__unix__)

  #include <pwd.h>
  #include <unistd.h>

  char* getHomeDir();

#endif

#endif /* UNIX_MACRO_STORAGE_H */
