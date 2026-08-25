#ifndef TOGGLECLICKTIMER_H
#define TOGGLECLICKTIMER_H

#include <gtk/gtk.h>

#include "builtins.h"
#include "graphics/state.h"
#include "graphics/sendNotification.h"
#include "linux/macro_storage.h"
#include "graphics/callbacks/clickTimer.h"


static void toggleClickTimer(GtkWidget* button, gpointer user_data) {
  ClickTimerState* state = (ClickTimerState*)user_data;

  state->sleep_ms =
    (gtk_spin_button_get_value_as_int(state->mins_spinbtn) * 60 * 1000)
    + (gtk_spin_button_get_value_as_int(state->secs_spinbtn) * 1000)
    + gtk_spin_button_get_value_as_int(state->ms_spinbtn);

  if (state->sleep_ms <= 0) {
    send_notification("Invalid Wait Time", "Timer must be for more than 0ms between clicks", state->app);
    return;
  }

  const char* xstr = gtk_entry_buffer_get_text(gtk_entry_get_buffer(state->x_coord_entry));
  const char* ystr = gtk_entry_buffer_get_text(gtk_entry_get_buffer(state->y_coord_entry));

  if (strlen(xstr) == 0 || strlen(ystr) == 0) {
    state->x = -1;
    state->y = -1;
  } else {
    if (sscanf(xstr, "%i", &state->x) != 1) {
      send_notification("Invalid X Coordinate", "The X coordinate for the click timer must be a number between 0 and 2^31 - 1", state->app);
      return;
    }
    if (sscanf(ystr, "%i", &state->y) != 1) {
      send_notification("Invalid Y Coordinate", "The Y coordinate for the click timer must be a number between 0 and 2^31 - 1", state->app);
      return;
    }
  }

  // do the threading

  if (!g_atomic_int_get(&state->timer_active)) {
    g_atomic_int_set(&state->timer_active, TRUE);
    state->timer_thread = g_thread_new("click-timer", clickTimer, state);

    gtk_button_set_label(GTK_BUTTON(state->start_stop_button), "STOP");
  } else {
    g_atomic_int_set(&state->timer_active, FALSE);
    g_thread_join(state->timer_thread);
    state->timer_thread = NULL;
    
    gtk_button_set_label(GTK_BUTTON(state->start_stop_button), "START");
  }
}

#endif /* TOGGLECLICKTIMER_H */