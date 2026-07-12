#ifndef CALLBACKS_STARTCLICKTIMER_H
#define CALLBACKS_STARTCLICKTIMER_H

#include <stdbool.h>

#include <gtk/gtk.h>

#include "graphics/globals.h"


static void callback_startStopClickTimer(GtkWidget* widget, gpointer user_data) {
  if (SLEEP_MS > 0 && CLICK_FUNC != NULL && !click_timer_is_active) {
    // TODO: start thread
    click_timer_is_active = true;
    gtk_button_set_label(GTK_BUTTON(widget), "Stop");
  } else if (click_timer_is_active) {
    // TODO: stop thread
    click_timer_is_active = false;
    gtk_button_set_label(GTK_BUTTON(widget), "Start");
  }
}

#endif /* CALLBACKS_STARTCLICKTIMER_H */