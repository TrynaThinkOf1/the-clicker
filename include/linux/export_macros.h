#ifndef UNIX_EXPORT_MACROS_H
#define UNIX_EXPORT_MACROS_H

#if defined(__APPLE__) || defined(__MACH__) || defined(__LINUX__) || defined(__unix__)

  #include <stdlib.h>
  #include <stdio.h>
  #include <unistd.h>
  #include <sys/stat.h>
  #include <sys/types.h>
  #include <pwd.h>
  #include <string.h>
  #include <stdbool.h>

  #include "macros.h"

  #define MACRO_STORAGE "/.clicker_macros/"
  

  bool directoryExists(const char* dir);
  bool createDirectory(const char* dir);

  bool nameExists(const char* name);

  bool exportMacro(const Macro* mac, const char* name);

  Macro* importMacro(const char* name);

  void deleteMacro(const char* name);

#endif

#endif /* UNIX_EXPORT_MACROS_H */
