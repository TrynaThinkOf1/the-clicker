#ifndef EXPORT_MACROS_H
#define EXPORT_MACROS_H

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

#endif /* EXPORT_MACROS_H */