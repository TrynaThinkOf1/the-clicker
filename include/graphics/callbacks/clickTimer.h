#ifndef CLICKTIMER_H
#define CLICKTIMER_H

#include <gtk/gtk.h>

#include "graphics/state.h"


static gpointer clickTimer(gpointer user_data) {
  ClickTimerState* state = (ClickTimerState*)user_data;
  
  while (g_atomic_int_get(&state->timer_active)) {
    g_usleep(state->sleep_ms * 1000);
    state->click_func(state->x, state->y);
  }
  
  return NULL;
}

#endif /* CLICKTIMER_H */