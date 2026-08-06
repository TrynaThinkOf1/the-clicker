#ifndef UNIX_MACRO_STORAGE_H
#define UNIX_MACRO_STORAGE_H

#if defined(__APPLE__) || defined(__MACH__) || defined(__LINUX__) || defined(__unix__)

  #include <stdio.h>
  #include <pwd.h>
  #include <unistd.h>
  #include <sys/stat.h>
  #include <sys/types.h>
  #include <stdbool.h>
  #include <string.h>

  #include "macros.h"
  #include "builtins.h"

  char* getHomeDir();

  /*
   * Can be used for both files and directories
   */
  bool filepathExists(const char* abs_name);

  /*
   * @contract: the passed name does not already exist
   */
  bool createDirectory(const char* abs_name);

  /*
   * Caller creates stack VLA to pass in
   * Example:
   *   char* names[3] = {"root", "directory", "file.txt"};
   *
   *   int size = 0;
   *   for (int i = 0; i < 3; i++) size += strlen(names[i]);
   *
   *   char abs[size + 3]; // the size of all the names and all the '/'
   *   createAbsName(names, 3, abs, size + 3); // "root/directory/file.txt" (technically bool true/false)
   *
   * @contract: absolute is calculated to be wide enough
   */
  bool createAbsName(char** names, int len, char* restrict absolute, int abs_len);

  void deleteFile(const char* abs_name);

  //

  bool exportMacro(Macro* mac, char* error);

  /*
   * Frees `op_mac` on error
   */
  bool importMacro(const char* name, Macro* op_mac, char* error);

  void deleteMacro(Macro* mac);

#endif

#endif /* UNIX_MACRO_STORAGE_H */
