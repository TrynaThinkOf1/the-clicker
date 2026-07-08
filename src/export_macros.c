#include "export_macros.h"

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <pwd.h>
#include <string.h>
#include <stdbool.h>

#include "macros.h"

/*
 * Don't worry about all of the repeated calls to `getFullPath`, the compiler
 * caches it in a register so it's not actually getting called 100 times
 */

char* getFullPath(const char* dir, const char* name) {
  uid_t uid = getuid(); // find the ID of the user
  struct passwd* info = getpwuid(uid); // get the user's info NOT PASSWORD!!

  char* full_path = malloc(strlen(info->pw_dir) + strlen(dir) + strlen(name));
  if (!full_path) return NULL;
  
	strcat(full_path, info->pw_dir);
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

//

bool exportMacro(const Macro* mac, const char* name) {
  if (nameExists(name)) return false;
  if (!directoryExists(MACRO_STORAGE)) if (!createDirectory(MACRO_STORAGE)) return false;

  char* full_path = getFullPath(MACRO_STORAGE, name);
  if (full_path == NULL) return false;
  
  FILE* file = fopen(full_path, "w");
  if (file == NULL) {
    free(full_path);
    return false;
  }
  

  fclose(file);
  free(full_path);
  return true;
}

Macro* importMacro(const char* name) {
  if (!nameExists(name)) return NULL;
  
  char* full_path = getFullPath(MACRO_STORAGE, name);
  if (full_path == NULL) return false;

  FILE* file = fopen(full_path, "r");
  if (file == NULL) {
    free(full_path);
    return false;
  }

  fclose(file);
  free(full_path);
  return NULL;
}

void deleteMacro(const char* name) {
  char* full_path = getFullPath(MACRO_STORAGE, name);
  if (full_path == NULL) return;

  remove(full_path);

  free(full_path);
}