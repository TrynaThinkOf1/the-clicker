#ifndef UNIX_MACRO_STORAGE_H
#define UNIX_MACRO_STORAGE_H

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
  #include "builtins.h"
  #include "parse_int.h"

  #define MACRO_STORAGE "/.clicker_macros/"
  

  bool directoryExists(const char* dir);
  bool createDirectory(const char* dir);

  bool nameExists(const char* name);

  bool exportMacro(Macro* mac);

  Macro* importMacro(char* name);

  void deleteMacro(const char* name);

#endif

#endif /* UNIX_MACRO_STORAGE_H */
