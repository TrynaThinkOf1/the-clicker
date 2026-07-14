#include "linux/macro_storage.h"

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

  /*
  * Don't worry about all of the repeated calls to `getFullPath`, the compiler
  * caches it in a register so it's not actually getting called 100 times
  */

  char* getFullPath(const char* dir, const char* name) {
    uid_t uid = getuid(); // find the ID of the user
    struct passwd* info = getpwuid(uid); // get the user's info NOT PASSWORD!!

    char* full_path = malloc(strlen(info->pw_dir) + strlen(dir) + strlen(name) + 1);
    if (!full_path) return NULL;

  	strcpy(full_path, info->pw_dir);
  	strcat(full_path, dir);
  	strcat(full_path, name);

  	return full_path;
  }


  bool directoryExists(const char* dir) {
    char* full_path = getFullPath(dir, "");
    if (full_path == NULL) return false;

    struct stat st = {0};
    if (stat(full_path, &st) == -1) {
      free(full_path);
      return false;
    }

    free(full_path);
    return true;
  }

  bool createDirectory(const char *dir) {
    char* full_path = getFullPath(dir, "");
    if (full_path == NULL) return false;

    // these permissions represent READ, WRITE, EXECUTE for users, groups, and others
    if (mkdir(full_path, S_IRWXU | S_IRWXG | S_IRWXO) == -1) {
      free(full_path);
      return false;
    }

    free(full_path);
    return true;
  }


  bool nameExists(const char* name) {
    if (!directoryExists(MACRO_STORAGE)) return false;

    //

    char* full_path = getFullPath(MACRO_STORAGE, name);
    if (full_path == NULL) return false;

    struct stat st = {0};
    if (stat(full_path, &st) == -1) {
      free(full_path);
      return false;
    }

    free(full_path);
    return true;
  }

  /*
   * 
   */

  bool exportMacro(const Macro* mac) {
    if (mac->first == NULL) return false;

    if (nameExists(mac->name)) return false;
    if (!directoryExists(MACRO_STORAGE)) if (!createDirectory(MACRO_STORAGE)) return false;

    char* full_path = getFullPath(MACRO_STORAGE, mac->name);
    if (full_path == NULL) return false;

    FILE* file = fopen(full_path, "w");
    if (file == NULL) {
      free(full_path);
      return false;
    }

    //

    fprintf(file, "\"%s\": {\n", mac->name);

    macro_part* part = mac->first;
    while (part != NULL) {
      fprintf(file, "\t");
      
      if (part->func == moveCursor) {
        fprintf(file, "moveCursor(");
      } else if (part->func == leftClick) {
        fprintf(file, "leftClick(");
      } else if (part->func == rightClick) {
        fprintf(file, "rightClick(");
      } else if (part->func == leftDoubleClick) {
        fprintf(file, "leftDoubleClick(");
      } else if (part->func == rightDoubleClick) {
        fprintf(file, "rightDoubleClick(");
      } else if (part->func == sleep_m) {
        fprintf(file, "sleep_m(");
      }

      fprintf(file, "%i, %i)\n", part->x, part->y);

      part = part->next;
    }

    fprintf(file, "}\n");

    //

    mac->saved = true;

    fclose(file);
    free(full_path);
    return true;
  }

  Macro* importMacro(const char* name) {
    if (!nameExists(name)) return NULL;
    printf("Name `%s` existed.\n", name);

    char* full_path = getFullPath(MACRO_STORAGE, name);
    if (full_path == NULL) return false;
    printf("Full path `%s` created.\n", full_path);

    FILE* file = fopen(full_path, "r");
    free(full_path);
    if (file == NULL) {
      return false;
    }
    printf("File opened successfully, file: `%p`.\n", file);

    Macro* mac = initializeMacro();
    if (mac == NULL) {
      fclose(file);
      return false;
    }
    printf("Macro allocated successfully, mac: `%p`.\n", mac);

    char buffer[100];
    int ch, idx = 0;
    while ((ch = getc(file)) != EOF) {
      while (ch != '\n' && idx < 99) {
        buffer[idx] = ch;
        ch = getc(file);
        idx++;
      }
      buffer[idx + 1] = '\0';

      int x = -2, y = -2;

      // grab the x and y coordinate encoded
      if (buffer[0] == '\t') {
        int begindex = 0, endex;
        
        while (((buffer[begindex] < 48 || buffer[begindex] > 57) && buffer[begindex] != '-') && begindex < idx) begindex++;
        if (begindex < idx) {
          endex = begindex;
          while ((buffer[endex] >= 48 && buffer[endex] <= 57 || buffer[endex] == '-') && endex < idx) endex++;
          if (endex > begindex) {
            printf("buffer: `%s`, begindex: %i, endex: %i\n", buffer, begindex, endex);
            x = parse_int(&buffer[begindex], endex - begindex - (buffer[begindex] == '-' ? 2 : 1));
            printf("x parsed successfully, x: %i.\n", x);
          }

          begindex = endex + 2;
          endex = begindex;
          if (begindex < idx) {
            while ((buffer[endex] >= 48 && buffer[endex] <= 57 || buffer[endex] == '-') && endex < idx) endex++;
            if (endex > begindex) {
              printf("buffer: `%s`, begindex: %i, endex: %i\n", buffer, begindex, endex);
              y = parse_int(&buffer[begindex], endex - begindex - (buffer[begindex] == '-' ? 2 : 1));
              printf("y parsed successfully, y: %i.\n", y);
            }
          }
        }
      }

      // parse the function name
      if (x >= -1 && y >= -1) {
        macro_part* part = malloc(sizeof(*part));
        part->x = x;
        part->y = y;
        part->func = NULL; // placeholder
        part->next = NULL;
        
        int endex = 1;
        while (buffer[endex] != '(' && endex < idx) endex++;
        char* name = malloc(endex);
        if (name == NULL) continue;
        strlcpy(name, buffer + 1, endex);
        printf("Name: `%s`.\n", name);

        if (strcmp(name, "moveCursor") == 0) {
          part->func = moveCursor;
        } else if (strcmp(name, "leftClick") == 0) {
          part->func = leftClick;
        } else if (strcmp(name, "rightClick") == 0) {
          part->func = rightClick;
        } else if (strcmp(name, "leftDoubleClick") == 0) {
          part->func = leftDoubleClick;
        } else if (strcmp(name, "rightDoubleClick") == 0) {
          part->func = rightDoubleClick;
        } else if (strcmp(name, "sleep_m") == 0) {
          part->func = sleep_m;
        }

        if (part->func != NULL) {
          if (mac->first == NULL) {
            mac->first = part;
            mac->last = part;
            part->next = part;
          } else {
            mac->last->next = part;
            mac->last = part;
          }

          printf("Name parsed successfully, name: `%s`.\n", name);
          printf("\npart: {\n\tx: %i\n\ty: %i\n\n\tfunc: %p\n\tnext: %p\n}\n\n", x, y, part->func, part->next);
        }

        free(name);
      }
      
      memset(buffer, 0, 100);
      idx = 0;
    } 
    
    // 

    mac->name = name;
    mac->saved = true;
    
    fclose(file);
    return mac;
  }

  void deleteMacro(const char* name) {
    char* full_path = getFullPath(MACRO_STORAGE, name);
    if (full_path == NULL) return;

    remove(full_path);

    free(full_path);
  }

#endif
