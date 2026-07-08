#ifndef MACROS_H
#define MACROS_H

#if defined(__APPLE__) || defined(__MACH__)
  #include "macos/mouse/mouse.h"
#elif defined(__LINUX__) || defined(__unix__)
  #include "linux/mouse/mouse.h"
#endif

#include <ApplicationServices/ApplicationServices.h> // MacOS Quartz Event Services

#include <stdlib.h>

#include "builtins.h"

typedef struct macro_part {
  int x;
  int y;
  
  void (*func)(int x, int y);
  
  struct macro_part* next;
} macro_part;

typedef struct Macro {
  macro_part* first;
  macro_part* last;
} Macro;

/// Could return NULL, that check falls on the caller
Macro* initializeMacro();

void freeMacro(Macro* mac);

void addMacroStep(Macro* mac, void (*func)(int x, int y), int x, int y);
void removeMacroStep(Macro* mac, int offset);

void runMacro(const Macro* mac);

#endif /* MACROS_H */
