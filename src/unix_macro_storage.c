#include "linux/macro_storage.h"
#include "macros.h"
#include <stdio.h>

#if defined(__APPLE__) || defined(__MACH__) || defined(__LINUX__) || defined(__unix__)

  bool regexMatch(const char* string, const char* pattern, char** error) {
    int status;
    regex_t re;
    
    if (regcomp(&re, pattern, REG_EXTENDED) != 0) {
      *error = "Failed to initialize RegEx engine!";
      return false;
    }
    
    status = regexec(&re, string, 0, NULL, 0);
    regfree(&re);
    
    *error = NULL;
    return status == 0;
  }

  //

  char* getHomeDir() {
    struct passwd* info = getpwuid(getuid()); // get the user's info NOT PASSWORD!!
    return info->pw_dir;
  }

  bool filepathExists(const char* abs_name) {
    struct stat st = {0};
    return stat(abs_name, &st) != -1;
  }

  bool createDirectory(const char* abs_name) {
    // these permissions are READ/WRITE/EXEC for all users and groups, kinda unsafe :/
    return mkdir(abs_name, S_IRWXU | S_IRWXG | S_IRWXO) != -1;
  }

  bool createAbsName(const char** names, int len, char* restrict absolute, int abs_len) {
    absolute[0] = '\0'; // super elusive garbage-init bug causes whole func to fail
    size_t offset = 0;

    for (int i = 0; i < len; i++) {
      register int size = strlen(names[i]); // not actually recomputed, it gets cached
      if (strlcat(absolute, names[i], abs_len) < size + offset ||
        (i < len - 1 && strlcat(absolute, "/", abs_len) < size + offset + 1)) return false;
      offset += size + 1; // + 1 for the '/'
    }

    return true;
  }

  //

  bool exportMacro(Macro* mac, char** error) {
    const char* names[] = {getHomeDir(), STORAGE_DIR, mac->name};
    int size = strlen(names[0]) + strlen(names[1]) + 2; // +1 for the '/' and +1 for the NUL
    char directory[size];
    if (!createAbsName(names, 2, directory, size)) {
      *error = "Filesystem Failure: Could not resolve directory path.";
      return false;
    }

    if (!filepathExists(directory)) {
      if (!createDirectory(directory)) {
        *error = "Filesystem Failure: Could not create storage directory.";
        return false;
      }
    }

    size += strlen(names[2]) + 1; // +1 for the next '/'
    char absolute[size];
    if (!createAbsName(names, 3, absolute, size)) {
      *error = "Filesystem Failure: Could not resolve file path.";
      return false;
    }

    if (filepathExists(absolute)) {
      *error = "Macro already exists!";
      return false;
    }

    //

    FILE* fp = fopen(absolute, "w");
    if (fp == NULL) {
      *error = "Failed to create macro storage file!";
      return false;
    }

    fprintf(fp, "\"%s\": {\n", mac->name);

    macro_part* p = mac->first;
    if (p == NULL) {
      *error = "Cannot save empty macro!";
      return false;
    }

    while (p != NULL) {
      char* name = getFuncName(p->func);
      if (p == NULL) {
        *error = "Invalid macro step!";
        return false;
      }

      fprintf(fp, "\t%s(%d, %d)\n", name, p->x, p->y);

      p = p->next;
    }

    fprintf(fp, "}\n");
    fclose(fp);

    mac->saved = true;
    return true;
  }

  bool importMacro(const char* name, Macro** op_mac, char** error) {
    const char* names[] = {getHomeDir(), STORAGE_DIR, name};
    int size = strlen(names[0]) + strlen(names[1]) + 2; // +1 for the '/' and +1 for the NUL
    char directory[size];
    if (!createAbsName(names, 2, directory, size)) {
      *error = "Filesystem Failure: Could not resolve directory path.";
      return false;
    }

    if (!filepathExists(directory)) {
      if (!createDirectory(directory)) {
        *error = "Filesystem Failure: Could not create storage directory.";
      } else {
        *error = "Macro does not exist!"; // if the dir doesnt exist neither does the file
      }

      return false;
    }

    size += strlen(names[2]) + 1; // +1 for the next '/'
    char absolute[size];
    if (!createAbsName(names, 3, absolute, size)) {
      *error = "Filesystem Failure: Could not resolve file path.";
      return false;
    }

    if (!filepathExists(absolute)) {
      *error = "Macro does not exist!";
      return false;
    }

    //

    FILE* fp = fopen(absolute, "r");
    if (fp == NULL) {
      *error = "Failed to read macro storage file!";
      return false;
    }

    *op_mac = initializeMacro();
    Macro* mac = *op_mac;
    
    register size_t s = (strlen(name) + 1) * sizeof(char);
    char* copied_name = malloc(s);
    if (copied_name == NULL || strlcpy(copied_name, name, s) < s - 1 || mac == NULL) {
      *error = "Failed to allocate macro!";
      return false;
    }
    mac->name = copied_name;
    mac->saved = true;

    char* regerr = NULL;
    char* line = NULL;
    size_t len;
    ssize_t read;
    while ((read = getline(&line, &len, fp)) != -1) {
      if (!regexMatch(line, PATTERN, &regerr)) {
        if (regerr != NULL) {
          *error = regerr;
          return false;
        }
        continue;
      }

      // if it passed regex that means it must have proper format and naming, therefore sscanf() can be used

      char func_name[17] = {0}; // longest possible name is rightDoubleClick @ 16 chars
      int x, y;
      /*
       * leading space = skip any leading whitespace ( , \t, \n, \r)
       * the %16[^(] means it will read in either 16 characters or until it hits the '('
       * %d, %d are the x and y of the line
       */
      if (sscanf(line, " %16[^(](%d, %d)", func_name, &x, &y) != 3) continue; // just skip the line

      void (*func)(int x, int y) = getNameFunc(func_name);
      if (func == NULL) continue; // skip - fluke?

      CLICKER_ASSERT(mac == NULL, "On import : op_mac = NULL");
      
      addMacroStep(mac, func, x, y);

      CLICKER_ASSERT(mac->first == NULL, "On import : op_mac->first = NULL");
      CLICKER_ASSERT(mac->last == NULL, "On import : op_mac->last = NULL");
    }

    return true;
  }

  void deleteMacro(Macro* mac) {
    const char* names[] = {getHomeDir(), STORAGE_DIR, mac->name};
    int size = strlen(names[0]) + strlen(names[1]) + strlen(names[2]) + 3; // +2 for the '/' and +1 for the NUL
    char absolute[size];
    if (!createAbsName(names, 3, absolute, size)) return; // macro doesn't exist, no need for deletion
    else remove(absolute);

    mac->saved = false;
  }

#endif
