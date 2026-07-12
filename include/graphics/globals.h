#ifndef GLOBALS_H
#define GLOBALS_H

#include <stdint.h>
#include <stdbool.h>

#include <gtk/gtk.h>
#include <pthread.h>

#include "builtins.h"

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

uint64_t SLEEP_MS = 0;

int CLICK_X = 0;
int CLICK_Y = 0;

void (*CLICK_FUNC)(int x, int y) = leftClick;
GtkWidget* FUNC_SELECTOR;


bool click_timer_is_active = false;

pthread_t click_timer_thread;
//

#endif /* GLOBALS_H */