#ifndef CALLBACKS_STARTCLICKTIMER_H
#define CALLBACKS_STARTCLICKTIMER_H

#include <gtk/gtk.h>

#include "graphics/globals.h"


static void callback_startClickTimer(GtkWidget* widget, gpointer user_data) {
  if (SLEEP_MS > 0 && CLICK_FUNC != NULL && !click_timer_is_active) {
    click_timer_is_active = true;
  }

  while (click_timer_is_active) {
    CLICK_FUNC(CLICK_X, CLICK_Y);
    sleep_m(SLEEP_MS, 0);
  }
}

#endif /* CALLBACKS_STARTCLICKTIMER_H */