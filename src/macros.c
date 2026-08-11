#include "macros.h"

#include <stdlib.h>

#include "builtins.h"


Macro* initializeMacro() {
  Macro* mac = malloc(sizeof(*mac));
  if (!mac) return NULL;

  mac->first = NULL;
  mac->last = NULL;

  return mac;
}


void freeMacro(Macro* mac) {
  while (mac->first != mac->last) {
    macro_part* new_head = mac->first->next;
    free(mac->first);
    mac->first = new_head;
  }

  free(mac->last);

  free(mac->name);
  
  free(mac);
}


void addMacroStep(Macro* mac, void (*func)(int x, int y), int x, int y) {
  macro_part* part = malloc(sizeof(*part));
  if (!part) return;

  part->func = func;
  part->x = x;
  part->y = y;
  part->next = NULL;

  if (mac->first == NULL) {
    mac->first = part;
    mac->last = part;
  } else {
    mac->last->next = part;
    mac->last = part;
  }

  mac->saved = false; // we just added a whole new step
}


void removeMacroStep(Macro* mac, int offset) {
  return;
}

void runMacro(const Macro* mac) {
  macro_part* part = mac->first;
  while (part != NULL) {
    part->func(part->x, part->y);
    part = part->next;
  }
}