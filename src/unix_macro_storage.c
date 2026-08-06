#include "linux/macro_storage.h"

#if defined(__APPLE__) || defined(__MACH__) || defined(__LINUX__) || defined(__unix__)

  char* getHomeDir() {
    struct passwd* info = getpwuid(getuid()); // get the user's info NOT PASSWORD!!
    return info->pw_dir;
  }

  bool directoryExists(const char* abs_name) {
    struct stat st = {0};
    return stat(abs_name, &st) != -1;
  }

  bool createDirectory(const char* abs_name) {
    // these permissions are READ/WRITE/EXEC for all users and groups, kinda unsafe :/
    return mkdir(abs_name, S_IRWXU | S_IRWXG | S_IRWXO) != -1;
  }

  bool createAbsName(const char** names, int len, char* restrict absolute, int abs_len) {
    absolute[0] = '\0'; // super elusive garbage-init bug causes whole func to fail
    int offset = 0;

    for (int i = 0; i < len; i++) {
      register int size = strlen(names[i]); // not actually recomputed, it gets cached
      if (strlcat(absolute, names[i], abs_len) < size + offset || strlcat(absolute, "/", abs_len) < size + offset + 1) return false;
      offset += size + 1; // + 1 for the '/'
    }

    return true;
  }

  void deleteFile(const char* abs_name) {
    remove(abs_name);
  }

  //

  
  bool exportMacro(Macro* mac, char* error) {
    mac->saved = true;
    return true;
  }

  bool importMacro(const char* name, Macro* op_mac, char* error) {
    return true;
  }

  void deleteMacro(Macro* mac) {
    mac->saved = false;
  }

#endif
