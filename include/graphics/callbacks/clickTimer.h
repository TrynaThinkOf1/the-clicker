#ifndef CLICKTIMER_H
#define CLICKTIMER_H

#include <gtk/gtk.h>

#include "graphics/state.h"


static gpointer clickTimer(gpointer user_data) {
  ClickTimerState* state = (ClickTimerState*)user_data;

  while (g_atomic_int_get(&state->timer_active)) {
    gulong remaining = state->sleep_ms;
    
    while (remaining > 0 && g_atomic_int_get(&state->timer_active)) {
      gulong chunk = remaining < 50 ? remaining : 50;
      g_usleep(chunk * 1000);
      remaining -= chunk;
    }
    
    if (g_atomic_int_get(&state->timer_active)) state->click_func(state->x, state->y);
  }

  return NULL;
}

#endif /* CLICKTIMER_H */
