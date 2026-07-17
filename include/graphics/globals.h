#ifndef GLOBALS_H
#define GLOBALS_H

#include <stdint.h>
#include <stdbool.h>

#include <gtk/gtk.h>
#include <pthread.h>

#include "builtins.h"
#include "macros.h"

/*
 * File to hold global variables that can be set
 * via entries and buttons that cannot necessarily
 * communicate otherwise (with a simple API, at least)
 */

// GLOBAL STATE FOR DEFAULT CLICK-TIMER FUNCTIONALTIY
struct entry_holder {
  GtkWidget* e1;
  GtkWidget* e2;
  GtkWidget* e3;
};
struct entry_holder holder = {0};

struct coord_holder {
  GtkWidget* xentry;
  GtkWidget* yentry;
};
struct coord_holder coords = {0};

uint64_t SLEEP_MS = 0;

int CLICK_X = -1;
int CLICK_Y = -1;

void (*CLICK_FUNC)(int x, int y) = leftClick;
GtkWidget* FUNC_SELECTOR;


bool click_timer_is_active = false;
volatile bool click_timer_should_stop = false;

pthread_t click_timer_thread;
//

// GLOBAL STATE FOR MACRO BOX
GtkWidget* macro_name_entry;

Macro* current_macro = NULL;

int NEXT_Y_POSITION = 0; // so that I can build an orderly stack of macro actions
// 

#endif /* GLOBALS_H */