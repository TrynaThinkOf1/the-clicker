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
  #include <regex.h> // woah.

  #include "macros.h"
  #include "builtins.h"
  #include "debug_tests.h"

  #define STORAGE_DIR ".clicker_macros"
  
  /* 
  * Pattern explanation:
  * \t       : Matches a literal tab character (C compiler converts \t to 0x09)
  * (...)    : Group containing allowed command strings (alternation)
  * \\(      : Matches a literal '(' (escaped for regex, so \\ in C string)
  * -?       : Optional minus sign for negative numbers
  * [0-9]+   : One or more digits
  * ,        : Literal comma
  * [ ]      : Literal space
  * \\)      : Matches a literal ')'
  * \n       : Matches a literal newline character (C compiler converts \n to 0x0A)
  */
  static const char* PATTERN = "\t(leftClick|rightClick|leftDoubleClick|rightDoubleClick|sleep_m|moveCursor)\\(-?[0-9]+, -?[0-9]+\\)\n";


  bool regexMatch(const char* string, const char* pattern, char** error);

  //

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
   *   int size = 0; // calculate size including '/' and NUL
   *
   *   char abs[size + 3]; // the size of all the names and all the '/'
   *   createAbsName(names, 3, abs, size + 3); // "root/directory/file.txt" (technically bool true/false)
   *
   * @contract: absolute is calculated to be wide enough
   */
  bool createAbsName(const char** names, int len, char* restrict absolute, int abs_len);

  //

  bool exportMacro(Macro* mac, char** error);

  /*
   * @contract: op_mac is NOT initialized, only a stack variable
   */
  bool importMacro(const char* name, Macro** op_mac, char** error);

  /*
   * This does NOT free the macro
   */
  void deleteMacro(Macro* mac);

#endif

#endif /* UNIX_MACRO_STORAGE_H */
